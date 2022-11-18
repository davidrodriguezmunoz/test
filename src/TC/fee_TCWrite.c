/**
 * @file fee_TCWrite.c
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief Fee library serelize telecommand packet functions.
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Instuto de Astrofísica de Canarias (IAC)
 * 
 */

#include <stdio.h>
#include <fee.h>
#include "../common/fee_common.h"
#include <string.h>
#include <arpa/inet.h>

/**
 * \defgroup Local TM Funcitons
 * @{
 */


/**
 * @brief 
 * 
 * @param freqbinninbband 
 * @param binningsize_max 
 * @param binningsize_min 
 * @param bandsize_max 
 * @param bandsize_min 
 * @return int 
 */
int check_feqbinningband_parameter(uint16_t freqbinninbband,
                                   int binningsize_max,
                                   int binningsize_min,
                                   int bandsize_max,
                                   int bandsize_min);
/**
 * @brief 
 * 
 * @param cdsparam 
 * @param cds_mode_max 
 * @param cds_mode_min 
 * @param digital_offset_max 
 * @param digital_offset_min 
 * @return int 
 */
int check_cdsparam_parameter(uint16_t cdsparam,
                             int cds_mode_max,
                             int cds_mode_min,
                             int digital_offset_max,
                             int digital_offset_min);

/**@}*/

