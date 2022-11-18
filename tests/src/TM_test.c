/**
 * @file TM_test.c
 * @brief  PTD Test. The test reads an example files which contains TM packets, deserialize the information, 
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

char str[TM_PACKET_BYTES * 10];

int TM_test(FILE *fp,  int *AreEqual)
{
   fee_TM_Packet_t TM_Message = {0};
   fee_TM_Packet_t TM_Message_Generated = {0};
   fee_TM_t TM_Data_Struct = {0};
   char *tok;
   int counter, byte_counter;
   *AreEqual = 1;

   while (fgets(str, TM_PACKET_BYTES * 10, fp))
   {
      byte_counter = 0;
      for (tok = strtok(str, " "), counter = 0; tok != NULL; tok = strtok(NULL, " "), counter++)
      {
         if (tok[0] && strstr(tok, "\n") == NULL && counter > 1)
         {

            TM_Message[byte_counter] = (uint8_t)atoi(tok);
            byte_counter++;
         }
      }

      if (fee_CheckTelemetryChecksum(TM_Message) != FEE_EXIT_SUCCESS){
         printf("Error at fee_CheckTelemetryChecksum\n");
         return EXIT_FAILURE;
      }  

      if (fee_TM_Read(TM_Message, &TM_Data_Struct) != FEE_EXIT_SUCCESS)
      {
         printf("Error at TMRead\n");
         return EXIT_FAILURE;
      }

      if (fee_TM_Write(TM_Data_Struct, TM_Message_Generated) != FEE_EXIT_SUCCESS)
      {
         printf("Error at TMWrite\n");
         return EXIT_FAILURE;
      }

      for (int i = 0; i < TM_PACKET_BYTES; i++)
      {
         if (TM_Message[i] != TM_Message_Generated[i])
         {
            printf("Error in bytes:%d 0x%02X 0x%02X\n", i + 1, TM_Message[i], TM_Message_Generated[i]);
            *AreEqual = 0;
         }
      }
   }

   return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
   FILE *fp;
   int AreEqual = 1;

   if (argc != 2)
   {
      printf("Argument Error: The program should be executed as: %s TM_MessageFile \n", argv[0]);
      return EXIT_FAILURE;
   }

   /* opening file for reading */
   fp = fopen(argv[1], "r");
   if (fp == NULL)
   {
      perror("Error opening file");
      return EXIT_FAILURE;
   }

   // Run test
   if (TM_test(fp, &AreEqual) != EXIT_SUCCESS) {
      fclose(fp);
      return EXIT_FAILURE;
   }

   // Clean-up
   fclose(fp);

   if (AreEqual)
   {
      printf("TM Test Success!\n");
      return EXIT_SUCCESS;
   }
   else
   {
      printf("TM Test Error!\n");
      return EXIT_FAILURE;
   }
}
