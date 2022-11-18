/**
 * @file fee.h
 * @author David Rodríguez Muñoz (david.rodriguez@iac.es)
 * @brief Library designed to serialized and deserialized fee electronics messages.
 * @version 0
 * @date 2022-03-22
 *
 * @copyright Instuto de Astrofísica de Canarias (IAC)
 *
 */

#ifndef FEE_H
#define FEE_H

#include <stdint.h>
#include <stddef.h>

/*************************/
/*       Consts          */
/*************************/

/**
 * \defgroup Constants
 * @{
 */

#define FEE_EXIT_SUCCESS 0
#define FEE_EXIT_ERROR -1
/*Data packets Bytes size*/
#define TC_PACKET_BYTES 75
#define TM_PACKET_BYTES 140

/*TM (HC signals) register ranges*/
#define TM_HC_SIGNAL_MIN 0
#define TM_HC_SIGNAL_MAX 65520

/*NUMBER OF CCD*/
#define FEE_NUM_CCD 2 /*Number of different CCD*/

/*Number of smear rows of the PTD Image*/
#define FEE_NUM_SMEAR_ROWS 2        /*Number of smear Rows*/

/*TC register ranges*/
#define TC_COUNTER_MAX 65535
#define TC_COUNTER_MIN 0

#define TC_OPMODE_MAX 2
#define TC_OPMODE_MIN 0

#define TC_EXPO_TIME_MAX 12000000
#define TC_EXPO_TIME_MIN 400

#define TC_DUOUTDRAINTVLTG_MAX 255
#define TC_DUOUTDRAINTVLTG_MIN 0

#define TC_DURESETVLTG_MAX 255
#define TC_DURESETVLTG_MIN 0

#define TC_DUDUMPVLTG_MAX 255
#define TC_DUDUMPVLTG_MIN 0

#define TC_DUOUTGATEVLTG_MAX 255
#define TC_DUOUTGATEVLTG_MIN 0

#define TC_DUIMGCKHVLTG_MAX 255
#define TC_DUIMGCKHVLTG_MIN 0

#define TC_DUSTGCKHVLTG_MAX 255
#define TC_DUSTGCKHVLTG_MIN 0

#define TC_DUREGCKHVLTG_MAX 255
#define TC_DUREGCKHVLTG_MIN 0

#define TC_DUDUMPCKHVLTG_MAX 255
#define TC_DUDUMPCKHVLTG_MIN 0

#define TC_DURESETCKHVLTG_MAX 255
#define TC_DURESETCKHVLTG_MIN 0

#define TC_NBSMEAR_MAX 255
#define TC_NBSMEAR_MIN 0

#define TC_WOISTART_MAX 1023
#define TC_WOISTART_MIN 0

#define TC_WOISIZE_MAX 536
#define TC_WOISIZE_MIN 0

#define TC_SPATIALBINNINGMODE_MAX 1
#define TC_SPATIALBINNINGMODE_MIN 0

#define TC_FTPTIME_MAX 255
#define TC_FTPTIME_MIN 0

#define TC_IMGSTGCKRFTIME_MAX 50
#define TC_IMGSTGCKRFTIME_MIN 0

#define TC_IMGSTGCKOVTIME_MAX 50
#define TC_IMGSTGCKOVTIME_MIN 0

#define TC_IMGSTGCKPWTIME_MAX 80
#define TC_IMGSTGCKPWTIME_MIN 0

#define TC_REGLINADVTIME_MAX 255
#define TC_REGLINADVTIME_MIN 0

#define TC_LINADVREGTIME_MAX 255
#define TC_LINADVREGTIME_MIN 0

#define TC_RCKPTIME_MAX 255
#define TC_RCKPTIME_MIN 0

#define TC_REGCKOVTIME_MAX 50
#define TC_REGCKOVTIME_MIN 0

#define TC_R1REGCKONTIME_MAX 255
#define TC_R1REGCKONTIME_MIN 0