int fee_TC_Write(fee_TC_t TC_Data_Struct, fee_TC_Packet_t TC_Packet)
{

    size_t byte_counter = 0;
    uint16_t op_mode = 0;
    uint16_t spatialbinning_mode = 0;
    uint16_t cdsparams = 0;
    uint16_t synpattern = 0;
    uint8_t checksum_tc_message = 0;

    /*Initialize variable to 0*/
    memset(TC_Packet, 0, sizeof(fee_TC_Packet_t));
    /*Convert enum variables to uint16_t*/
    op_mode = (uint16_t)TC_Data_Struct.OPMODE;
    spatialbinning_mode = (uint16_t)TC_Data_Struct.SPATIALBINNINGMODE;
    cdsparams = (uint16_t)TC_Data_Struct.CDSPARAMS;
    synpattern = (uint16_t)TC_Data_Struct.SYNTPATTERN;

    if (SerializeParameter(&TC_Data_Struct.TC_COUNTER, sizeof(TC_Data_Struct.TC_COUNTER), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&op_mode, sizeof(op_mode), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.EXPO_TIME, sizeof(TC_Data_Struct.EXPO_TIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        Serialize_Spare_Parameter(sizeof(uint8_t), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DUOUTDRAINTVLTG, sizeof(TC_Data_Struct.DUOUTDRAINTVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DURESETVLTG, sizeof(TC_Data_Struct.DURESETVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DUDUMPVLTG, sizeof(TC_Data_Struct.DUDUMPVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DUOUTGATEVLTG, sizeof(TC_Data_Struct.DUOUTGATEVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DUIMGCKHVLTG, sizeof(TC_Data_Struct.DUIMGCKHVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DUSTGCKHVLTG, sizeof(TC_Data_Struct.DUSTGCKHVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DUREGCKHVLTG, sizeof(TC_Data_Struct.DUREGCKHVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DUDUMPCKHVLTG, sizeof(TC_Data_Struct.DUDUMPCKHVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DURESETCKHVLTG, sizeof(TC_Data_Struct.DURESETCKHVLTG), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.NBSMEAR, sizeof(TC_Data_Struct.NBSMEAR), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.WOISTART, sizeof(TC_Data_Struct.WOISTART), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.WOISIZE, sizeof(TC_Data_Struct.WOISIZE), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&spatialbinning_mode, sizeof(spatialbinning_mode), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.FTPTIME, sizeof(TC_Data_Struct.FTPTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.IMGSTGCKRFTIME, sizeof(TC_Data_Struct.IMGSTGCKRFTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.IMGSTGCKOVTIME, sizeof(TC_Data_Struct.IMGSTGCKOVTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.IMGSTGCKPWTIME, sizeof(TC_Data_Struct.IMGSTGCKPWTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.REGLINADVTIME, sizeof(TC_Data_Struct.REGLINADVTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.LINADVREGTIME, sizeof(TC_Data_Struct.LINADVREGTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.RCKPTIME, sizeof(TC_Data_Struct.RCKPTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.REGCKOVTIME, sizeof(TC_Data_Struct.REGCKOVTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.R1REGCKONTIME, sizeof(TC_Data_Struct.R1REGCKONTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.R3REGCKONTIME, sizeof(TC_Data_Struct.R3REGCKONTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        Serialize_Spare_Parameter(sizeof(uint8_t), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.R2CKRISEDELTIME, sizeof(TC_Data_Struct.R2CKRISEDELTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.RESETCKONTIME, sizeof(TC_Data_Struct.RESETCKONTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.RESETCKFALLDELTIME, sizeof(TC_Data_Struct.RESETCKFALLDELTIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.ADC1TIME, sizeof(TC_Data_Struct.ADC1TIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.ADC2TIME, sizeof(TC_Data_Struct.ADC2TIME), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.ADC1RDDLY, sizeof(TC_Data_Struct.ADC1RDDLY), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.ADC2RDDLY, sizeof(TC_Data_Struct.ADC2RDDLY), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.DULAMBDA, sizeof(TC_Data_Struct.DULAMBDA), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.FREQBINNINGBAND_1, sizeof(TC_Data_Struct.FREQBINNINGBAND_1), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.FREQBINNINGBAND_2, sizeof(TC_Data_Struct.FREQBINNINGBAND_2), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.FREQBINNINGBAND_3, sizeof(TC_Data_Struct.FREQBINNINGBAND_3), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.FREQBINNINGBAND_4, sizeof(TC_Data_Struct.FREQBINNINGBAND_4), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.FREQBINNINGBAND_5, sizeof(TC_Data_Struct.FREQBINNINGBAND_5), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.PIXEL_MIN, sizeof(TC_Data_Struct.PIXEL_MIN), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.PIXEL_MAX, sizeof(TC_Data_Struct.PIXEL_MAX), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&synpattern, sizeof(synpattern), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&cdsparams, sizeof(cdsparams), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.HCNBSAMPLE, sizeof(TC_Data_Struct.HCNBSAMPLE), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.NBTAIL, sizeof(TC_Data_Struct.NBTAIL), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        SerializeParameter(&TC_Data_Struct.ACQSTARTDELAY, sizeof(TC_Data_Struct.ACQSTARTDELAY), &byte_counter, TC_Packet, TC_PACKET_BYTES) ||
        Serialize_Spare_Parameter(sizeof(uint8_t) * NUM_SPARE_BYTES_END_TELECOMMAND, &byte_counter, TC_Packet, TC_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }

    /*Calculate checksum of the TCMessage and insert it*/
    checksum_tc_message = XORChecksum8(TC_Packet, TC_PACKET_BYTES - TC_CHECKSUM_BYTES);
    if (SerializeParameter(&checksum_tc_message, sizeof(checksum_tc_message), &byte_counter, TC_Packet, TC_PACKET_BYTES))
    {
        return FEE_EXIT_ERROR;
    }

    /*Check that lengths match*/
    if (byte_counter != TC_PACKET_BYTES)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}

int fee_TC_BoundsCheck(fee_TC_t TC_Data_Struct)
{

    if (TC_Data_Struct.TC_COUNTER < TC_COUNTER_MIN || TC_Data_Struct.TC_COUNTER > TC_COUNTER_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.OPMODE < TC_OPMODE_MIN || TC_Data_Struct.OPMODE > TC_OPMODE_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.EXPO_TIME < TC_EXPO_TIME_MIN || TC_Data_Struct.EXPO_TIME > TC_EXPO_TIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DUOUTDRAINTVLTG < TC_DUOUTDRAINTVLTG_MIN || TC_Data_Struct.DUOUTDRAINTVLTG > TC_DUOUTDRAINTVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DURESETVLTG < TC_DURESETVLTG_MIN || TC_Data_Struct.DURESETVLTG > TC_DURESETVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DUDUMPVLTG < TC_DUDUMPVLTG_MIN || TC_Data_Struct.DUDUMPVLTG > TC_DUDUMPVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DUOUTGATEVLTG < TC_DUOUTGATEVLTG_MIN || TC_Data_Struct.DUOUTGATEVLTG > TC_DUOUTGATEVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DUIMGCKHVLTG < TC_DUIMGCKHVLTG_MIN || TC_Data_Struct.DUIMGCKHVLTG > TC_DUIMGCKHVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DUSTGCKHVLTG < TC_DUSTGCKHVLTG_MIN || TC_Data_Struct.DUSTGCKHVLTG > TC_DUSTGCKHVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DUREGCKHVLTG < TC_DUREGCKHVLTG_MIN || TC_Data_Struct.DUREGCKHVLTG > TC_DUREGCKHVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DUDUMPCKHVLTG < TC_DUDUMPCKHVLTG_MIN || TC_Data_Struct.DUDUMPCKHVLTG > TC_DUDUMPCKHVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DURESETCKHVLTG < TC_DURESETCKHVLTG_MIN || TC_Data_Struct.DURESETCKHVLTG > TC_DURESETCKHVLTG_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.NBSMEAR < TC_NBSMEAR_MIN || TC_Data_Struct.NBSMEAR > TC_NBSMEAR_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.WOISTART < TC_WOISTART_MIN || TC_Data_Struct.WOISTART > TC_WOISTART_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.WOISIZE < TC_WOISIZE_MIN || TC_Data_Struct.WOISIZE > TC_WOISIZE_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.SPATIALBINNINGMODE < TC_SPATIALBINNINGMODE_MIN || TC_Data_Struct.SPATIALBINNINGMODE > TC_SPATIALBINNINGMODE_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.FTPTIME < TC_FTPTIME_MIN || TC_Data_Struct.FTPTIME > TC_FTPTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.IMGSTGCKRFTIME < TC_IMGSTGCKRFTIME_MIN || TC_Data_Struct.IMGSTGCKRFTIME > TC_IMGSTGCKRFTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.IMGSTGCKOVTIME < TC_IMGSTGCKOVTIME_MIN || TC_Data_Struct.IMGSTGCKOVTIME > TC_IMGSTGCKOVTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.IMGSTGCKPWTIME < TC_IMGSTGCKPWTIME_MIN || TC_Data_Struct.IMGSTGCKPWTIME > TC_IMGSTGCKPWTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.REGLINADVTIME < TC_REGLINADVTIME_MIN || TC_Data_Struct.REGLINADVTIME > TC_REGLINADVTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.LINADVREGTIME < TC_LINADVREGTIME_MIN || TC_Data_Struct.LINADVREGTIME > TC_LINADVREGTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.RCKPTIME < TC_RCKPTIME_MIN || TC_Data_Struct.RCKPTIME > TC_RCKPTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.REGCKOVTIME < TC_REGCKOVTIME_MIN || TC_Data_Struct.REGCKOVTIME > TC_REGCKOVTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.R1REGCKONTIME < TC_R1REGCKONTIME_MIN || TC_Data_Struct.R1REGCKONTIME > TC_R1REGCKONTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.R3REGCKONTIME < TC_R3REGCKONTIME_MIN || TC_Data_Struct.R3REGCKONTIME > TC_R3REGCKONTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.R2CKRISEDELTIME < TC_R2CKRISEDELTIME_MIN || TC_Data_Struct.R2CKRISEDELTIME > TC_R2CKRISEDELTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.RESETCKONTIME < TC_RESETCKONTIME_MIN || TC_Data_Struct.RESETCKONTIME > TC_RESETCKONTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.RESETCKFALLDELTIME < TC_RESETCKFALLDELTIME_MIN || TC_Data_Struct.RESETCKFALLDELTIME > TC_RESETCKFALLDELTIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.ADC1TIME < TC_ADC1TIME_MIN || TC_Data_Struct.ADC1TIME > TC_ADC1TIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.ADC2TIME < TC_ADC2TIME_MIN || TC_Data_Struct.ADC2TIME > TC_ADC2TIME_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.ADC1RDDLY < TC_ADC1RDDLY_MIN || TC_Data_Struct.ADC1RDDLY > TC_ADC1RDDLY_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.ADC2RDDLY < TC_ADC2RDDLY_MIN || TC_Data_Struct.ADC2RDDLY > TC_ADC2RDDLY_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.DULAMBDA < TC_DULAMBDA_MIN || TC_Data_Struct.DULAMBDA > TC_DULAMBDA_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.PIXEL_MIN < TC_PIXEL_MIN_MIN || TC_Data_Struct.PIXEL_MIN > TC_PIXEL_MIN_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.PIXEL_MAX < TC_PIXEL_MAX_MIN || TC_Data_Struct.PIXEL_MAX > TC_PIXEL_MAX_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.HCNBSAMPLE < TC_HCNBSAMPLE_MIN || TC_Data_Struct.HCNBSAMPLE > TC_HCNBSAMPLE_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.NBTAIL < TC_NBTAIL_MIN || TC_Data_Struct.NBTAIL > TC_NBTAIL_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.ACQSTARTDELAY < TC_ACQSTARTDELAY_MIN || TC_Data_Struct.ACQSTARTDELAY > TC_ACQSTARTDELAY_MAX)
    {
        return FEE_EXIT_ERROR;
    }

    if (check_cdsparam_parameter(TC_Data_Struct.CDSPARAMS, TC_CDSPARAMS_MODE_MAX, TC_CDSPARAMS_MODE_MIN,
                                 TC_CDSPARAMS_DIGITAL_OFFSET_MAX, TC_CDSPARAMS_DIGITAL_OFFSET_MIN))
    {
        return FEE_EXIT_ERROR;
    }

    if (check_feqbinningband_parameter(TC_Data_Struct.FREQBINNINGBAND_1, TC_FREQBINNINGBAND_1_BINNINGSIZE_MAX,
                                       TC_FREQBINNINGBAND_1_BINNINGSIZE_MIN, TC_FREQBINNINGBAND_1_BANDSIZE_MAX, TC_FREQBINNINGBAND_1_BANDSIZE_MIN))
    {
        return FEE_EXIT_ERROR;
    }

    if (check_feqbinningband_parameter(TC_Data_Struct.FREQBINNINGBAND_2, TC_FREQBINNINGBAND_2_BINNINGSIZE_MAX,
                                       TC_FREQBINNINGBAND_2_BINNINGSIZE_MIN, TC_FREQBINNINGBAND_2_BANDSIZE_MAX, TC_FREQBINNINGBAND_2_BANDSIZE_MIN))
    {
        return FEE_EXIT_ERROR;
    }

    if (check_feqbinningband_parameter(TC_Data_Struct.FREQBINNINGBAND_3, TC_FREQBINNINGBAND_3_BINNINGSIZE_MAX,
                                       TC_FREQBINNINGBAND_3_BINNINGSIZE_MIN, TC_FREQBINNINGBAND_3_BANDSIZE_MAX, TC_FREQBINNINGBAND_3_BANDSIZE_MIN))
    {
        return FEE_EXIT_ERROR;
    }

    if (check_feqbinningband_parameter(TC_Data_Struct.FREQBINNINGBAND_4, TC_FREQBINNINGBAND_4_BINNINGSIZE_MAX,
                                       TC_FREQBINNINGBAND_4_BINNINGSIZE_MIN, TC_FREQBINNINGBAND_4_BANDSIZE_MAX, TC_FREQBINNINGBAND_4_BANDSIZE_MIN))
    {
        return FEE_EXIT_ERROR;
    }

    if (check_feqbinningband_parameter(TC_Data_Struct.FREQBINNINGBAND_5, TC_FREQBINNINGBAND_5_BINNINGSIZE_MAX,
                                       TC_FREQBINNINGBAND_5_BINNINGSIZE_MIN, TC_FREQBINNINGBAND_5_BANDSIZE_MAX, TC_FREQBINNINGBAND_5_BANDSIZE_MIN))
    {
        return FEE_EXIT_ERROR;
    }

    if (TC_Data_Struct.SYNTPATTERN != NO_SYNTHETIC_PATTERN && TC_Data_Struct.SYNTPATTERN != SYNTHETIC_PATTERN_1 && TC_Data_Struct.SYNTPATTERN != SYNTHETIC_PATTERN_2)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}

uint16_t fee_fill_cdsparam_parameter(cds_params_t cds_mode, int digital_offset)
{
    uint16_t cds_mode_s;
    uint16_t digigtal_offset_s;

    /*cds_mode parameter length is 2 bits*/
    cds_mode_s = (uint16_t)cds_mode & 0x0003;
    /*digital_offset parameter length is nine bits*/
    digigtal_offset_s = (uint16_t)digital_offset & 0x03FF;
    /*cdsparam = cds_mode [0:1] spare [2,5] bandsize[6:15] where 0 is the MSB*/
    /*cdsparam = cds_mode [14:15] spare [10,13] bandsize[0:9] where 0 is the LSB*/
    return cds_mode_s << 14 | digigtal_offset_s;
}

uint16_t fee_fill_freqbinningband_parameter(int binningsize, int bandsize)
{
    uint16_t binninsize_s;
    uint16_t bandsize_s;

    /*Binningsize parameter length is three bits and has an offset of -1*/
    binninsize_s = ((uint16_t)binningsize & 0x0007) - 1;
    /*Bandsize parameter length is nine bits*/
    bandsize_s = ((uint16_t)bandsize) & 0x01FF;
    /*freqbinninbband = binningsize [0:2] spare [3,6] bandsize[7:15] being 0 the MSB*/
    /*freqbinninbband = binningsize [13:15] spare [9,12] bandsize[0:0] being 0 the LSB*/
    return (binninsize_s << 13) | bandsize_s;
}

int check_cdsparam_parameter(uint16_t cdsparam,
                             int cds_mode_max,
                             int cds_mode_min,
                             int digital_offset_max,
                             int digital_offset_min)
{
    uint16_t cds_mode_s = 0;
    uint16_t digigtal_offset_s = 0;

    fee_getCDSParam_parameters(cdsparam, &cds_mode_s, &digigtal_offset_s);

    /* Check that parameters are not out of bound*/
    if (cds_mode_s < cds_mode_min ||
        cds_mode_s > cds_mode_max ||
        digigtal_offset_s < digital_offset_min ||
        digigtal_offset_s > digital_offset_max)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}

int check_feqbinningband_parameter(uint16_t freqbinningband,
                                   int binningsize_max,
                                   int binningsize_min,
                                   int bandsize_max,
                                   int bandsize_min)
{
    uint16_t binninsize_s;
    uint16_t bandsize_s;

    fee_getFreqBinningBand_parameters(freqbinningband, &binninsize_s, &bandsize_s);

    /* Check that parameters are not out of bound*/
    if (binninsize_s < binningsize_min ||
        binninsize_s > binningsize_max ||
        bandsize_s < bandsize_min ||
        bandsize_s > bandsize_max)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}
