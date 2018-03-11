#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// when reading a line of a file, the upper limit to the number of read characters
#define MAXLENOFLINE 2000

// the number of trials to seek a eigenvalue when pmd can`t by a vector_x(0)
#define MAXTRIAL 5

// the number in order for determining whether or not a eigenvalue comes to convergent.
#define EPSILON 10e-3

// when excecuting Power method, the upper limit to the number of power of vector_x(0).
#define MAXPOWER 10000

// Prototypes
void   make_MatB(double[][*], double[], double, int);
void   normalize_vector(double[], int);
void   Mat_mul_vec(double[][*], double[], double[], int);
double inner_product(double[], double[], int);
void   vector_copy(double[], double[], int);
int    pmd(double[][*], double[], double*, int);
void   random_makex0(double[], int);
void   print_result(double[], double, int, int);
void   print_error(int);

int dim;                               // in order for argument of function definition(This is formally needed.)

/*
 * filename: file's name which contains Matrix(n*n) you want to seek eigenvalues
 * numseekeigen: The numbef of eigenvalues you want to seek ( 1 <= numseekeigen <= n (n=dim) )
 *               numseekeigen is 1 by defalut.
 */
int main(int argc, char const* argv[]) // ./program "filename" "numseekeigen"
{
   // The Code about inputinf from the file is as below.
   FILE* fp;
   int   row = 0; // row of MatA
   int   col = 1; // column of MatA
   int   i, j;
   char  temp[MAXLENOFLINE];
   char* tem;

   if(argc == 1 || 2 < argc) {
      printf("Command-line input needs to be below. \n");
      printf("./program filename (numseekeigen(the numbef of eigenvalues you want to seek))");
      return 1;
   }
   if((fp = fopen(argv[1], "r")) == NULL) {
      printf("An error was encountered while reading the file.\n");
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

   double MatA[row][col];

   for(i = 0; i < row; i++) {
      fgets(temp, MAXLENOFLINE, fp);
      MatA[i][0] = atof(strtok(temp, " \t,"));
      j = 1;
      while((tem = strtok(NULL, " \t,")) != NULL) {
         MatA[i][j] = atof(tem);
         j++;
      }
   }

   for(i = 0; i < row; i++) {
      for(j = 0; j < col - 1; j++) {
         printf("%f ", MatA[i][j]);
      }
      printf("%f\n", MatA[i][j]);
   }
   // The Code about inputing from the file is as above.


   // Variables Declaratioin
   int    numseekeigen; // The numbef of eigenvalues you want to seek
   int    dim = row;    // dim=row=col=n (it doesn`t mean mathmatical dim(MatrixA))
   double eigen;        // eigenvalue
   double vecx[dim];    // x_k(0)
   int    i1, i2;       // these are in order for "for loop".
   int    checker;      // this contains the information about whether or not pmd seeked a eigenvlaue correctly.
   // int row : row of MatA
   // int col : column of MatA
   // (In this problam, MatrixA is n*n, then row=col=n=dim)

   // Define the numseekeigen
   if(argc == 2) {
      numseekeigen = 1;
   } else {
      numseekeigen = atoi(argv[2]);
      if(numseekeigen > dim) {
         printf("The number of eigenvalues are %d.\n", dim);
         return 1;
      }
   }

   // seek the eigenvalues by power method
   for(i1 = 1; i1 <= numseekeigen; i1++) {
      make_MatB(MatA, vecx, eigen, dim); // Change MatA to "A - λ*vecx*t^vecx"(≡B)
      for(i2 = 0; i2 < dim; i2++) {
         vecx[i2] = 1.0;
      }
      for(i2 = 0; i2 < MAXTRIAL; i2++) {
         if((checker = pmd(MatA, vecx, &eigen, dim)) == 0) { // excecute the power method
            print_result(vecx, eigen, dim, i1);
            break;
         } else {
            random_makex0(vecx, dim);    // try power method by another vector_x(0)
         }
      }
      print_error(i1);                   // display an error message that how many eigenvalues can`t be seeked.
   }

   return 0;
}

void make_MatB(double MatA[][dim], double vecx[], double eigen, int dim)
{
   // Change MatA to "A - λ*vecx*(t^vecx)"(≡B)
   int row, col;
   for(row = 0; row < dim; row++) {
      for(col = 0; col < dim; col++) {
         MatA[row][col] -= eigen * vecx[row] * vecx[col];
      }
   }
}

void normalize_vector(double vecx[], int dim)
{
   // normalize vector_x
   double sum = 0;
   double norm;
   int    i;
   for(i = 0; i < dim; i++) {
      sum += pow(vecx[i], 2);
   }
   norm = sqrt(sum);
   for(i = 0; i < dim; i++) {
      vecx[i] /= norm;
   }
}

void Mat_mul_vec(double MatA[][dim], double vecy[], double vecx[], int dim)
{
   // seek vecy = MatA*vecx
   int i, j;
   for(i = 0; i < dim; i++) {
      vecy[i] = 0.0;
      for(j = 0; j < dim; j++) {
         vecy[i] += MatA[i][j] * vecx[j];
      }
   }
}

double inner_product(double vec1[], double vec2[], int dim)
{
   // seek <vec1,vec2>
   double inner_product = 0;
   for(int i = 0; i < dim; i++) {
      inner_product += vec1[i] * vec2[i];
   }
   return inner_product;
}

void vector_copy(double vec1[], vec2[], int dim)
{
   // copy vector components from vec2 to vec1
   for(int i = 0; i < dim; i++) {
      vec1[i] = vec2[i];
   }
}

int pmd(double MatA[][dim], double vecx[], double* eigen, int dim)
{
   // Power method
   *eigen = 0.0;
   double vecy[dim];
   double eigen1;
   for(int power = 0; power < count; power++) {
      normalize_vector(vecx, dim);
      Mat_mul_vec(MatA, vecy, vecx, dim);
      eigen1 = inner_product(vecy, vecy) / inner_product(vecy, vecx); // Rayleigh quotient
      if(abs((eigen1 - *eigen) / (*eigen)) < EPSILON) {
         *eigen = eigen1;
         vector_copy(vecx,vecy,dim);
         return 0;
      }
      *eigen = eigen1;
      vector_copy(vecx,vecy);
   }
   return 1;
}