#define TC_R3REGCKONTIME_MAX 255
#define TC_R3REGCKONTIME_MIN 0

#define TC_R2CKRISEDELTIME_MAX 50
#define TC_R2CKRISEDELTIME_MIN 0

#define TC_RESETCKONTIME_MAX 50
#define TC_RESETCKONTIME_MIN 3

#define TC_RESETCKFALLDELTIME_MAX 50
#define TC_RESETCKFALLDELTIME_MIN 0

#define TC_ADC1TIME_MAX 255
#define TC_ADC1TIME_MIN 0

#define TC_ADC2TIME_MAX 255
#define TC_ADC2TIME_MIN 0

#define TC_ADC1RDDLY_MAX 255
#define TC_ADC1RDDLY_MIN 0

#define TC_ADC2RDDLY_MAX 255
#define TC_ADC2RDDLY_MIN 0

#define TC_DULAMBDA_MAX 449
#define TC_DULAMBDA_MIN 0

#define TC_FREQBINNINGBAND_1_BINNINGSIZE_MAX 7
#define TC_FREQBINNINGBAND_1_BINNINGSIZE_MIN 0
#define TC_FREQBINNINGBAND_1_BANDSIZE_MAX 450
#define TC_FREQBINNINGBAND_1_BANDSIZE_MIN 0

#define TC_FREQBINNINGBAND_2_BINNINGSIZE_MAX 7
#define TC_FREQBINNINGBAND_2_BINNINGSIZE_MIN 0
#define TC_FREQBINNINGBAND_2_BANDSIZE_MAX 450
#define TC_FREQBINNINGBAND_2_BANDSIZE_MIN 0

#define TC_FREQBINNINGBAND_3_BINNINGSIZE_MAX 7
#define TC_FREQBINNINGBAND_3_BINNINGSIZE_MIN 0
#define TC_FREQBINNINGBAND_3_BANDSIZE_MAX 450
#define TC_FREQBINNINGBAND_3_BANDSIZE_MIN 0

#define TC_FREQBINNINGBAND_4_BINNINGSIZE_MAX 7
#define TC_FREQBINNINGBAND_4_BINNINGSIZE_MIN 0
#define TC_FREQBINNINGBAND_4_BANDSIZE_MAX 450
#define TC_FREQBINNINGBAND_4_BANDSIZE_MIN 0

#define TC_FREQBINNINGBAND_5_BINNINGSIZE_MAX 7
#define TC_FREQBINNINGBAND_5_BINNINGSIZE_MIN 0
#define TC_FREQBINNINGBAND_5_BANDSIZE_MAX 450
#define TC_FREQBINNINGBAND_5_BANDSIZE_MIN 0

#define TC_PIXEL_MIN_MAX 65535
#define TC_PIXEL_MIN_MIN 0

#define TC_PIXEL_MAX_MAX 65535
#define TC_PIXEL_MAX_MIN 0

#define TC_CDSPARAMS_MODE_MAX 2
#define TC_CDSPARAMS_MODE_MIN 0

#define TC_CDSPARAMS_DIGITAL_OFFSET_MAX 1023
#define TC_CDSPARAMS_DIGITAL_OFFSET_MIN 0

#define TC_HCNBSAMPLE_MAX 16
#define TC_HCNBSAMPLE_MIN 1

#define TC_NBTAIL_MAX 1023
#define TC_NBTAIL_MIN 0

#define TC_ACQSTARTDELAY_MAX 7
#define TC_ACQSTARTDELAY_MIN 0

/**@}*/

/* --------------------- */
/* ---- Data types ---- */
/* --------------------- */

/**
 * \defgroup DataTypes
 * @{
 */

typedef uint8_t fee_TC_Packet_t[TC_PACKET_BYTES];
typedef uint8_t fee_TM_Packet_t[TM_PACKET_BYTES];

