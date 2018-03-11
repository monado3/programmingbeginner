#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENOFLINE 2000

int main(int argc, char* argv[])
{
   FILE* fp;
   int   row = 0;
   int   col = 1;
   int   i, j;
   char  temp[MAXLENOFLINE];
   char* tem;

   if(argc != 2) {
      printf("コマンドのあとに一つファイルを指定してください\n");
   }
   if((fp = fopen(argv[1], "r")) == NULL) {
      printf("読み込みに失敗しました。\n");
      return 1;
   }

   while(fgets(temp, MAXLENOFLINE, fp) != NULL) {
      row++;
   }

   strtok(temp, " \t,");
   while(strtok(NULL, " \t,") != NULL) {
      col++;
   }

   fseek(fp, 0, SEEK_SET);

   double ans[row][col];

   for(i = 0; i < row; i++) {
      fgets(temp, MAXLENOFLINE, fp);
      ans[i][0] = atof(strtok(temp, " \t,"));
      j = 1;
      while((tem = strtok(NULL, " \t,")) != NULL) {
         ans[i][j] = atof(tem);
         j++;
      }
   }

   for(i = 0; i < row; i++) {
      for(j = 0; j < col - 1; j++) {
         printf("%f ", ans[i][j]);
      }
      printf("%f\n", ans[i][j]);
   }

   return 0;
}
