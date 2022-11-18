/**
 * @file fee_common.h
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief Common utils of the fee library.
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Instuto de Astrofísica de Canarias (IAC)
 * 
 */

#ifndef FEE_COMMON_H
#define FEE_COMMON_H

#include "fee.h"

/*Number of speare bits at the end of TC message*/
#define NUM_SPARE_BYTES_END_TELECOMMAND 4
/*Number of speare bits at the end of TM message*/
#define NUM_LAST_TM_SPAREBYTES 16

/*Number of bytes fo the TC checksum*/
#define TC_CHECKSUM_BYTES 1
/*Number of bytes fo the TM checksum*/
#define TM_CHECKSUM_BYTES 2
/*Number of bytes fo the PTD checksum*/
#define PTD_CHECKSUM_BYTES 2


/*Deserialization structure*/
typedef struct
{

    uint8_t *Message;
    size_t max_length_Message;
    size_t byte_counter;

} DeserializationInfo_t;


/**
 * @brief Function which deserialize parameters from a unit8_t vector with network endianess. 
 *
 * @param TM_serialization [Input/Output] Structure with deserialization information. As, 
 *  Byte counter of the packet, maximun length of the packet and the information vector.
 * @param parameter        [Output] Parameter deserialized.
 * @param parameter_length_bytes [Input] Length in bytes of the parameter deserialized. 
 * @return int - The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int DeserializeParameter(DeserializationInfo_t *TM_serialization, void *parameter, int parameter_length_bytes);

/**
 * @brief Function which serialize information into a uint8_t vector with network endianess.
 * 
 * @param data [Input] Parameter to be serialized.
 * @param data_length_bytes [Input] Length, in bytes, of the parameter to be serialized.
 * @param byte_counter [Input/Output] Number of bytes padded in MessageVect vector 
 * @param MessageVect [Output] Vector where the information is serialized. 
 * @param max_length_Message [Input] Maximum length of MessageVect Vector. 
 * @return int The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int SerializeParameter(void *data, int data_length_bytes, size_t *byte_counter, uint8_t *MessageVect, size_t max_length_Message);

/**
 * @brief Function which serialize information into a uint8_t vector without endianess conversion.
 * 
 * @param data [Input] Parameter to be serialized.
 * @param data_length_bytes [Input] Length, in bytes, of the parameter to be serialized.
 * @param byte_counter [Input/Output] Number of bytes padded in MessageVect vector 
 * @param MessageVect [Output] Vector where the information is serialized. 
 * @param max_length_Message [Input] Maximum length of MessageVect Vector. 
 * @return int The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */ 
int SerializeParameter_NoEndianessConversion(void *data, int data_length_bytes, size_t *byte_counter, uint8_t *MessageVect, size_t max_length_Message);

/**
 * @brief Funciton that fills a vector with zeros.
 * 
 * @param data_length_bytes [Input] Length, in bytes, of the parameter to be serialized.
 * @param byte_counter [Input/Output] Number of bytes padded in MessageVect vector 
 * @param MessageVect [Output] Vector where the information is serialized. 
 * @param max_length_Message [Input] Maximum length of MessageVect Vector. 
 * @return int The function returns FEE_EXIT_ERROR if any error occurs. Otherwise, FEE_EXIT_SUCCESS will be returned.
 */
int Serialize_Spare_Parameter(int data_length_bytes, size_t *byte_counter, uint8_t *MessageVect, size_t max_length_Message);

/**
 * @brief Function that checks if Bandsize parameter is multiple of BinningSize
 *
 * @param freqbinningband [Input] Freqbinninband (which is form by two parameter parameter
 * @return int - The function returns 1 if Bandsize is a multiple of BinningSize. Otherwise, 0 will be returned. 
 * In case of any of the parameters is 0 the function would return 0.
 */
int BandSize_MultitpleOf_BinningSize(uint16_t freqbinningband);

/**
 * @brief Calculation a simple xor checsum (eight bits) of uint8_t vector. 
 * 
 * @param data [Input] Data vector
 * @param dataLength  [input] Data vector length
 * @return uint8_t  Calculated checksum
 */
uint8_t XORChecksum8(uint8_t *data, size_t dataLength);

/**
 * @brief Calculation a simple xor checsum (sixteen bits) of uint8_t vector. 
 *
 * @param data [Input] Data vector
 * @param dataLength  [input] Data vector length
 * @return uint16_t  Calculated checksum
 */
uint16_t XORChecksum16(uint8_t *data, size_t dataLength);

#endif