typedef enum
{
    OPMODE_SAFE = 0,
    OPMODE_STAND_BY = 1,
    OPMODE_OPERATIONAL = 2
} op_mode_t;

#define FEE_OPMODE_BYTESIZE 2

typedef enum
{
    SPATALBIN_NOTENABLE = 0,
    SPATIALBIN_ENABLE = 1

} spatialbinning_t;

#define FEE_SPATIALBINNING_BYTESIZE 2

typedef enum
{
    NO_SYNTHETIC_PATTERN = 0,
    SYNTHETIC_PATTERN_1 = 240,
    SYNTHETIC_PATTERN_2 = 241
    
} synpattern_t;

#define FEE_SYNPATTERN_BYTESIZE 2

typedef enum
{
    DEFAULT_CDS = 0,
    REFERENCE_LEVEL_CDS = 1,
    VIDEO_LEVEL_CDS = 2

} cds_params_t;

#define FEE_CDSPARAMS_BYTESIZE 2

/*
TC Packet Error Masks
15: Wrong SpW Destination Address;
14: TC wrong length;
13: TC Counter error;
12: CHECKSUM error;
11: Wrong value in a TC packet field or out-of-range value in a TC packet field;
10: TC received or in a wrong time window;
9: More than one TC received in an ACQSTART vperiod;
8: No TC received in an ACQSTART period;
7: TC Buffer EDAC error
6: SpW Disconnection error
5: SpW Parity error
4: SpW Escape Sequence error
3: SpW Character Sequence error
2: SpW Credit error
1..0: Not used
*/
typedef enum
{

    TC_ERROR_Wrong_SpwDestination_Address = 0x8000,
    TC_ERROR_TC_wrong_length = 0x4000,
    TC_ERROR_TC_Counter_error = 0x2000,
    TC_ERROR_CHECKSUM_error = 0x1000,
    TC_ERROR_Wrong_value_in_a_TCpacketField_or_out_of_range = 0x0800,
    TC_ERROR_TC_received_or_in_a_wrong_time_window = 0x0400,
    TC_ERROR_More_than_one_TC_received_in_an_ACQSTART_period = 0x0200,
    TC_ERROR_No_TC_received_in_an_ACQSTART_period = 0x0100,
    TC_ERROR_TC_Buffer_Edac_error = 0x0080,
    TC_ERROR_SpW_Disconnection_error = 0x0040,
    TC_ERROR_SpW_Parity_error = 0x0020,
    TC_ERROR_SpW_Escape_Sequence_error = 0x0010,
    TC_ERROR_SpW_Character_Sequence_error = 0x0008,
    TC_ERROR_SpW_Credit_error = 0x0004,

} fee_TC_Error_t;

/*
VAU Application Level Error MASKs
15: ACQSTART_ERROR
14: PIXEL_TM_ERROR; Interruption of Pixel Packet
13: HC_ACQ_ERROR; Interruption of HC acquisition
12: TC_EXEC_ERROR; Interrruption of TC execution
11: VAU_TASKS_ERROR; Interruption of VAU
tasks
10: SEFI error
9: PIXEL_BUFFER_OVERFLOW
8..0: Not used
*/

typedef enum
{

    VAU_ERROR_ACQSTART_ERROR = 0x8000,
    VAU_ERROR_PIXEL_TM_ERROR = 0x4000,
    VAU_ERROR_HC_ACQ_ERROR = 0x2000,
    VAU_ERROR_TC_EXEC_ERROR = 0x1000,
    VAU_ERROR_VAU_TASKS_ERROR = 0x0800,
    VAU_ERROR_SEFI_ERROR = 0x0400,
    VAU_ERROR_PIXEL_BUFFER_OVERFLOW = 0x0200,

} fee_VAU_Error_t;

