#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXLENOFLINE 2000
#define eppp         10e-10

int main(int argc, char const* argv[]) // ./program "filename" "numfindvector"
{
   FILE*  fp;
   int    row = 0;                     // row of MatX
   int    col = 0;                     // column of MatX
   int    i, j;
   char   temp[MAXLENOFLINE];
   char*  buf1;
   double buf2;

   if(argc == 1 || 3 < argc) {
      printf("Command-line input needs to be below. \n");
      printf(
             "./program filename (numfindvector(the number of principal vectors you want to find))\n\nThe program aborted.\n");
      return 1;
   }
   if((fp = fopen(argv[1], "r")) == NULL) {
      printf("An error was encountered while reading the file.\n\nThe program aborted.\n");
      return 1;
   }
   while(fgets(temp, MAXLENOFLINE, fp) != NULL) {
      row++;
   }

   buf2 = atof(buf1 = strtok(temp, " \t,") );
   if( ( fabs(buf2 = atof(buf1) ) < eppp) && *buf1 != '0') {
   } else {
      printf("char  = %c\n", *buf1);
      printf("float = %f\n", fabs(buf2 - eppp));
      col++;
   }
   while((buf1 = strtok(NULL, " \t,")) != NULL) {
      if( ( fabs(buf2 = atof(buf1) ) < eppp) && *buf1 != '0') {
         continue;
      } else {
         printf("char  = %c\n", *buf1);
         printf("float = %f\n", fabs(buf2 - eppp));
         col++;
      }
   }

   printf("\nrow=%d", row);
   printf("\ncol=%d\n", col);

   fseek(fp, 0, SEEK_SET);

   // make 2-dimention array dynamically(MatX)
   double** MatX;
   double*  base_MatX;
   MatX      = malloc(sizeof(double*) * row);
   base_MatX = malloc(sizeof(double) * row * col);
   for(i = 0; i < row; i++) {
      MatX[i] = base_MatX + i * col;
   }

   for(i = 0; i < row; i++) {
      fgets(temp, MAXLENOFLINE, fp);
      buf2 = atof(buf1 = strtok(temp, " \t,")); // 'comma', 'space', and 'tab' as delimiters.
      if((fabs(buf2 = atof(buf1)) < eppp) && *buf1 != '0') {
         j = 0;
      } else {
         MatX[i][0] = buf2;
         j = 1;
      }
      while((buf1 = strtok(NULL, " \t,")) != NULL) {
         if((fabs(buf2 = atof(buf1)) < eppp) && *buf1 != '0') {
            continue;
         } else {
            MatX[i][j] = buf2;
            j++;
         }
      }
   }

   fclose(fp);

   printf("MatrixA is as below.\n");
   for(i = 0; i < row; i++) {
      for(j = 0; j < col; j++) {
         printf("%f ", MatX[i][j]);
      }
      printf("\b\n");
   }
   printf("\n");

   return 0;
}
