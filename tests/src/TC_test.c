/**
 * @file TC_test.c
 * @author David Rodríguez Muñoz. (david.rodriguez@iac.es)
 * @brief  PTD Test. The test reads an example files which contains TC packets, deserialize the information, 
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

int TC_test(FILE *fp, int *AreEqual)
{
   fee_TC_Packet_t TC_Message = {0};
   fee_TC_Packet_t TC_Message_Generated = {0};
   fee_TC_t TC_Data_Struct = {0};
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

            TC_Message[byte_counter] = (uint8_t)atoi(tok);
            byte_counter++;
         }
      }

      /*Check received TC checksum*/

      if (fee_CheckTeleCommandChecksum(TC_Message) != FEE_EXIT_SUCCESS){
         printf("Error at fee_CheckTeleCommandChecksum");
         return EXIT_FAILURE;
      }

      /*deserialize TC*/
      if (fee_TC_Read(TC_Message, &TC_Data_Struct) != FEE_EXIT_SUCCESS)
      {
         printf("Error at TCRead\n");
         return EXIT_FAILURE;
      }

      /*Check bounds*/
      if(fee_TC_BoundsCheck(TC_Data_Struct) != FEE_EXIT_SUCCESS)
      {
         return EXIT_FAILURE;
      }

      /*Serialize back TC*/
      if (fee_TC_Write(TC_Data_Struct, TC_Message_Generated) != FEE_EXIT_SUCCESS)
      {
         printf("Error at TCRead\n");
         return EXIT_FAILURE;
      }

      for (int i = 0; i < TC_PACKET_BYTES; i++)
      {
         if (TC_Message[i] != TC_Message_Generated[i])
         {
            printf("Error in bytes:%d 0x%02X 0x%02X\n", i + 1, TC_Message[i], TC_Message_Generated[i]);

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
      printf("Argument Error: The program should be executed as: %s TC_MessageFile \n", argv[0]);
      return EXIT_FAILURE;
   }

   /* opening file for reading */
   fp = fopen(argv[1], "r");
   if (fp == NULL)
   {
      perror("Error opening file");
      return (EXIT_FAILURE);
   }

   // Run test
   if (TC_test(fp, &AreEqual) != EXIT_SUCCESS){
      fclose(fp);
      return EXIT_FAILURE;
   }

   // Clean-up
   fclose(fp);

   if (AreEqual)
   {
      printf("TC Test Success!\n");
      return EXIT_SUCCESS;
   }
   else
   {
      printf("TC Test Error!\n");
      return EXIT_FAILURE;
   }
}