typedef struct
{

    uint16_t TC_COUNTER;
    op_mode_t OPMODE; /*16Bits*/
    uint32_t EXPO_TIME;
    /*4.Spare 8 bits*/
    uint8_t DUOUTDRAINTVLTG;
    uint8_t DURESETVLTG;
    uint8_t DUDUMPVLTG;
    uint8_t DUOUTGATEVLTG;
    uint8_t DUIMGCKHVLTG;
    uint8_t DUSTGCKHVLTG;
    uint8_t DUREGCKHVLTG;
    uint8_t DUDUMPCKHVLTG;
    uint8_t DURESETCKHVLTG;
    uint16_t NBSMEAR;
    uint16_t WOISTART;
    uint16_t WOISIZE;
    spatialbinning_t SPATIALBINNINGMODE; /*16Bits*/
    uint8_t FTPTIME;
    uint8_t IMGSTGCKRFTIME;
    uint8_t IMGSTGCKOVTIME;
    uint8_t IMGSTGCKPWTIME;
    uint8_t REGLINADVTIME;
    uint8_t LINADVREGTIME;
    uint8_t RCKPTIME;
    uint8_t REGCKOVTIME;
    uint8_t R1REGCKONTIME;
    uint8_t R3REGCKONTIME;
    uint8_t R2CKRISEDELTIME;
    uint8_t RESETCKONTIME;
    uint8_t RESETCKFALLDELTIME;
    uint8_t ADC1TIME;
    uint8_t ADC2TIME;
    uint8_t ADC1RDDLY;
    uint8_t ADC2RDDLY;
    uint16_t DULAMBDA;
    uint16_t FREQBINNINGBAND_1;
    uint16_t FREQBINNINGBAND_2;
    uint16_t FREQBINNINGBAND_3;
    uint16_t FREQBINNINGBAND_4;
    uint16_t FREQBINNINGBAND_5;
    uint16_t PIXEL_MIN;
    uint16_t PIXEL_MAX;
    synpattern_t SYNTPATTERN; /*16Bits*/
    cds_params_t CDSPARAMS;   /*16Bits*/
    uint16_t HCNBSAMPLE;
    uint16_t NBTAIL;
    uint16_t ACQSTARTDELAY;

} fee_TC_t; /* TC_DataStruct */

typedef struct
{

    uint32_t TM_COUNTER;
    fee_TC_t Returned_TC;
    uint16_t CCDTEMP_MEAS1;
    uint16_t CCDTEMP_MEAS2;
    uint16_t VAUTEMP_MEAS;
    uint16_t FPPETEMP_MEAS;
    uint16_t VODE_MEAS;
    uint16_t VODF_MEAS;
    uint16_t VODG_MEAS;
    uint16_t VODH_MEAS;
    uint16_t VRD_MEAS;
    uint16_t VDD_MEAS;
    uint16_t VOG_MEAS;
    uint16_t IPHIH_MEAS;
    uint16_t SPHIH_MEAS;
    uint16_t RPHIH_MEAS;
    uint16_t PHIRH_MEAS;
    uint16_t VDGH_MEAS;
    uint16_t VANAP_MEAS;
    uint16_t VANAN_MEAS;
    uint16_t VDET_MEAS;
    uint16_t VDRV_MEAS;
    uint16_t VDIG_MEAS;
    uint16_t IDIG_MEAS;
    uint16_t TC_ERROR;
    uint16_t VAU_ERROR;

} fee_TM_t; /* TM_DataStruct */

typedef struct
{

    float CCDTEMP_MEAS1_f;
    float CCDTEMP_MEAS2_f;
    float VAUTEMP_MEAS_f;
    float FPPETEMP_MEAS_f;
    float VODE_MEAS_f;
    float VODF_MEAS_f;
    float VODG_MEAS_f;
    float VODH_MEAS_f;
    float VRD_MEAS_f;
    float VDD_MEAS_f;
    float VOG_MEAS_f;
    float IPHIH_MEAS_f;
    float SPHIH_MEAS_f;
    float RPHIH_MEAS_f;
    float PHIRH_MEAS_f;
    float VDGH_MEAS_f;
    float VANAP_MEAS_f;
    float VDET_MEAS_f;
    float VANAN_MEAS_f;
    float VDRV_MEAS_f;
    float VDIG_MEAS_f;
    float IDIG_MEAS_f;

} fee_TM_Float_t;

