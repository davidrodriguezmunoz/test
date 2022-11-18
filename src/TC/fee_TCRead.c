/**
 * @file fee_TCRead.c
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief Fee library deserialize telecommand packet functions.
 * @version 0.1
 * @date 2022-03-24
 *
 * @copyright Instuto de Astrofísica de Canarias (IAC)
 *
 */

#include <stdio.h>
#include <arpa/inet.h>
#include <fee.h>
#include "../common/fee_common.h"


int fee_TC_Read(fee_TC_Packet_t TC_Packet, fee_TC_t *TC_Data_Struct)
{

    DeserializationInfo_t TC_deserialization;
    /*Intermediate variables for the parameters that are enums*/
    uint16_t op_mode = 0;
    uint16_t spatialbinning_mode = 0;
    uint16_t cdsparams = 0;
    uint16_t synpattern = 0;

    TC_deserialization.Message = TC_Packet;
    TC_deserialization.max_length_Message = TC_PACKET_BYTES;
    TC_deserialization.byte_counter = 0;

    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->TC_COUNTER, sizeof(TC_Data_Struct->TC_COUNTER)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &op_mode, FEE_OPMODE_BYTESIZE))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->EXPO_TIME, sizeof(TC_Data_Struct->EXPO_TIME)))
    {
        return FEE_EXIT_ERROR;
    }

    /*Discard spare byte Index 5*/
    TC_deserialization.byte_counter = TC_deserialization.byte_counter + 1;

    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DUOUTDRAINTVLTG, sizeof(TC_Data_Struct->DUOUTDRAINTVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DURESETVLTG, sizeof(TC_Data_Struct->DURESETVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DUDUMPVLTG, sizeof(TC_Data_Struct->DUDUMPVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DUOUTGATEVLTG, sizeof(TC_Data_Struct->DUOUTGATEVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DUIMGCKHVLTG, sizeof(TC_Data_Struct->DUIMGCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DUSTGCKHVLTG, sizeof(TC_Data_Struct->DUSTGCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DUREGCKHVLTG, sizeof(TC_Data_Struct->DUREGCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DUDUMPCKHVLTG, sizeof(TC_Data_Struct->DUDUMPCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DURESETCKHVLTG, sizeof(TC_Data_Struct->DURESETCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->NBSMEAR, sizeof(TC_Data_Struct->NBSMEAR)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->WOISTART, sizeof(TC_Data_Struct->WOISTART)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->WOISIZE, sizeof(TC_Data_Struct->WOISIZE)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &spatialbinning_mode, FEE_SPATIALBINNING_BYTESIZE))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->FTPTIME, sizeof(TC_Data_Struct->FTPTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->IMGSTGCKRFTIME, sizeof(TC_Data_Struct->IMGSTGCKRFTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->IMGSTGCKOVTIME, sizeof(TC_Data_Struct->IMGSTGCKOVTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->IMGSTGCKPWTIME, sizeof(TC_Data_Struct->IMGSTGCKPWTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->REGLINADVTIME, sizeof(TC_Data_Struct->REGLINADVTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->LINADVREGTIME, sizeof(TC_Data_Struct->LINADVREGTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->RCKPTIME, sizeof(TC_Data_Struct->RCKPTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->REGCKOVTIME, sizeof(TC_Data_Struct->REGCKOVTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->R1REGCKONTIME, sizeof(TC_Data_Struct->R1REGCKONTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->R3REGCKONTIME, sizeof(TC_Data_Struct->R3REGCKONTIME)))
    {
        return FEE_EXIT_ERROR;
    }

    /*Discard spare byte Index 29*/
    TC_deserialization.byte_counter = TC_deserialization.byte_counter + 1;

    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->R2CKRISEDELTIME, sizeof(TC_Data_Struct->R2CKRISEDELTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->RESETCKONTIME, sizeof(TC_Data_Struct->RESETCKONTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->RESETCKFALLDELTIME, sizeof(TC_Data_Struct->RESETCKFALLDELTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->ADC1TIME, sizeof(TC_Data_Struct->ADC1TIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->ADC2TIME, sizeof(TC_Data_Struct->ADC2TIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->ADC1RDDLY, sizeof(TC_Data_Struct->ADC1RDDLY)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->ADC2RDDLY, sizeof(TC_Data_Struct->ADC2RDDLY)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->DULAMBDA, sizeof(TC_Data_Struct->DULAMBDA)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->FREQBINNINGBAND_1, sizeof(TC_Data_Struct->FREQBINNINGBAND_1)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->FREQBINNINGBAND_2, sizeof(TC_Data_Struct->FREQBINNINGBAND_2)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->FREQBINNINGBAND_3, sizeof(TC_Data_Struct->FREQBINNINGBAND_3)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->FREQBINNINGBAND_4, sizeof(TC_Data_Struct->FREQBINNINGBAND_4)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->FREQBINNINGBAND_5, sizeof(TC_Data_Struct->FREQBINNINGBAND_5)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->PIXEL_MIN, sizeof(TC_Data_Struct->PIXEL_MIN)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->PIXEL_MAX, sizeof(TC_Data_Struct->PIXEL_MAX)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &synpattern, FEE_SYNPATTERN_BYTESIZE))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &cdsparams, FEE_CDSPARAMS_BYTESIZE))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->HCNBSAMPLE, sizeof(TC_Data_Struct->HCNBSAMPLE)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->NBTAIL, sizeof(TC_Data_Struct->NBTAIL)))
    {
        return FEE_EXIT_ERROR;
    }

    if (DeserializeParameter(&TC_deserialization, &TC_Data_Struct->ACQSTARTDELAY, sizeof(TC_Data_Struct->ACQSTARTDELAY)))
    {
        return FEE_EXIT_ERROR;
    }

    /*Increase byte counter to discard spare bytes and discard the telecommand*/
    TC_deserialization.byte_counter += NUM_SPARE_BYTES_END_TELECOMMAND + TC_CHECKSUM_BYTES;

    /*Convert enum variables to uint16_t*/
    TC_Data_Struct->OPMODE = op_mode ;
    TC_Data_Struct->SPATIALBINNINGMODE = spatialbinning_mode;
    TC_Data_Struct->CDSPARAMS = cdsparams;
    TC_Data_Struct->SYNTPATTERN = synpattern;

    /*Verify that the packet length is correct*/
    if (TC_deserialization.byte_counter != TC_deserialization.max_length_Message)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}

void fee_getFreqBinningBand_parameters(uint16_t freqbinningband, uint16_t *binninsize, uint16_t *bandsize)
{

    /*freqbinningband = binningsize [0:2]  spare [3,6] bandsize[7:15] where 0 is the MSB*/
    /*freqbinningband = binningsize [13:15]  spare [9:12] bandsize[0:8] where 0 is the LSB*/

    /*The binninsize value has an offset of 1*/
    *binninsize = ((freqbinningband >> 13) & 0x0007) + 1;
    *bandsize = (freqbinningband)&0x01FF;
}

void fee_getCDSParam_parameters(uint16_t cdsparam, uint16_t *cds_mode, uint16_t *digital_offset)
{

    /*cdsparam = cds_param [0:1] spare [2,5] bandsize[6:15] where 0 is the MSB*/
    /*cdsparam = cds_param [14:15] spare [10,13] bandsize[0:9] where 0 is the LSB*/
    *cds_mode = (cdsparam >> 14) & 0x0003;
    *digital_offset = cdsparam & 0x03FF;
}

int fee_CheckTeleCommandChecksum(fee_TC_Packet_t TC_Packet){

    uint8_t ReadedChecksum = 0;
    uint8_t CalculatedChecksum = 0;

    /*Read checksum*/
    ReadedChecksum = TC_Packet[TC_PACKET_BYTES - TC_CHECKSUM_BYTES];
    
    /*Calcualte checksum*/
    CalculatedChecksum = XORChecksum8(TC_Packet, TC_PACKET_BYTES - TC_CHECKSUM_BYTES);

    /*Compare both checksums*/
    if (CalculatedChecksum != ReadedChecksum)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}