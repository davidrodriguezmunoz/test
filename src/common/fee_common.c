/**
 * @file fee_common.c
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief Common utils of the fee library.
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Instuto de Astrofísica de Canarias (IAC)
 * 
 */

#include <fee.h>
#include "fee_common.h"
#include "stdio.h"
#include <arpa/inet.h>
#include <string.h>

uint8_t XORChecksum8(uint8_t *data, size_t dataLength)
{
    uint8_t value = 0;
    size_t i = 0;

    for (i = 0; i < dataLength; i++)
    {
        value ^= (uint8_t)data[i];
    }
    return value;
}

uint16_t XORChecksum16(uint8_t *data, size_t dataLength)
{
    uint16_t value = 0;
    uint16_t value_int = 0;

    for (size_t i = 0; i < dataLength / 2; i++)
    {   
        memcpy(&value_int, &data[2 * i], 2);
        value ^= value_int;
    }

    if (dataLength % 2)
    {
        value ^= data[dataLength - 1];
    }

    return value;
}

int BandSize_MultitpleOf_BinningSize(uint16_t freqbinningband)
{

    uint16_t binninsize_s = 0;
    uint16_t bandsize_s = 0;

    if (freqbinningband == 0)
    {
        return -1;
    }

    fee_getFreqBinningBand_parameters(freqbinningband, &binninsize_s, &bandsize_s);

    /*Protection against 0 divison*/
    if (binninsize_s == 0 || bandsize_s == 0)
    {
        return 0;
    }
    
    if (bandsize_s % binninsize_s == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int DeserializeParameter(DeserializationInfo_t *DeserializationStructure, void *parameter, int parameter_length_bytes)
{

    size_t *byte_counter = NULL;

    byte_counter = &DeserializationStructure->byte_counter;

    if (*byte_counter + parameter_length_bytes > DeserializationStructure->max_length_Message)
    {
        return FEE_EXIT_ERROR;
    }

    if (parameter_length_bytes == 1)
    {
        *(uint8_t *)parameter = DeserializationStructure->Message[*byte_counter];
    }
    else if (parameter_length_bytes == 2)
    {

         /*Convert 16 bits word from network endianess to host endianess*/
        memcpy(parameter, &DeserializationStructure->Message[*byte_counter], parameter_length_bytes);
        *(uint16_t *) parameter =  ntohs( *(uint16_t *)parameter);

    }
    else if (parameter_length_bytes == 4)
    {
        /*Convert 16 bits word from network endianess to host endianess*/
        memcpy(parameter, &DeserializationStructure->Message[*byte_counter], parameter_length_bytes);
        *(uint32_t *) parameter =  ntohl( *(uint32_t *)parameter);
    }
    else
    {
        return FEE_EXIT_ERROR;
    }

    *byte_counter = *byte_counter + parameter_length_bytes;

    return FEE_EXIT_SUCCESS;
}

int Serialize_Spare_Parameter(int data_length_bytes, size_t *byte_counter, uint8_t *TC_Message, size_t max_length_Message)
{

    if (max_length_Message >= data_length_bytes + *byte_counter)
    {
        memset(TC_Message + *byte_counter, 0, sizeof(TC_Message[0]));
        *byte_counter = *byte_counter + data_length_bytes;
    }
    else
    {
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}

int SerializeParameter(void *data, int data_length_bytes, size_t *byte_counter, uint8_t *MessageVect, size_t max_length_Message)
{

    uint16_t net_short = 0;
    uint32_t net_long = 0;

    /*Check overflow*/
    if (max_length_Message >= data_length_bytes + *byte_counter)
    {
        /*Different operations depending on the data length*/
        if (data_length_bytes == 1)
        {
            MessageVect[*byte_counter] = *(uint8_t *)data;
        }
        else if (data_length_bytes == 2)
        {
            /*Convert 16 bits word from host endianess to network endianess*/
            net_short = htons(*(uint16_t *)data);
            /*Insert new information to the TC_message vector*/
            memcpy(MessageVect + *byte_counter, &net_short, data_length_bytes);
        }
        else if (data_length_bytes == 4)
        {
            /*Convert 36 bits word from host endianess to networdk endianess*/
            net_long = htonl(*(uint32_t *)data);
            /*Insert new information to the TC_message vector*/
            memcpy(MessageVect + *byte_counter, &net_long, data_length_bytes);
        }
        else
        {
            /*Return not supported new data length error*/
            return FEE_EXIT_ERROR;
        }

        /*Update the counter of the inserted information*/
        *byte_counter = *byte_counter + data_length_bytes;
    }
    else
    {
        /*Return overflow error*/
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}

int SerializeParameter_NoEndianessConversion(void *data, int data_length_bytes, size_t *byte_counter, uint8_t *MessageVect, size_t max_length_Message)
{

    /*Check overflow*/
    if (max_length_Message >= data_length_bytes + *byte_counter)
    {
        
        /*Copy the information to the vector*/
        memcpy(MessageVect + *byte_counter, data, data_length_bytes);

        /*Update the counter of the inserted information*/
        *byte_counter = *byte_counter + data_length_bytes;
    }
    else
    {
        /*Return overflow error*/
        return FEE_EXIT_ERROR;
    }

    return FEE_EXIT_SUCCESS;
}
