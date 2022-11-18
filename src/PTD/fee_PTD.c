/**
 * @file fee_PTD.c
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief Fee library serialize and deserialize PTD packet functions.
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Instuto de Astrofísica de Canarias (IAC)
 * 
 */

#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <fee.h>
#include "../common/fee_common.h"

#define NUM_DARK_INFO_PER_ROW 2 /*Number of dark-info parameters in each row data of the data packet*/
#define NUM_CHANNELS_READFPGA 2 /*UP and Bottom channels. One per each CCD*/
#define NUM_VOLTAGE_REF_INFO 4  /*Number of voltage reference parameters in Pixel data packet*/

#define LENGTH_CHECKSUM_BYTES 2          /*Length in bytes of the checksum*/
#define LENGTH_PIXEL_DATA_CONTER_BYTES 4 /*Length in bytes of the DATA */
#define BYTES_PTD_PARAMETERS 2           /*Length in bytes of each data packet parameter. Only PIXEL_DATA_COUNTER is 4 bytes*/

size_t fee_PTDImageIndx(size_t RowIndex, size_t ColIndex, size_t NumColumns)
{   
    return RowIndex * NumColumns + ColIndex;
}

int fee_Calculate_PTD_Sizes(fee_TM_t TmInformation, fee_PTDSizes_t *PTDSizes, fee_ImageMatrixTotalSizes_t *ImageMatrixSizes)
{

    /*	o is the index of rows defined in Table 3.6 1 and ranges from 1 to WOISIZE/(SBM+1),
    p is the index of over-scan rows defined in  Table 3.6 1 and ranges from 1 to NBTAIL/(SBM+1)*/
    unsigned int NumDataRows = 0;
    unsigned int NumDataParametersPerRow = 0;
    unsigned int NumSmearInfo = 0;
    unsigned int NumOverScanRows = 0;
    unsigned int NumOverScanParametersPerRaw = 0;
    unsigned int DataPacketTotalBytes = 0;
    unsigned int m;

    uint16_t woisize = 0;
    uint16_t nbtail = 0;
    unsigned int spatialbinningmode = 0;
    uint16_t binningsize_1 = 0, binningsize_2 = 0, binningsize_3 = 0, binningsize_4 = 0, binningsize_5 = 0;
    uint16_t bandsize_1 = 0, bandsize_2 = 0, bandsize_3 = 0, bandsize_4 = 0, bandsize_5 = 0;

    woisize = TmInformation.Returned_TC.WOISIZE;
    spatialbinningmode = TmInformation.Returned_TC.SPATIALBINNINGMODE;
    nbtail = TmInformation.Returned_TC.NBTAIL;

    memset(PTDSizes, 0, sizeof(fee_PTDSizes_t));
    memset(ImageMatrixSizes, 0, sizeof(fee_ImageMatrixTotalSizes_t));

    if (TmInformation.Returned_TC.OPMODE != OPMODE_OPERATIONAL ||
        TmInformation.VAU_ERROR ||
        TmInformation.TC_ERROR)
    {
        return FEE_EXIT_SUCCESS;
    }

    /*Check that Bandsize are multplies of Binningsize_n */
    if (BandSize_MultitpleOf_BinningSize(TmInformation.Returned_TC.FREQBINNINGBAND_1) == 0 ||
        BandSize_MultitpleOf_BinningSize(TmInformation.Returned_TC.FREQBINNINGBAND_2) == 0 ||
        BandSize_MultitpleOf_BinningSize(TmInformation.Returned_TC.FREQBINNINGBAND_3) == 0 ||
        BandSize_MultitpleOf_BinningSize(TmInformation.Returned_TC.FREQBINNINGBAND_4) == 0 ||
        BandSize_MultitpleOf_BinningSize(TmInformation.Returned_TC.FREQBINNINGBAND_5) == 0)
    {
        return FEE_EXIT_ERROR;
    }

    /*Get values of bining sizes and band sizes*/
    fee_getFreqBinningBand_parameters(TmInformation.Returned_TC.FREQBINNINGBAND_1, &binningsize_1, &bandsize_1);
    fee_getFreqBinningBand_parameters(TmInformation.Returned_TC.FREQBINNINGBAND_2, &binningsize_2, &bandsize_2);
    fee_getFreqBinningBand_parameters(TmInformation.Returned_TC.FREQBINNINGBAND_3, &binningsize_3, &bandsize_3);
    fee_getFreqBinningBand_parameters(TmInformation.Returned_TC.FREQBINNINGBAND_4, &binningsize_4, &bandsize_4);
    fee_getFreqBinningBand_parameters(TmInformation.Returned_TC.FREQBINNINGBAND_5, &binningsize_5, &bandsize_5);

    /*If woisize is an odd number and SPATIALBINNINGMOD = 1 the data rows is cualculated based on woisize -1 */
    if (TmInformation.Returned_TC.WOISIZE % 2 != 0 && spatialbinningmode == SPATIALBIN_ENABLE)
    {
        woisize = woisize - 1;
    }

    /*Protection against 0 division*/
    if (spatialbinningmode + 1 == 0)
    {
        return FEE_EXIT_ERROR;
    }

    /*Calculation of the number of rows of the image to read*/
    NumDataRows = woisize / (spatialbinningmode + 1);

    /*Calculation of the number of pixels of each bandsize*/
    m = NUM_CHANNELS_READFPGA * (bandsize_1 / binningsize_1 + bandsize_2 / binningsize_2 + bandsize_3 / binningsize_3 +
                                 bandsize_4 / binningsize_4 + bandsize_5 / binningsize_5);
    /*Calculation of the number of parameters of each row */
    NumDataParametersPerRow = NUM_DARK_INFO_PER_ROW * FEE_NUM_CCD + m;

    /*Calculation of the number of total smear parametes*/
    NumSmearInfo = FEE_NUM_SMEAR_ROWS * m;

    /*If nbtail is an odd number and SPATIALBINNINGMOD = 1 the over-scan rows is cualculated based on nbtail -1 */
    if (TmInformation.Returned_TC.WOISIZE % 2 != 0 && spatialbinningmode == SPATIALBIN_ENABLE)
    {
        nbtail = nbtail - 1;
    }

    /*Calculation of the number of rows of the Over-Scan row to read*/
    NumOverScanRows = nbtail / (spatialbinningmode + 1);
    /*Calculation of the number of parameters of of each row*/
    NumOverScanParametersPerRaw = NUM_DARK_INFO_PER_ROW * FEE_NUM_CCD + m;
    /*Calculation in bytes of the whole data packet. PixelDataCounter+Data+SmearInfo+OverScanData+LengthChecksum*/
    DataPacketTotalBytes = LENGTH_PIXEL_DATA_CONTER_BYTES +
                           BYTES_PTD_PARAMETERS * (NumDataParametersPerRow * NumDataRows + NumSmearInfo + NumOverScanParametersPerRaw * NumOverScanRows + NUM_VOLTAGE_REF_INFO) +
                           LENGTH_CHECKSUM_BYTES;

    /*Assign output values*/
    PTDSizes->NumDataRows = NumDataRows;
    PTDSizes->NumDataParametersPerRow_EveryCDD = NumDataParametersPerRow;
    PTDSizes->NumSmearRows = FEE_NUM_SMEAR_ROWS;
    PTDSizes->NumOverScanRows = NumOverScanRows;
    PTDSizes->NumSmearParameters_EveryCCD = NumSmearInfo ;
    PTDSizes->NumDarkInfoPerRow_EveryCCD =  NUM_DARK_INFO_PER_ROW * FEE_NUM_CCD;
    PTDSizes->DataPacketTotalBytes = DataPacketTotalBytes;
                                   
    ImageMatrixSizes->ImageTotalRows = FEE_NUM_SMEAR_ROWS + NumOverScanRows + NumDataRows;    ;           
    ImageMatrixSizes->ImageTotalColumns = PTDSizes->NumDataParametersPerRow_EveryCDD / FEE_NUM_CCD;
    ImageMatrixSizes->ImageMatrixBytes = BYTES_PTD_PARAMETERS * ImageMatrixSizes->ImageTotalColumns * ImageMatrixSizes->ImageTotalRows ;  

    return FEE_EXIT_SUCCESS;
}

