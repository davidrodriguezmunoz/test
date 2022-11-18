/**
 * @file PTD_test.c
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief  PTD Test. The test reads an example files which contains PTD packets, deserialize the information, 
 *  re-serializes it and checks if both packets (the original and the re-serialized) are equal.    
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fee.h>

#define MAXIMUM_PTD_LINE_SIZE 5000000

char str[TM_PACKET_BYTES * 10];
char str_PTD[MAXIMUM_PTD_LINE_SIZE];

void free_loop(uint16_t **ptr, size_t num)
{
    size_t i;

    for (i = 0; i < num; i++)
    {
        free(ptr[i]);
    }
}

int PTD_test(FILE *fTM, FILE *fDTP, int *AreEqual)
{
    char str_timestamp_aux[50];
    fee_TM_Packet_t TM_Message = {0};
    uint8_t *PixelDataPacket;
    uint8_t *PixelDataPacketGenerated;
    fee_TM_t TM_Data_Struct = {0};
    char *tok;
    int counter, byte_counter_TM, byte_counter_FDTP;
    long int timestamp_DTP = 0, timestamp_TM = 0;
    fee_PTD_t PTD_Data;

    *AreEqual = 1;

    PixelDataPacket = (uint8_t *)malloc(MAXIMUM_PTD_LINE_SIZE * sizeof(uint8_t));
    PixelDataPacketGenerated = (uint8_t *)malloc(MAXIMUM_PTD_LINE_SIZE * sizeof(uint8_t));

    /*Iterate line by line of the TDP*/
    while (fgets(str_PTD, MAXIMUM_PTD_LINE_SIZE, fDTP))
    {

        byte_counter_FDTP = 0;
        /*Get Timestamp*/

        memcpy(str_timestamp_aux, str_PTD, sizeof(char) * 14);
        timestamp_DTP = atol(str_timestamp_aux);

        rewind(fTM);
        /*Search closest timestamp from TM file*/
        while (fgets(str, TM_PACKET_BYTES * 10, fTM))
        {
            byte_counter_TM = 0;
            timestamp_TM = 0;

            for (tok = strtok(str, " "), counter = 0; tok != NULL; tok = strtok(NULL, " "), counter++)
            {

                if (tok[0] && strstr(tok, "\n") == NULL &&
                    counter > 1 &&
                    (timestamp_DTP - timestamp_TM) >= 0)
                {

                    TM_Message[byte_counter_TM] = (uint8_t)atoi(tok);
                    byte_counter_TM++;
                }
                else if (tok[0] && strstr(tok, "\n") == NULL && counter == 0)
                {
                    timestamp_TM = atol(tok);
                }
            }
        }

        fflush(NULL);

        if (fee_TM_Read(TM_Message, &TM_Data_Struct) != FEE_EXIT_SUCCESS)
        {
            free(PixelDataPacketGenerated);
            free(PixelDataPacket);
            printf("Error at TMRead\n");
            return EXIT_FAILURE;
        }

        
        if (fee_Calculate_PTD_Sizes(TM_Data_Struct, &PTD_Data.PTDSizes, &PTD_Data.PTDImageMatrixTotalSizes)!= FEE_EXIT_SUCCESS){
            free(PixelDataPacketGenerated);
            free(PixelDataPacket);
            printf("Error at CalculatePTD_sizes\n");
            return EXIT_FAILURE;
        }

        if (PTD_Data.PTDSizes.DataPacketTotalBytes == 0){
            free (PixelDataPacketGenerated);
            free(PixelDataPacket);
            printf("Error at CalculatePTD_sizes\n");
            return EXIT_FAILURE;
        }

        for (tok = strtok(str_PTD, " "), counter = 0; tok != NULL; tok = strtok(NULL, " "), counter++)
        {

            if (tok[0] && strstr(tok, "\n") == NULL && counter > 2)
            {
                PixelDataPacket[byte_counter_FDTP] = (uint8_t)atoi(tok);
                byte_counter_FDTP++;
            }
        }

        for (int k = 0; k < FEE_NUM_CCD; k++)
        {
            PTD_Data.ImageMatrix[k] = (uint16_t *)malloc(PTD_Data.PTDImageMatrixTotalSizes.ImageMatrixBytes);
        }


        if (fee_CheckPTDChecksum(PixelDataPacket, PTD_Data.PTDSizes) != FEE_EXIT_SUCCESS ){
            free_loop(PTD_Data.ImageMatrix, FEE_NUM_CCD);
            free (PixelDataPacketGenerated);
            free(PixelDataPacket);
            printf("Error at fee_CheckPTDChecksum\n");
            return EXIT_FAILURE;
        }

        if (fee_PTD_Read(PixelDataPacket, TM_Data_Struct, &PTD_Data) != FEE_EXIT_SUCCESS)
        {
            free_loop(PTD_Data.ImageMatrix, FEE_NUM_CCD);
            free(PixelDataPacketGenerated);
            free(PixelDataPacket);
            return EXIT_FAILURE;
        }

        if (fee_PTD_Write(TM_Data_Struct, PTD_Data, PixelDataPacketGenerated) != FEE_EXIT_SUCCESS)
        {
            free_loop(PTD_Data.ImageMatrix, FEE_NUM_CCD);
            free(PixelDataPacketGenerated);
            free(PixelDataPacket);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < PTD_Data.PTDSizes.DataPacketTotalBytes; i++)
        {
            if (PixelDataPacket[i] != PixelDataPacketGenerated[i])
            {
                printf("Error in bytes:%ld 0x%02X 0x%02X\n", i + 1, PixelDataPacket[i], PixelDataPacketGenerated[i]);

                *AreEqual = 0;
            }
        }

        free_loop(PTD_Data.ImageMatrix, FEE_NUM_CCD);
    }

    free(PixelDataPacketGenerated);
    free(PixelDataPacket);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{

    FILE *fTM, *fDTP;
    int AreEqual = 1;

    if (argc != 3)
    {
        printf("Argument Error: The program should be executed as: %s TM_MessageFile PTM_MessageFile \n", argv[0]);
        return EXIT_FAILURE;
    }

    /* opening file for reading */
    fTM = fopen(argv[1], "r");
    if (fTM == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fDTP = fopen(argv[2], "r");
    if (fDTP == NULL)
    {
        fclose(fTM);
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Run test
    if (PTD_test(fTM, fDTP, &AreEqual) != EXIT_SUCCESS){
        fclose(fTM);
        return EXIT_FAILURE;
    }

    // Clean-up
    fclose(fDTP);
    fclose(fTM);

    // Check return code
    if (AreEqual)
    {
        printf("PTD Test Success!\n");
        return EXIT_SUCCESS;
    }
    else
    {
        printf("PTD Test Error!\n");
        return EXIT_FAILURE;
    }
}