typedef struct {
    
    size_t NumDataRows;                       /*Number of Data information rows in the PTD packet*/
    size_t NumOverScanRows;                   /*Number of Over Scan rows rows in the PTD packet*/
    size_t NumSmearRows;                      /*Number of Over SmearRows in the PTD packet. This parameter is constant*/  
    size_t NumDataParametersPerRow_EveryCDD;  /*Number of parameters per row of information data for every CCD (the parameter is multipled by FEE_NUM_CCD). 
                                                It applies to Information data and and OverScan data. 
                                                It considers the dark info.
                                                */
    size_t NumSmearParameters_EveryCCD;       /*Number of parameters of the SmearInformation. Smear information does not contain dark info*/
    size_t NumDarkInfoPerRow_EveryCCD;        /*Number of parameters with dark info per row (For Data and OverScan) considering every 
                                                ccds (the parameter is multipled by FEE_NUM_CCD). This parameter is constant */
    size_t DataPacketTotalBytes;              /*Number of bytes of the Data Packet */
                                              /* DataPacketTotalBytes = PixelDataCounterBytes + DataInformationBytes                                                               
                                                               + SmearInfoBytes +OverscanInfoBytes 
                                                               + VoltageRefInfoBytes + checksum bytes */

} fee_PTDSizes_t;

typedef struct{
    size_t ImageMatrixBytes;         /*Size of a generated ImageMatrix (fee_PTD_t) with the sizes parameters 16(bits)*NumDataRows*TotalRows */
                                     /*Memory of the ImageMatrix variable should be reserved for, at least, ImageMatrixBytes bytes for each CDD*/
    size_t ImageTotalRows;           /*Total of Rows of the ImageMatrix Variable. ImageTotalRows = NumSmearRows + NumOverScanRows + NumDataRows*/
    size_t ImageTotalColumns;        /*Total of Columns of the ImageMatrix Variable*/
} fee_ImageMatrixTotalSizes_t;


/**
 * Structure ot the deserialized PTD information (ImageMatrix). 
 *     
 * 
 * DarkInfo(Left)   DarkInfo(Right)        | Pixel Information (Linea 1)
 * DarkInfo(Left)   DarkInfo(Right)        | Pixel Information (Linea 2)
 *                              ........
 *                              ........
 *  0             0                        |  SmearInformation (Linea 1)
 *  0             0                        |  SmearInformation (Linea 2)
 *                              ........
 *                              ........
 * DarkOverScan(Left) DarkOverScan(Right)  | Over Scan Information (Linea 1)
 * DarkOverScan(Left) DarkOverScan(Right)  | Over Scan Information (Linea 1)
 * 
 */
typedef struct
{
    uint32_t PIXEL_DATA_COUNTER;           /*Counter of each Pixel Packet*/
    uint16_t VOLTAGES_REFERENCES[4];       /*Voltage References*/
    uint16_t *ImageMatrix[FEE_NUM_CCD];    /*Stored image. Memory should be reserved for, at least, PTDImageMatrixTotalSizes.ImageMatrixBytes bytes for each CCD*/
    fee_PTDSizes_t PTDSizes;          /*Sizes of the PTD Packet*/
    fee_ImageMatrixTotalSizes_t   PTDImageMatrixTotalSizes;               /*Sizes of the PTD Packet*/
} fee_PTD_t;

/**@}*/

/* ---------------------------- */
/* ---- Public Functions ------ */
/* ---------------------------- */

/**
 * \defgroup Global Funcitons
 * @{
 */

/**
 * @brief Function that generates the TC packet with a given information structure.
 *
 * @param TC_Data_Struct [Input] Structure with the TC information to be insterted in the TC Packet.
 * @param TC_Packet [Output] Generated TC Packet.
 * @return int - The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 *
 */
