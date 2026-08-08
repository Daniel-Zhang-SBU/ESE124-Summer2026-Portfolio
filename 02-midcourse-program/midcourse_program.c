/*
Name:Daniel Zhang
Date:7/22/26
Program name: CSV Grade Book 
Purpose: Read grades.csv and print each student's average.
*/
#include <stdio.h>

int main(void)
{
   FILE *fp = NULL;
   char line[256];
   char name[100];
   int score1, score2, score3;
   fp = fopen("grades.csv", "r");       //open file
   if (fp == NULL)
   {
      printf("Failed to open grades.csv");
      return 1;
   }
   while(fgets(line, sizeof(line), fp))         //read one line
   {
      if (sscanf(line, " %99[^,],%d,%d,%d", name, &score1, &score2, &score3) == 4)     // %99[^,] skip any whitespaces infront and read 99 character values until the next comma
      {
         float avg = (score1 + score2 + score3) / 3.0f;                //we have to divide by 3.0 becuase we want the decimals. If we only divide by 3, we lose the decimals because of integer division
         printf("%s average %.1f\n", name, avg);
      }
      else
      printf("Student %s invalid line", name);
   }
   fclose(fp);              //close file
   return 0;
}