
/**
 * @file fee_TMRead.c
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief Fee library deserialize telemetry packet functions.
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Instuto de Astrofísica de Canarias (IAC)
 * 
 */
#include <fee.h>
#include "../common/fee_common.h"
#include <string.h>
#include <arpa/inet.h>
#include <math.h>

/*CCD temperature constants*/
#define CCD_TEMPERATURE_GAIN (float)4.82e-2f
#define CCD_TEMPERATURE_OFFSET 7.086e2f
#define CCD_TEMPERATURE_A 4.53e1f
#define CCD_TEMPERATURE_B 1.88e-01f
#define CCD_TEMPERATURE_C 4.08e-05f

/*VAU and FPPE Temperature constants*/
#define VUAFPPE_TEMPERATURE_A 8.889e-04f
#define VUAFPPE_TEMPERATURE_B 2.449e-04f
#define VUAFPPE_TEMPERATURE_C 1.238e-07f
#define VUAFPPE_TEMPERATURE_D 8.059e-04f
#define VUAFPPE_TEMPERATURE_E 3.830e3f
#define VUAFPPE_TEMPERATURE_F 2.5f

/*Bias voltages gains*/
#define BIAS_VOLTAGE_GAIN_VOD 8.864e-3f
#define BIAS_VOLTAGE_GAIN_VRD 5.794e-3f
#define BIAS_VOLTAGE_GAIN_VDD 8.864e-3f
#define BIAS_VOLTAGE_GAIN_VOG 1.471e-3f

/*CCD Clock voltage gains*/
#define IPHIH_GAIN 3.352e-3f
#define SPHIH_GAIN 3.352e-3f
#define RPHIH_GAIN 3.352e-3f
#define PHIRH_GAIN 3.892e-3f
#define VDGH_GAIN 3.892e-3f

/*Power supplies voltages gains*/
#define VDIG_GAIN 1.612e-3f
#define VDRV_GAIN 8.864e-3f
#define VANLGP_GAIN 1.612e-3f
#define VANLGN_GAIN -1.733e-3f
#define VDET_GAIN 2.627e-3f

/*Digital supply current gain*/
#define IDIG_GAIN 3.941e-4f