int fee_TC_Write(fee_TC_t TC_Data_Struct, fee_TC_Packet_t TC_Packet);

/**
 * @brief The fuction deserelized the information of a TC Packet and store it in a stuctre.
 *
 * @param TC_Packet [Input] TC Packet to be deserialized
 * @param TC_Data_Struct [Output] TM information structure filled with the TC Packet information
 * @return int - The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int fee_TC_Read(fee_TC_Packet_t TC_Packet, fee_TC_t *TC_Data_Struct);

/**
 * @brief Function that checks the integrity checksum of a TC packet
 * 
 * @param TC_Packet [Input] Telecommand packet
 * @return int - The function returns FEE_EXIT_SUCCES if the checksum is correct and FEE_EXIT_ERROR in case the TM message checksum 
 * diffieres by the one calculated by this library. 
 */
int fee_CheckTeleCommandChecksum(fee_TC_Packet_t TC_Packet);

/**
 * @brief The function checks if the TC information is correctly bounded.
 *
 * @param TC_Data_Struct [Input] TC Data information structure.
 * @return int - The function returns FEE_EXIT_SUCCESS if the information is correclty bounded. Otherwise, FEE_EXIT_ERROR wil be returned.
 */
int fee_TC_BoundsCheck(fee_TC_t TC_Data_Struct);

/**
 * @brief The fuction deserelized the information of a TM Packet and store it in a stuctre.
 *
 * @param TM_Packet [Input] TM Packet to be deserialized
 * @param TM_Data_Struct [Output] TM information structure filled with the TM Packet information
 * @return int - The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int fee_TM_Read(fee_TM_Packet_t TM_Packet, fee_TM_t *TM_Data_Struct);

/**
 * @brief Function that serialize the TM information to generate a TM packet.
 *
 * @param TM_Data_Struct [Input] Structure with the TM information to be insterted in the TM Packet
 * @param TM_Packet [Output] Generated TM Packet
 * @return int - The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int fee_TM_Write(fee_TM_t TM_Data_Struct, fee_TM_Packet_t TM_Packet);

/**
 * @brief Function that checks the integrity checksum of a TM packet
 * 
 * @param TM_Packet [Input] Telemetry packet
 * @return int - The function returns FEE_EXIT_SUCCES if the checksum is correct and FEE_EXIT_ERROR in case the TM message checksum 
 * diffieres by the one calculated by this library. 
 */
int fee_CheckTelemetryChecksum(fee_TM_Packet_t TM_Packet);

/**
 * @brief Convert the telemetry index parameters to physical parameters
 *
 * @param TM_Data_Struct_Index [Input] Structure of the TM index parameters
 * @param TM_DATA_F  [Ouptut] Structure with the converted parameters.
 * @return int The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int fee_convert_TM_parameters(fee_TM_t TM_Data_Struct_Index, fee_TM_Float_t *TM_DATA_F);

/**
 * @brief Function that deserialize the Pixel Data Packet (PTD). 
 *
 * @param PixelDataPacket [Input] Pixel data packet to be deserialized
 * @param TmInformation [Input] TM information structure needed to read the PixelDataPacket. 
 * @param PTD_Data [Output] Deserealized pixel data packet structure.
 * @return int - The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int fee_PTD_Read(uint8_t *PixelDataPacket, fee_TM_t TmInformation, fee_PTD_t *PTD_Data);

/**
 * @brief  Function that serialize the Pixel Data Packet (PTD)
 *
 * @param TmInformation [Input] TM information structure needed to generate the PixelDataPacket. 
 * @param PTD_Data [Input] PTD information to be serialize. 
 * @param PixelDataPacket [Oputut] Pixel data packet to be deserialized generated. 
 * @return int
 */
int fee_PTD_Write(fee_TM_t TmInformation, fee_PTD_t PTD_Data, uint8_t *PixelDataPacket);