int fee_PTD_Read(uint8_t *PixelDataPacket, fee_TM_t TmInformation, fee_PTD_t *PTD_Data)
{

    fee_PTDSizes_t *PTDSizes;

    uint16_t ParameterAux16 = 0;
    size_t PixelRowIt = 0, CCDIt = 0, DarkIt = 0,
           PixelDataIt = 0, SmearRowIt = 0, OverScanRowIt = 0,
           SmearIt = 0, VoltageRefIt = 0, RowIndex = 0 , ColumnIndex = 0;;

    size_t TotalColumns = 0;

    DeserializationInfo_t PTD_DeserializationInfo;

    PTDSizes = &PTD_Data->PTDSizes;

    if (fee_Calculate_PTD_Sizes(TmInformation, PTDSizes, &PTD_Data->PTDImageMatrixTotalSizes) != FEE_EXIT_SUCCESS)
    {
        return FEE_EXIT_ERROR;
    }

    TotalColumns = PTD_Data->PTDImageMatrixTotalSizes.ImageTotalColumns;

    /*Initialize PTD Desiarilazation Information*/
    PTD_DeserializationInfo.Message = PixelDataPacket;
    PTD_DeserializationInfo.max_length_Message = PTDSizes->DataPacketTotalBytes;
    PTD_DeserializationInfo.byte_counter = 0;

    /*ReadPixelDataCounter*/
    if (DeserializeParameter(&PTD_DeserializationInfo, &PTD_Data->PIXEL_DATA_COUNTER, sizeof(PTD_Data->PIXEL_DATA_COUNTER)) != FEE_EXIT_SUCCESS)
    {
        return FEE_EXIT_ERROR;
    }

    /*Initialize RowIndex*/
    RowIndex = 0;
    /*Store the data pixel in the PTD_Data->ImageMatrix*/
    for (PixelRowIt = 0; PixelRowIt < PTDSizes->NumDataRows; PixelRowIt++, RowIndex++)
    {

        /*Read Row Dark Info and store it at the left side of the data image*/
        for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
        {
            for (DarkIt = 0; DarkIt < NUM_DARK_INFO_PER_ROW; DarkIt++)
            {
                if (DeserializeParameter(&PTD_DeserializationInfo, &ParameterAux16, BYTES_PTD_PARAMETERS) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }

                ColumnIndex = DarkIt;
                PTD_Data->ImageMatrix[CCDIt][fee_PTDImageIndx(RowIndex, ColumnIndex, TotalColumns)] = ParameterAux16;
            }
        }

        /*Store the data pixel information after the dark info*/
        for (PixelDataIt = 0;
             PixelDataIt*FEE_NUM_CCD < (PTDSizes->NumDataParametersPerRow_EveryCDD - FEE_NUM_CCD * NUM_DARK_INFO_PER_ROW);
             PixelDataIt ++)
        {
            for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
            {
                if (DeserializeParameter(&PTD_DeserializationInfo, &ParameterAux16, BYTES_PTD_PARAMETERS) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }

                ColumnIndex = PixelDataIt + NUM_DARK_INFO_PER_ROW;
                PTD_Data->ImageMatrix[CCDIt][fee_PTDImageIndx(RowIndex,ColumnIndex, TotalColumns)] = ParameterAux16;
            }
        }
    }

    /*Read Smear Information*/
    for (SmearRowIt = 0; SmearRowIt < FEE_NUM_SMEAR_ROWS; SmearRowIt++, RowIndex++)
    {

        /*Set to 0 dark info. There is no dark info in smear info*/
        for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
        {
            for (DarkIt = 0; DarkIt < NUM_DARK_INFO_PER_ROW; DarkIt++)
            {
                PTD_Data->ImageMatrix[CCDIt][fee_PTDImageIndx(RowIndex, DarkIt, TotalColumns)] = 0;
            }
        }

        for (SmearIt = 0; 
             SmearIt*FEE_NUM_CCD < (PTDSizes->NumDataParametersPerRow_EveryCDD - FEE_NUM_CCD * NUM_DARK_INFO_PER_ROW); 
             SmearIt ++)
        {
            for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
            {
                if (DeserializeParameter(&PTD_DeserializationInfo, &ParameterAux16, BYTES_PTD_PARAMETERS) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }

                ColumnIndex = SmearIt + NUM_DARK_INFO_PER_ROW;
                PTD_Data->ImageMatrix[CCDIt][fee_PTDImageIndx(RowIndex,ColumnIndex, TotalColumns)] = ParameterAux16;
            }
        }
    }

    /*Store the over-scan info below smear info*/
    for (OverScanRowIt = 0; OverScanRowIt < PTDSizes->NumOverScanRows; OverScanRowIt++, RowIndex++)
    {
        /*Read OverScan Dark Info and store it at the left side of the data image*/
        for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
        {
            for (DarkIt = 0; DarkIt < NUM_DARK_INFO_PER_ROW; DarkIt++)
            {

                if (DeserializeParameter(&PTD_DeserializationInfo, &ParameterAux16, BYTES_PTD_PARAMETERS) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }

                ColumnIndex = DarkIt;
                PTD_Data->ImageMatrix[CCDIt][fee_PTDImageIndx(RowIndex, ColumnIndex, TotalColumns)] = ParameterAux16;
            }
        }

        /*Store the over data pixel information after the dark info*/
        for (PixelDataIt = 0; 
             PixelDataIt*FEE_NUM_CCD < (PTDSizes->NumDataParametersPerRow_EveryCDD - FEE_NUM_CCD * NUM_DARK_INFO_PER_ROW); 
             PixelDataIt ++)
        {
            for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
            {
                if (DeserializeParameter(&PTD_DeserializationInfo, &ParameterAux16, BYTES_PTD_PARAMETERS) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }

                ColumnIndex = PixelDataIt + NUM_DARK_INFO_PER_ROW;
                PTD_Data->ImageMatrix[CCDIt][fee_PTDImageIndx(RowIndex,ColumnIndex , TotalColumns)] = ParameterAux16;
            }
        }
    }
 
    /*Check ImageIndx size*/
    if ((fee_PTDImageIndx(RowIndex -1, ColumnIndex, TotalColumns) + 1) !=
        PTD_Data->PTDImageMatrixTotalSizes.ImageTotalRows *   PTD_Data->PTDImageMatrixTotalSizes.ImageTotalColumns){
        return FEE_EXIT_ERROR;
    }

    /*Store in a vector the Voltage Reference Info*/
    for (VoltageRefIt = 0; VoltageRefIt < NUM_VOLTAGE_REF_INFO; VoltageRefIt++)
    {
        if (DeserializeParameter(&PTD_DeserializationInfo, &ParameterAux16, BYTES_PTD_PARAMETERS) != FEE_EXIT_SUCCESS)
        {
            return FEE_EXIT_ERROR;
        }
        PTD_Data->VOLTAGES_REFERENCES[VoltageRefIt] = ParameterAux16;
    }

    //Add checksum size
    PTD_DeserializationInfo.byte_counter = PTD_DeserializationInfo.byte_counter + PTD_CHECKSUM_BYTES; 

    /*Verify that the packet length is correct*/
    if (PTD_DeserializationInfo.byte_counter != PTD_DeserializationInfo.max_length_Message)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}

