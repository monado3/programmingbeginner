#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// when reading a line of a file, the upper limit to the number of read characters
#define MAXLENOFLINE 2000

// the number of trials to find a eigenvalue when pmd can`t by a vector_x(0)
#define MAXTRIAL 5

// the number in order for judging whether or not a eigenvalue comes to convergence.
#define EPSILON 10e-3

// when excecuting Power method, the upper limit to the number of power of vector_x(0).
#define MAXPOWER 10000

// Prototypes
void   make_MatB(double[][*], double[], double, int);
void   normalize_vector(double[], int);
void   Mat_mul_vec(double[][*], double[], double[], int);
double inner_product(double[], double[], int);
void   vector_copy(double[], double[], int);
int    pmd(double[][*], double[], double*, int*, int);
void   random_makex0(double[], int);
void   print_result(double[], int ,double, int, int);
void   print_error(int);

int dim;                               // in order for argument of function definition(This is formally needed.)

/*
 * filename: file's name which contains Matrix(n*n) you want to find eigenvalues
 * numfindeigen: The numbef of eigenvalues you want to find ( 1 <= numfindeigen <= n (n=dim) )
 *               numfindeigen is 1 by defalut.
 */
int main(int argc, char const* argv[]) // ./program "filename" "numfindeigen"
{

   // The Code about inputinf from the file is as below.
   //this program uses 'comma', 'space', and 'tab' as delimiters.
   FILE* fp;
   int   row = 0; // row of MatA
   int   col = 1; // column of MatA
   int   i, j;
   char  temp[MAXLENOFLINE];
   char* tem;

   if(argc == 1 || 2 < argc) {
      printf("Command-line input needs to be below. \n");
      printf("./program filename (numfindeigen(the numbef of eigenvalues you want to find))");
      return 1;
   }
   if((fp = fopen(argv[1], "r")) == NULL) {
      printf("An error was encountered while reading the file.\n");
      return 1;
   }
   while(fgets(temp, MAXLENOFLINE, fp) != NULL) {
      row++;
   }

   strtok(temp, " \t,");//
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


   //display input MatrixA
   printf("MatrixA is as below.\n");
   for(i = 0; i < row; i++) {
      for(j = 0; j < col - 1; j++) {
         printf("%f ", MatA[i][j]);
      }
      printf("%f\n", MatA[i][j]);
   }
   printf("\n");
   // The Code about inputing from the file is as above.


   // Variables Declaratioin
   int    numfindeigen; // The numbef of eigenvalues you want to find
   int    dim = row;    // dim=row=col=n (it doesn`t mean mathmatical dim(MatrixA))
   double eigen = 0.0;        // eigenvalue
   int power; //In pmd, this is used as iteration variable. (The number of iterations)
   double vecx[dim];    // x_k(0)
   int    i1, i2;       // these are in order for "for loop".
   int    checker;      // this contains the information about whether or not pmd found a eigenvlaue correctly.
   // int row : row of MatA
   // int col : column of MatA
   // (In this problam, MatrixA is n*n, then row=col=n=dim)

   // Define the numfindeigen
   if(argc == 2) {
      numfindeigen = 1;
   } else {
      numfindeigen = atoi(argv[2]);
      if(numfindeigen > dim) {
         printf("The number of eigenvalues are %d.\n", dim);
         return 1;
      }
   }

   srand(time(NULL));//determine the seed

   // find the eigenvalues by power method
   for(i1 = 1; i1 <= numfindeigen; i1++) {
      make_MatB(MatA, vecx, eigen, dim); // Change MatA to "A - λ*vecx*t^vecx"(≡B)
      for(i2 = 0; i2 < dim; i2++) {
         vecx[i2] = 1.0;
      }
      for(i2 = 0; i2 < MAXTRIAL; i2++) {
         if((checker = pmd(MatA, vecx, &eigen, &power, dim)) == 0) { // excecute the power method
            print_result(vecx, i1, eigen, dim, power);
            break;
         } else {
            random_makex0(vecx, dim);    // try power method by another vector_x(0)
         }
      }
      print_error(i1);                   // display an error message that how many eigenvalues can`t be found.
      return 1;
   }
   printf("The program successfully terminated");

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
   // calculate vecy ( = MatA * vecx )
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
   // calculate <vec1,vec2>
   double inner_product = 0;
   for(int i = 0; i < dim; i++) {
      inner_product += vec1[i] * vec2[i];
   }
   return inner_product;
}

void vector_copy(double vec1[], double vec2[], int dim)
{
   // copy vector components from vec2 to vec1
   for(int i = 0; i < dim; i++) {
      vec1[i] = vec2[i];
   }
}

int pmd(double MatA[][dim], double vecx[], double* eigen, int* power,int dim)
{
   // Power method
   *eigen = - 1.0;
   double vecy[dim];
   double eigen1;
   for(*power = 1; *power < MAXTRIAL; (*power)++) {
      normalize_vector(vecx, dim);
      Mat_mul_vec(MatA, vecy, vecx, dim);
      eigen1 = inner_product(vecy, vecy, dim) / inner_product(vecy, vecx, dim); // Rayleigh quotient
      if(fabs( (eigen1 - *eigen) / (*eigen) ) < EPSILON ) {//convergence judgement
         *eigen = eigen1;
         vector_copy(vecx,vecy,dim);
         return 0;
      }
      *eigen = eigen1;
      vector_copy(vecx,vecy, dim);
   }
   return 1;
}

void random_makex0(double vecx[], int dim)
{
   //make vector x(0) by randomly in order to try power method by another x(0)
   for (int i = 0; i<dim;i++){
      vecx[i] = rand()/RAND_MAX + 0.5; // 0.5 <= vecx[i] < 1.5
   }
}

void print_result(double vecx[], int i1, double eigen, int dim, int power)
{
   //display the result of each calculation of a eigen value nad a eigen vector.
   printf("λ%d = %f\n", i1, eigen);
   printf("vector v%d = (",i1);
   for (int i = 0; i < dim; i++){
       printf("%f, ",vecx[i]);
   }
   printf("\b\b )\n");
   printf("The number of iterations (the number of power) is %d.\n\n", power);
}

void print_error(int i1)
{
   //display error message that λ wasn`t found.
   printf("λ%d wasn't found.\n\n The program aborted.\n", i1);
}
