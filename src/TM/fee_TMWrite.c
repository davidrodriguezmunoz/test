/**
 * @file fee_TMWrite.c
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief Fee library serialize telecommand packet functions.
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Instuto de Astrofísica de Canarias (IAC)
 * 
 */

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <fee.h>
#include "../common/fee_common.h"

int fee_TM_Write(fee_TM_t TM_Data_Struct, fee_TM_Packet_t TM_Packet)
{

    size_t byte_counter = 0;
    uint16_t checksum_tm_message = 0;
    /*Intermediate variables for the parameters that are enums*/
    uint16_t op_mode = 0;
    uint16_t spatialbinning_mode = 0;
    uint16_t cdsparams = 0;
    uint16_t synpattern = 0;

    /*Initialize variable to 0*/
    memset(TM_Packet, 0, sizeof(fee_TM_Packet_t));
    /*Convert enum variables to uint16_t*/
    op_mode = (uint16_t)TM_Data_Struct.Returned_TC.OPMODE;
    spatialbinning_mode = (uint16_t)TM_Data_Struct.Returned_TC.SPATIALBINNINGMODE;
    cdsparams = (uint16_t)TM_Data_Struct.Returned_TC.CDSPARAMS;
    synpattern = (uint16_t)TM_Data_Struct.Returned_TC.SYNTPATTERN;

    if (SerializeParameter(&TM_Data_Struct.TM_COUNTER, sizeof(TM_Data_Struct.TM_COUNTER), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.TC_COUNTER, sizeof(TM_Data_Struct.Returned_TC.TC_COUNTER), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&op_mode, FEE_OPMODE_BYTESIZE, &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.EXPO_TIME, sizeof(TM_Data_Struct.Returned_TC.EXPO_TIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }

    /*spare byte Index 5*/
    Serialize_Spare_Parameter(sizeof(uint8_t), &byte_counter, TM_Packet, TM_PACKET_BYTES);

    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DUOUTDRAINTVLTG, sizeof(TM_Data_Struct.Returned_TC.DUOUTDRAINTVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DURESETVLTG, sizeof(TM_Data_Struct.Returned_TC.DURESETVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DUDUMPVLTG, sizeof(TM_Data_Struct.Returned_TC.DUDUMPVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DUOUTGATEVLTG, sizeof(TM_Data_Struct.Returned_TC.DUOUTGATEVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DUIMGCKHVLTG, sizeof(TM_Data_Struct.Returned_TC.DUIMGCKHVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DUSTGCKHVLTG, sizeof(TM_Data_Struct.Returned_TC.DUSTGCKHVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DUREGCKHVLTG, sizeof(TM_Data_Struct.Returned_TC.DUREGCKHVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DUDUMPCKHVLTG, sizeof(TM_Data_Struct.Returned_TC.DUDUMPCKHVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DURESETCKHVLTG, sizeof(TM_Data_Struct.Returned_TC.DURESETCKHVLTG), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.NBSMEAR, sizeof(TM_Data_Struct.Returned_TC.NBSMEAR), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.WOISTART, sizeof(TM_Data_Struct.Returned_TC.WOISTART), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.WOISIZE, sizeof(TM_Data_Struct.Returned_TC.WOISIZE), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&spatialbinning_mode, FEE_SPATIALBINNING_BYTESIZE, &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.FTPTIME, sizeof(TM_Data_Struct.Returned_TC.FTPTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.IMGSTGCKRFTIME, sizeof(TM_Data_Struct.Returned_TC.IMGSTGCKRFTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.IMGSTGCKOVTIME, sizeof(TM_Data_Struct.Returned_TC.IMGSTGCKOVTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.IMGSTGCKPWTIME, sizeof(TM_Data_Struct.Returned_TC.IMGSTGCKPWTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.REGLINADVTIME, sizeof(TM_Data_Struct.Returned_TC.REGLINADVTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.LINADVREGTIME, sizeof(TM_Data_Struct.Returned_TC.LINADVREGTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.RCKPTIME, sizeof(TM_Data_Struct.Returned_TC.RCKPTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.REGCKOVTIME, sizeof(TM_Data_Struct.Returned_TC.REGCKOVTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.R1REGCKONTIME, sizeof(TM_Data_Struct.Returned_TC.R1REGCKONTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.R3REGCKONTIME, sizeof(TM_Data_Struct.Returned_TC.R3REGCKONTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }

    /*Discard spare byte Index 29*/
    Serialize_Spare_Parameter(sizeof(uint8_t), &byte_counter, TM_Packet, TM_PACKET_BYTES);

    if (SerializeParameter(&TM_Data_Struct.Returned_TC.R2CKRISEDELTIME, sizeof(TM_Data_Struct.Returned_TC.R2CKRISEDELTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.RESETCKONTIME, sizeof(TM_Data_Struct.Returned_TC.RESETCKONTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.RESETCKFALLDELTIME, sizeof(TM_Data_Struct.Returned_TC.RESETCKFALLDELTIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.ADC1TIME, sizeof(TM_Data_Struct.Returned_TC.ADC1TIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.ADC2TIME, sizeof(TM_Data_Struct.Returned_TC.ADC2TIME), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.ADC1RDDLY, sizeof(TM_Data_Struct.Returned_TC.ADC1RDDLY), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.ADC2RDDLY, sizeof(TM_Data_Struct.Returned_TC.ADC2RDDLY), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.DULAMBDA, sizeof(TM_Data_Struct.Returned_TC.DULAMBDA), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.FREQBINNINGBAND_1, sizeof(TM_Data_Struct.Returned_TC.FREQBINNINGBAND_1), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.FREQBINNINGBAND_2, sizeof(TM_Data_Struct.Returned_TC.FREQBINNINGBAND_2), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.FREQBINNINGBAND_3, sizeof(TM_Data_Struct.Returned_TC.FREQBINNINGBAND_3), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.FREQBINNINGBAND_4, sizeof(TM_Data_Struct.Returned_TC.FREQBINNINGBAND_4), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.FREQBINNINGBAND_5, sizeof(TM_Data_Struct.Returned_TC.FREQBINNINGBAND_5), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.PIXEL_MIN, sizeof(TM_Data_Struct.Returned_TC.PIXEL_MIN), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.PIXEL_MAX, sizeof(TM_Data_Struct.Returned_TC.PIXEL_MAX), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&synpattern, FEE_SYNPATTERN_BYTESIZE, &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&cdsparams, FEE_CDSPARAMS_BYTESIZE, &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.HCNBSAMPLE, sizeof(TM_Data_Struct.Returned_TC.HCNBSAMPLE), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.NBTAIL, sizeof(TM_Data_Struct.Returned_TC.NBTAIL), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.CCDTEMP_MEAS1, sizeof(TM_Data_Struct.CCDTEMP_MEAS1), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.CCDTEMP_MEAS2, sizeof(TM_Data_Struct.CCDTEMP_MEAS2), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VAUTEMP_MEAS, sizeof(TM_Data_Struct.VAUTEMP_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.FPPETEMP_MEAS, sizeof(TM_Data_Struct.FPPETEMP_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VODE_MEAS, sizeof(TM_Data_Struct.VODE_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VODF_MEAS, sizeof(TM_Data_Struct.VODF_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VODG_MEAS, sizeof(TM_Data_Struct.VODG_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VODH_MEAS, sizeof(TM_Data_Struct.VODH_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VRD_MEAS, sizeof(TM_Data_Struct.VRD_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VDD_MEAS, sizeof(TM_Data_Struct.VDD_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VOG_MEAS, sizeof(TM_Data_Struct.VOG_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.IPHIH_MEAS, sizeof(TM_Data_Struct.IPHIH_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.SPHIH_MEAS, sizeof(TM_Data_Struct.SPHIH_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.RPHIH_MEAS, sizeof(TM_Data_Struct.RPHIH_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.PHIRH_MEAS, sizeof(TM_Data_Struct.PHIRH_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VDGH_MEAS, sizeof(TM_Data_Struct.VDGH_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VANAP_MEAS, sizeof(TM_Data_Struct.VANAP_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VANAN_MEAS, sizeof(TM_Data_Struct.VANAN_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VDET_MEAS, sizeof(TM_Data_Struct.VDET_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VDRV_MEAS, sizeof(TM_Data_Struct.VDRV_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VDIG_MEAS, sizeof(TM_Data_Struct.VDIG_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.IDIG_MEAS, sizeof(TM_Data_Struct.IDIG_MEAS), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.TC_ERROR, sizeof(TM_Data_Struct.TC_ERROR), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.VAU_ERROR, sizeof(TM_Data_Struct.VAU_ERROR), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }
    if (SerializeParameter(&TM_Data_Struct.Returned_TC.ACQSTARTDELAY, sizeof(TM_Data_Struct.Returned_TC.ACQSTARTDELAY), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }

    /*Insert las sparebytes*/
    Serialize_Spare_Parameter(sizeof(uint8_t) * NUM_LAST_TM_SPAREBYTES, &byte_counter, TM_Packet, TM_PACKET_BYTES);

    /*Calculate checksum of the TCMessage, convert from host endiannes to net, and insert it*/
    checksum_tm_message = XORChecksum16(TM_Packet, TM_PACKET_BYTES - TM_CHECKSUM_BYTES);
    /*Serialize checksum. Edianess conversion is not necessary*/
    if (SerializeParameter_NoEndianessConversion(&checksum_tm_message, sizeof(checksum_tm_message), &byte_counter, TM_Packet, TM_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }

    /*Check that lengths match*/
    if (byte_counter != TM_PACKET_BYTES)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}