/*TBD Cambiar las descripciones*/
int fee_PTD_Write(fee_TM_t TmInformation, fee_PTD_t PTD_Data, uint8_t *PixelDataPacket)
{

    fee_PTDSizes_t *PTDSizes;

    uint16_t ParameterAux16 = 0, CalculatedChecksum = 0;
    size_t PixelRowIt = 0, CCDIt = 0, DarkIt = 0,
           PixelDataIt = 0, SmearRowIt = 0, OverScanRowIt = 0,
           SmearIt = 0, VoltageRefIt = 0, RowCounter = 0;

    size_t TotalColumns = 0;
    size_t byte_counter = 0;

    PTDSizes = &PTD_Data.PTDSizes;

    if (fee_Calculate_PTD_Sizes(TmInformation, PTDSizes, &PTD_Data.PTDImageMatrixTotalSizes) != FEE_EXIT_SUCCESS)
    {
        return FEE_EXIT_ERROR;
    }

    TotalColumns = PTD_Data.PTDImageMatrixTotalSizes.ImageTotalColumns;;

    /*WritePixelDataCounter*/
    if (SerializeParameter(&PTD_Data.PIXEL_DATA_COUNTER, sizeof(PTD_Data.PIXEL_DATA_COUNTER),
                           &byte_counter, PixelDataPacket, PTDSizes->DataPacketTotalBytes) != FEE_EXIT_SUCCESS)
    {
        return FEE_EXIT_ERROR;
    }

    /*Initialize RowCounter*/
    RowCounter = 0;
    /*Read thte the PTDSizes.ImageMatrix and fill the packet*/
    for (PixelRowIt = 0; PixelRowIt < PTDSizes->NumDataRows; PixelRowIt++, RowCounter++)
    {

        /*Fill the dark info*/
        for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
        {
            for (DarkIt = 0; DarkIt < NUM_DARK_INFO_PER_ROW; DarkIt++)
            {
                ParameterAux16 = PTD_Data.ImageMatrix[CCDIt][fee_PTDImageIndx(RowCounter, DarkIt, TotalColumns)];

                if (SerializeParameter(&ParameterAux16, BYTES_PTD_PARAMETERS,
                                       &byte_counter, PixelDataPacket, PTDSizes->DataPacketTotalBytes) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }
            }
        }

        /*Fill the data pixel information after the dark info*/
        for (PixelDataIt = 0;
             PixelDataIt * FEE_NUM_CCD < (PTDSizes->NumDataParametersPerRow_EveryCDD - FEE_NUM_CCD * NUM_DARK_INFO_PER_ROW);
             PixelDataIt++)
        {
            for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
            {
                ParameterAux16 = PTD_Data.ImageMatrix[CCDIt][fee_PTDImageIndx(RowCounter, PixelDataIt + NUM_DARK_INFO_PER_ROW, TotalColumns)];

                // ParameterAux16 =0;
                if (SerializeParameter(&ParameterAux16, BYTES_PTD_PARAMETERS,
                                       &byte_counter, PixelDataPacket, PTDSizes->DataPacketTotalBytes) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }
            }
        }
    }

    /*Fill the Smear Information*/
    for (SmearRowIt = 0; SmearRowIt < FEE_NUM_SMEAR_ROWS; SmearRowIt++, RowCounter++)
    {
        for (SmearIt = 0; 
             SmearIt *FEE_NUM_CCD < (PTDSizes->NumDataParametersPerRow_EveryCDD - FEE_NUM_CCD * NUM_DARK_INFO_PER_ROW); 
             SmearIt++ )
        {
            for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
            {

                ParameterAux16 = PTD_Data.ImageMatrix[CCDIt][fee_PTDImageIndx(RowCounter, SmearIt + NUM_DARK_INFO_PER_ROW, TotalColumns)];
                
                if (SerializeParameter(&ParameterAux16, BYTES_PTD_PARAMETERS,
                                       &byte_counter, PixelDataPacket, PTDSizes->DataPacketTotalBytes) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }
            }
        }
    }

    /*Store the over-scan info below smear info*/
    for (OverScanRowIt = 0; OverScanRowIt < PTDSizes->NumOverScanRows; OverScanRowIt++, RowCounter++)
    {
        /*OverScan Dark Info is at the left side of the data image*/
        for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
        {
            for (DarkIt = 0; DarkIt < NUM_DARK_INFO_PER_ROW; DarkIt++)
            {

                ParameterAux16 = PTD_Data.ImageMatrix[CCDIt][fee_PTDImageIndx(RowCounter, DarkIt, TotalColumns)];

                if (SerializeParameter(&ParameterAux16, BYTES_PTD_PARAMETERS,
                                       &byte_counter, PixelDataPacket, PTDSizes->DataPacketTotalBytes) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }
            }
        }

        /*Store the over data pixel information after the dark info*/
        for (PixelDataIt = 0; 
             PixelDataIt * FEE_NUM_CCD < (PTDSizes->NumDataParametersPerRow_EveryCDD - FEE_NUM_CCD * NUM_DARK_INFO_PER_ROW); 
             PixelDataIt ++)
        {
            for (CCDIt = 0; CCDIt < FEE_NUM_CCD; CCDIt++)
            {
                ParameterAux16 = PTD_Data.ImageMatrix[CCDIt][fee_PTDImageIndx(RowCounter, PixelDataIt + NUM_DARK_INFO_PER_ROW, TotalColumns)];

                if (SerializeParameter(&ParameterAux16, BYTES_PTD_PARAMETERS,
                                       &byte_counter, PixelDataPacket, PTDSizes->DataPacketTotalBytes) != FEE_EXIT_SUCCESS)
                {
                    return FEE_EXIT_ERROR;
                }
            }
        }
    }

    /*Fill the packet with the Voltage Reference Info*/
    for (VoltageRefIt = 0; VoltageRefIt < NUM_VOLTAGE_REF_INFO; VoltageRefIt++)
    {

        ParameterAux16 = PTD_Data.VOLTAGES_REFERENCES[VoltageRefIt];

        if (SerializeParameter(&ParameterAux16, BYTES_PTD_PARAMETERS,
                               &byte_counter, PixelDataPacket, PTDSizes->DataPacketTotalBytes) != FEE_EXIT_SUCCESS)
        {
            return FEE_EXIT_ERROR;
        }
    }

    /*Calculate checksum*/
    CalculatedChecksum = XORChecksum16(PixelDataPacket, byte_counter);
    /*Serialize checksum. Edianess conversion is not necessary*/
    if (SerializeParameter_NoEndianessConversion(&CalculatedChecksum, BYTES_PTD_PARAMETERS,
                           &byte_counter, PixelDataPacket, PTDSizes->DataPacketTotalBytes) != FEE_EXIT_SUCCESS)
    {
        return FEE_EXIT_ERROR;
    }

    /*Verify that the packet length is correct*/
    if (byte_counter != PTDSizes->DataPacketTotalBytes)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}



int fee_CheckPTDChecksum(fee_TM_Packet_t PTD_Packet, fee_PTDSizes_t PTDSizes){

    uint16_t ReadedChecksum = 0;
    uint16_t CalculatedChecksum = 0;

    /*Read checksum*/
    memcpy(&ReadedChecksum, PTD_Packet + (PTDSizes.DataPacketTotalBytes - PTD_CHECKSUM_BYTES), PTD_CHECKSUM_BYTES) ;
    
    /*Calcualte checksum*/
    CalculatedChecksum = XORChecksum16(PTD_Packet, PTDSizes.DataPacketTotalBytes - TM_CHECKSUM_BYTES);

    /*Compare both checksums*/
    if (CalculatedChecksum != ReadedChecksum)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}