int fee_convert_TM_parameters(fee_TM_t TM_Data_Struct_Index, fee_TM_Float_t *TM_DATA_F)
{

    float hcnbsample_f = 0.0;
    float ccd_resistance_1 = 0.0, ccd_resistance_2 = 0.0;
    float vau_resistance = 0.0, fppe_resistance = 0.0;

    /*Check that HCNBSAMPlE is different to zero. And protect the code to zero division*/
    if (TM_Data_Struct_Index.Returned_TC.HCNBSAMPLE == 0)
    {
        return FEE_EXIT_ERROR;
    }

    /*Convert to float the hcnbsample variable*/
    hcnbsample_f = (float)TM_Data_Struct_Index.Returned_TC.HCNBSAMPLE;

    /*CCD Tempeature TM */
    ccd_resistance_1 = ((float)TM_Data_Struct_Index.CCDTEMP_MEAS1 / hcnbsample_f) * CCD_TEMPERATURE_GAIN + CCD_TEMPERATURE_OFFSET;
    TM_DATA_F->CCDTEMP_MEAS1_f = CCD_TEMPERATURE_A + (CCD_TEMPERATURE_B * ccd_resistance_1) + (CCD_TEMPERATURE_C * ccd_resistance_1 * ccd_resistance_1);

    ccd_resistance_2 = ((float)TM_Data_Struct_Index.CCDTEMP_MEAS2 / hcnbsample_f) * CCD_TEMPERATURE_GAIN + CCD_TEMPERATURE_OFFSET;
    TM_DATA_F->CCDTEMP_MEAS2_f = CCD_TEMPERATURE_A + (CCD_TEMPERATURE_B * ccd_resistance_2) + (CCD_TEMPERATURE_C * ccd_resistance_2 * ccd_resistance_2);

    /* VAU and FPPE temperature*/

    /*Protection against zero division*/
    if ((VUAFPPE_TEMPERATURE_F - ((float)TM_Data_Struct_Index.VAUTEMP_MEAS / hcnbsample_f * VUAFPPE_TEMPERATURE_D)) == 0.0)
    {
        return FEE_EXIT_ERROR;
    }
    vau_resistance = ((float)TM_Data_Struct_Index.VAUTEMP_MEAS / hcnbsample_f * VUAFPPE_TEMPERATURE_D * VUAFPPE_TEMPERATURE_E) /
                     (VUAFPPE_TEMPERATURE_F - ((float)TM_Data_Struct_Index.VAUTEMP_MEAS / hcnbsample_f * VUAFPPE_TEMPERATURE_D));

    TM_DATA_F->VAUTEMP_MEAS_f = 1 /
                                        (VUAFPPE_TEMPERATURE_A + VUAFPPE_TEMPERATURE_B * log(vau_resistance) + VUAFPPE_TEMPERATURE_C * log(vau_resistance) * log(vau_resistance));

    /*Protection against zero division*/
    if ((VUAFPPE_TEMPERATURE_F - ((float)TM_Data_Struct_Index.FPPETEMP_MEAS / hcnbsample_f * VUAFPPE_TEMPERATURE_D)) == 0.0)
    {
        return FEE_EXIT_ERROR;
    }
    fppe_resistance = ((float)TM_Data_Struct_Index.FPPETEMP_MEAS / hcnbsample_f * VUAFPPE_TEMPERATURE_D * VUAFPPE_TEMPERATURE_E) /
                      (VUAFPPE_TEMPERATURE_F - ((float)TM_Data_Struct_Index.FPPETEMP_MEAS / hcnbsample_f * VUAFPPE_TEMPERATURE_D));

    TM_DATA_F->FPPETEMP_MEAS_f = 1 /
                                         (VUAFPPE_TEMPERATURE_A + VUAFPPE_TEMPERATURE_B * log(fppe_resistance) + VUAFPPE_TEMPERATURE_C * log(fppe_resistance) * log(fppe_resistance));

    /* Bias Voltages TM*/
    TM_DATA_F->VODE_MEAS_f = BIAS_VOLTAGE_GAIN_VOD * (float)TM_Data_Struct_Index.VODE_MEAS / hcnbsample_f;
    TM_DATA_F->VODF_MEAS_f = BIAS_VOLTAGE_GAIN_VOD * (float)TM_Data_Struct_Index.VODF_MEAS / hcnbsample_f;
    TM_DATA_F->VODG_MEAS_f = BIAS_VOLTAGE_GAIN_VOD * (float)TM_Data_Struct_Index.VODG_MEAS / hcnbsample_f;
    TM_DATA_F->VODH_MEAS_f = BIAS_VOLTAGE_GAIN_VOD * (float)TM_Data_Struct_Index.VODH_MEAS / hcnbsample_f;
    TM_DATA_F->VRD_MEAS_f = BIAS_VOLTAGE_GAIN_VRD * (float)TM_Data_Struct_Index.VRD_MEAS / hcnbsample_f;
    TM_DATA_F->VDD_MEAS_f = BIAS_VOLTAGE_GAIN_VDD * (float)TM_Data_Struct_Index.VDD_MEAS / hcnbsample_f;
    TM_DATA_F->VOG_MEAS_f = BIAS_VOLTAGE_GAIN_VOG * (float)TM_Data_Struct_Index.VOG_MEAS / hcnbsample_f;

    /*Clock level voltages*/
    TM_DATA_F->IPHIH_MEAS_f = IPHIH_GAIN * (float)TM_Data_Struct_Index.IPHIH_MEAS / hcnbsample_f;
    TM_DATA_F->SPHIH_MEAS_f = SPHIH_GAIN * (float)TM_Data_Struct_Index.SPHIH_MEAS / hcnbsample_f;
    TM_DATA_F->RPHIH_MEAS_f = RPHIH_GAIN * (float)TM_Data_Struct_Index.RPHIH_MEAS / hcnbsample_f;
    TM_DATA_F->PHIRH_MEAS_f = PHIRH_GAIN * (float)TM_Data_Struct_Index.PHIRH_MEAS / hcnbsample_f;
    TM_DATA_F->VDGH_MEAS_f = VDGH_GAIN * (float)TM_Data_Struct_Index.VDGH_MEAS / hcnbsample_f;

    /*Power supplies voltages*/
    TM_DATA_F->VDIG_MEAS_f = VDIG_GAIN * (float)TM_Data_Struct_Index.VDIG_MEAS / hcnbsample_f;
    TM_DATA_F->VDRV_MEAS_f = VDRV_GAIN * (float)TM_Data_Struct_Index.VDRV_MEAS / hcnbsample_f;
    TM_DATA_F->VANAP_MEAS_f = VANLGP_GAIN * (float)TM_Data_Struct_Index.VANAP_MEAS / hcnbsample_f;
    TM_DATA_F->VANAN_MEAS_f = VANLGN_GAIN * (float)TM_Data_Struct_Index.VANAN_MEAS / hcnbsample_f;
    TM_DATA_F->VDET_MEAS_f = VDET_GAIN * (float)TM_Data_Struct_Index.VDET_MEAS / hcnbsample_f;

    /*digital supply current tm*/
    TM_DATA_F->IDIG_MEAS_f = IDIG_GAIN * (float)TM_Data_Struct_Index.IDIG_MEAS / hcnbsample_f;

    return FEE_EXIT_SUCCESS;
}