/**
 * @brief
 *
 * @param TmInformation [Input] TM information structure
 * @param PTDSizes  [Output] Struct with size information of the PTD packet
 * @param ImageMatrixSizes [Output] Struct with the maximum sizes of the PTD deserialized Image ImageMatrix
 * @return int - The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int fee_Calculate_PTD_Sizes(fee_TM_t TmInformation, fee_PTDSizes_t *PTDSizes, fee_ImageMatrixTotalSizes_t *ImageMatrixSizes);

/**
 * @brief Function that checks the integrity checksum of a PTD packet
 * 
 * @param PTD_Packet [Input] PTD packet
 * @param PTDSizes [Input] Structure with sizes information of the PTD packet
 * @return int - The function returns FEE_EXIT_SUCCES if the checksum is correct and FEE_EXIT_ERROR in case the TM message checksum 
 * diffieres by the one calculated by this library. 
 */
int fee_CheckPTDChecksum(fee_TM_Packet_t PTD_Packet, fee_PTDSizes_t PTDSizes);

/**
 * @brief Function tat gets the binninsize and bansize parameters from the freqbinningband paramer. 
 *  freqbinningband = binningsize [13:15]  spare [9:12] bandsize[0:8] where 0 is the LSB
 *  !Warning! The function returns a binningsize which offset value of 1 have been already applied. 
 *      *binninsize = ((freqbinningband >> 13) & 0x0007) + 1;
 * 
 * @param freqbinningband  [Input] Freqbinningg band parameter
 * @param binninsize_s  [Output] Parameter which indicates the binninsize applied to the band.
 * @param bandsize_s    [Output] Parameter which indicates the length (in pixels) of the band.
 */
void fee_getFreqBinningBand_parameters(uint16_t freqbinningband, uint16_t *binninsize_s, uint16_t *bandsize_s);

/**
 * @brief Function tat gets the digital_offset and cds_mode parameters from the freqbinningband paramer. 
 * 
 * @param cdsparam  [Input] CDS parameter. cdsparam = cds_param [14:15] spare [10,13] bandsize[0:9] where 0 is the LSB
 * @param cds_mode [Output] Defines if the FPGA apples :
 *   00: the default CDS
 *   01: The reference level
 *   10: The video level
 * @param digital_offset [Output] Defines the digital offste to be applied in the CDs
 */
void fee_getCDSParam_parameters(uint16_t cdsparam, uint16_t *cds_mode, uint16_t *digital_offset);

/**
 * @brief Function which helps to fill the 16 bits cds parameter.
 *  The CDS parameter should be form as follows : cdsparam = cds_mode [0:1] spare [2,5] bandsize[6:15]
 *
 * @param cds_mode [Input] Part of the CDS Parameter. Defines if the FPGA apples :
 *   00: the default CDS
 *   01: The reference level
 *   10: The video level
 * @param digital_offset [Input] Part of the CDS parameter. Defines the digital offste to be applied in the CDs
 * @return uint16_t The function returns the filled CDS parameter.
 */
uint16_t fee_fill_cdsparam_parameter(cds_params_t cds_mode, int digital_offset);

/**
 * @brief Function which helps to fill the 16 bits freqbinnindband parameters (1,2,3,4,5).
 * The CDS parameter should be form as follows : freqbinninbband = binningsize [0:2] spare [3,6] bandsize[7:15]
 * !Warning! The binningsize input parameter must be introduced without the offset applied, the function applies it before genereting the freqbinning band parameter. 
 *
 * @param binningsize [Input] Part of the freqbinningband parameter. Defines the number of pixel to be used by binning algorithm for the band
 * @param bandsize  [Input] Part of the freqbinninbband parameter. Defines the number of pixel in the band.
 * @return uint16_t The function return the filled freqbinningband parametrer.
 */
uint16_t fee_fill_freqbinningband_parameter(int binningsize, int bandsize);


/**@}*/

#endif