int fee_TM_Read(fee_TM_Packet_t TM_Packet, fee_TM_t *TM_Data_Struct)
{

    DeserializationInfo_t TM_serialization;
    /*Intermediate variables for the parameters that are enums*/
    uint16_t op_mode = 0;
    uint16_t spatialbinning_mode = 0;
    uint16_t cdsparams = 0;
    uint16_t synpattern = 0;

    TM_serialization.Message = TM_Packet;
    TM_serialization.max_length_Message = TM_PACKET_BYTES;
    TM_serialization.byte_counter = 0;

    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->TM_COUNTER, sizeof(TM_Data_Struct->TM_COUNTER)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.TC_COUNTER, sizeof(TM_Data_Struct->Returned_TC.TC_COUNTER)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &op_mode, FEE_OPMODE_BYTESIZE))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.EXPO_TIME, sizeof(TM_Data_Struct->Returned_TC.EXPO_TIME)))
    {
        return FEE_EXIT_ERROR;
    }

    /*Discard spare byte Index 5*/
    TM_serialization.byte_counter = TM_serialization.byte_counter + 1;

    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DUOUTDRAINTVLTG, sizeof(TM_Data_Struct->Returned_TC.DUOUTDRAINTVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DURESETVLTG, sizeof(TM_Data_Struct->Returned_TC.DURESETVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DUDUMPVLTG, sizeof(TM_Data_Struct->Returned_TC.DUDUMPVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DUOUTGATEVLTG, sizeof(TM_Data_Struct->Returned_TC.DUOUTGATEVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DUIMGCKHVLTG, sizeof(TM_Data_Struct->Returned_TC.DUIMGCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DUSTGCKHVLTG, sizeof(TM_Data_Struct->Returned_TC.DUSTGCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DUREGCKHVLTG, sizeof(TM_Data_Struct->Returned_TC.DUREGCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DUDUMPCKHVLTG, sizeof(TM_Data_Struct->Returned_TC.DUDUMPCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DURESETCKHVLTG, sizeof(TM_Data_Struct->Returned_TC.DURESETCKHVLTG)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.NBSMEAR, sizeof(TM_Data_Struct->Returned_TC.NBSMEAR)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.WOISTART, sizeof(TM_Data_Struct->Returned_TC.WOISTART)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.WOISIZE, sizeof(TM_Data_Struct->Returned_TC.WOISIZE)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &spatialbinning_mode, FEE_SPATIALBINNING_BYTESIZE))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.FTPTIME, sizeof(TM_Data_Struct->Returned_TC.FTPTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.IMGSTGCKRFTIME, sizeof(TM_Data_Struct->Returned_TC.IMGSTGCKRFTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.IMGSTGCKOVTIME, sizeof(TM_Data_Struct->Returned_TC.IMGSTGCKOVTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.IMGSTGCKPWTIME, sizeof(TM_Data_Struct->Returned_TC.IMGSTGCKPWTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.REGLINADVTIME, sizeof(TM_Data_Struct->Returned_TC.REGLINADVTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.LINADVREGTIME, sizeof(TM_Data_Struct->Returned_TC.LINADVREGTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.RCKPTIME, sizeof(TM_Data_Struct->Returned_TC.RCKPTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.REGCKOVTIME, sizeof(TM_Data_Struct->Returned_TC.REGCKOVTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.R1REGCKONTIME, sizeof(TM_Data_Struct->Returned_TC.R1REGCKONTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.R3REGCKONTIME, sizeof(TM_Data_Struct->Returned_TC.R3REGCKONTIME)))
    {
        return FEE_EXIT_ERROR;
    }

    /*Discard spare byte Index 29*/
    TM_serialization.byte_counter = TM_serialization.byte_counter + 1;

    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.R2CKRISEDELTIME, sizeof(TM_Data_Struct->Returned_TC.R2CKRISEDELTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.RESETCKONTIME, sizeof(TM_Data_Struct->Returned_TC.RESETCKONTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.RESETCKFALLDELTIME, sizeof(TM_Data_Struct->Returned_TC.RESETCKFALLDELTIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.ADC1TIME, sizeof(TM_Data_Struct->Returned_TC.ADC1TIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.ADC2TIME, sizeof(TM_Data_Struct->Returned_TC.ADC2TIME)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.ADC1RDDLY, sizeof(TM_Data_Struct->Returned_TC.ADC1RDDLY)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.ADC2RDDLY, sizeof(TM_Data_Struct->Returned_TC.ADC2RDDLY)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.DULAMBDA, sizeof(TM_Data_Struct->Returned_TC.DULAMBDA)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.FREQBINNINGBAND_1, sizeof(TM_Data_Struct->Returned_TC.FREQBINNINGBAND_1)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.FREQBINNINGBAND_2, sizeof(TM_Data_Struct->Returned_TC.FREQBINNINGBAND_2)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.FREQBINNINGBAND_3, sizeof(TM_Data_Struct->Returned_TC.FREQBINNINGBAND_3)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.FREQBINNINGBAND_4, sizeof(TM_Data_Struct->Returned_TC.FREQBINNINGBAND_4)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.FREQBINNINGBAND_5, sizeof(TM_Data_Struct->Returned_TC.FREQBINNINGBAND_5)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.PIXEL_MIN, sizeof(TM_Data_Struct->Returned_TC.PIXEL_MIN)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.PIXEL_MAX, sizeof(TM_Data_Struct->Returned_TC.PIXEL_MAX)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &synpattern, FEE_SYNPATTERN_BYTESIZE))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &cdsparams, FEE_CDSPARAMS_BYTESIZE))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.HCNBSAMPLE, sizeof(TM_Data_Struct->Returned_TC.HCNBSAMPLE)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.NBTAIL, sizeof(TM_Data_Struct->Returned_TC.NBTAIL)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->CCDTEMP_MEAS1, sizeof(TM_Data_Struct->CCDTEMP_MEAS1)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->CCDTEMP_MEAS2, sizeof(TM_Data_Struct->CCDTEMP_MEAS2)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VAUTEMP_MEAS, sizeof(TM_Data_Struct->VAUTEMP_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->FPPETEMP_MEAS, sizeof(TM_Data_Struct->FPPETEMP_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VODE_MEAS, sizeof(TM_Data_Struct->VODE_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VODF_MEAS, sizeof(TM_Data_Struct->VODF_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VODG_MEAS, sizeof(TM_Data_Struct->VODG_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VODH_MEAS, sizeof(TM_Data_Struct->VODH_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VRD_MEAS, sizeof(TM_Data_Struct->VRD_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VDD_MEAS, sizeof(TM_Data_Struct->VDD_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VOG_MEAS, sizeof(TM_Data_Struct->VOG_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->IPHIH_MEAS, sizeof(TM_Data_Struct->IPHIH_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->SPHIH_MEAS, sizeof(TM_Data_Struct->SPHIH_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->RPHIH_MEAS, sizeof(TM_Data_Struct->RPHIH_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->PHIRH_MEAS, sizeof(TM_Data_Struct->PHIRH_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VDGH_MEAS, sizeof(TM_Data_Struct->VDGH_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VANAP_MEAS, sizeof(TM_Data_Struct->VANAP_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VANAN_MEAS, sizeof(TM_Data_Struct->VANAN_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VDET_MEAS, sizeof(TM_Data_Struct->VDET_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VDRV_MEAS, sizeof(TM_Data_Struct->VDRV_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VDIG_MEAS, sizeof(TM_Data_Struct->VDIG_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->IDIG_MEAS, sizeof(TM_Data_Struct->IDIG_MEAS)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->TC_ERROR, sizeof(TM_Data_Struct->TC_ERROR)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->VAU_ERROR, sizeof(TM_Data_Struct->VAU_ERROR)))
    {
        return FEE_EXIT_ERROR;
    }
    if (DeserializeParameter(&TM_serialization, &TM_Data_Struct->Returned_TC.ACQSTARTDELAY, sizeof(TM_Data_Struct->Returned_TC.ACQSTARTDELAY)))
    {
        return FEE_EXIT_ERROR;
    }

    /*Convert enum variables to uint16_t*/
    TM_Data_Struct->Returned_TC.OPMODE = op_mode ;
    TM_Data_Struct->Returned_TC.SPATIALBINNINGMODE = spatialbinning_mode;
    TM_Data_Struct->Returned_TC.CDSPARAMS = cdsparams;
    TM_Data_Struct->Returned_TC.SYNTPATTERN = synpattern;

    /*Increase byte counter to discard spare bytes and the checksum*/
    TM_serialization.byte_counter += ( NUM_LAST_TM_SPAREBYTES + TM_CHECKSUM_BYTES );

    /*Verify that the packet length is correct*/
    if (TM_serialization.byte_counter != TM_serialization.max_length_Message)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}

int fee_CheckTelemetryChecksum(fee_TM_Packet_t TM_Packet){

    uint16_t ReadedChecksum = 0;
    uint16_t CalculatedChecksum = 0;

    /*Read checksum*/
    memcpy(&ReadedChecksum, TM_Packet + (TM_PACKET_BYTES - TM_CHECKSUM_BYTES), TM_CHECKSUM_BYTES) ;
    
    /*Calcualte checksum*/
    CalculatedChecksum = XORChecksum16(TM_Packet, TM_PACKET_BYTES - TM_CHECKSUM_BYTES);

    /*Compare both checksums*/
    if (CalculatedChecksum != ReadedChecksum)
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}