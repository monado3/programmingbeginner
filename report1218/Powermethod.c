#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// when reading a line of a file, the upper limit to the number of read characters
#define MAXLENOFLINE 2000

// the number of trials to find a eigenvalue when pmd can`t by a vector_x(0)
#define MAXTRIAL 3

// the number in order for judging whether or not a eigenvalue comes to convergence.
#define EPSILON 1e-15

// when excecuting Power method, the upper limit to the number of power of vector_x(0).
#define MAXPOWER 100000


// Prototypes

// input data from file
void input_data(FILE*, int*, int*);

// make a MatrixA from file
void make_MatA(FILE*, double**, int);

// Change MatA to "A - eigenvalue*vecx*(t^vecx)"(=B)
void make_MatB(double**, double[], double, int);

// normalize vector_x
void normalize_vector(double[], int);

// calculate vecy ( = MatA * vecx )
void Mat_mul_vec(double**, double[], double[], int);

// calculate <vec1,vec2>
double inner_product(double[], double[], int);

// copy each vector component from vec2 to vec1
void vector_copy(double[], double[], int);

// Power method
int pmd(double**, double[], double[], double*, int*, int);

// make vector x(0) by randomly in order to try power method by another x(0)
void random_makex0(double[], int);

// display the result of each calculation of a eigenvalue.
void print_result(double[], int, double, int, int);

// display error message that a eigenvalue wasn`t found.
void print_error(int, int);


/*
 * filename: file's name which contains Matrix(n*n) you want to find eigenvalues
 * numfindeigen: The numbef of eigenvalues you want to find ( 1 <= numfindeigen <= n (n=dim) )
 *               numfindeigen is 1 by defalut.
 */
int main(int argc, char const* argv[]) // ./program "filename" "numfindeigen"
{
   // The Code about input from the file is as below.
   // this program uses 'comma', 'space', and 'tab' as delimiters.
   FILE* fp;
   int   row = 0; // row of MatA
   int   col = 0; // column of MatA
   int   i, j;

   if(argc == 1 || 3 < argc) {
      printf("Command-line input needs to be below. \n");
      printf(
             "./program filename (numfindeigen(the number of eigenvalues you want to find))\n\nThe program aborted.\n\n");
      return 1;
   }
   if((fp = fopen(argv[1], "r")) == NULL) {
      printf("An error was encountered while reading the file.\n\nThe program aborted.\n\n");
      return 1;
   }

   input_data(fp, &row, &col);

   // make 2-dimention array dynamically(MatA)
   double** MatA;
   double*  base_MatA;
   MatA      = (double**) malloc(sizeof(double*) * row);
   base_MatA = (double*) malloc(sizeof(double) * row * col);
   for(i = 0; i < row; i++) {
      MatA[i] = base_MatA + i * col;
   }

   make_MatA(fp, MatA, row);

   fclose(fp);
   // The Code about inputing from the file is as above.


   // display input MatrixA
   printf("MatrixA (Input data) is as below.\n");
   for(i = 0; i < row; i++) {
      for(j = 0; j < col; j++) {
         printf("%9f ", MatA[i][j]);
      }
      printf("\b\n");
   }
   printf("\n");


   // Variables Declaratioin
   int     numfindeigen; // The number of eigenvalues you want to find
   int     dim   = row;  // dim=row=col=n (it doesn`t mean mathmatical dim(MatrixA))
   double  eigen = 0.0;  // eigenvalue
   double* vecx;         // x_(k)
   double* vecy;         // vecy = MatA * vecx
   int     power;        // In pmd, this is used as iteration variable. (The number of iterations)
   int     i1, i2;       // these are in order for "for loop".
   int     checker;      // this contains the information about whether or not pmd found a eigenvlaue correctly.
   // int row : row of MatA
   // int col : column of MatA
   // (In this problam, MatrixA is n*n, then row=col=n=dim)

   vecx = (double*) malloc(sizeof(double) * dim); // x_k(0)
   vecy = (double*) malloc(sizeof(double) * dim); // vecy = MatA * vecx

   // When the input matrix isn`t a square matrix.
   if(row != col) {
      printf("The input Matrix isn't a square matrix.\n\nThe program aborted.\n\n");
      return 1;
   }

   // Define the numfindeigen (the number of eigenvalues you want to find)
   if(argc == 2) {
      numfindeigen = 1;
   } else {
      numfindeigen = atoi(argv[2]);
      if(numfindeigen > dim || numfindeigen < 1) {
         printf("The number of eigenvalues are %d.\n", dim);
         printf("numfindeigen should be %d at most and 1 at least.\n\nThe program aborted.\n\n", dim);
         return 1;
      }
   }

   // find the eigenvalues by power method
   for(i1 = 1; i1 <= numfindeigen; i1++) {
      make_MatB(MatA, vecx, eigen, dim); // Change MatA to "A - eigenvalue*vecx*t^vecx"(=B)
      for(i2 = 0; i2 < dim; i2++) {
         vecx[i2] = 1.0;
      }
      for(i2 = 0; i2 < MAXTRIAL; i2++) {
         if((checker = pmd(MatA, vecx, vecy, &eigen, &power, dim)) == 0) { // excecute the power method
            print_result(vecx, i1, eigen, dim, power);
            break;
         } else {
            random_makex0(vecx, dim);   // try power method by another vector_x(0)
         }
      }
      if(i2 == MAXTRIAL) {              // When i2eigenvalue wasn`t found.
         print_error(i1, numfindeigen); // display an error message that how many eigenvalues can`t be found.
         return 1;
      }
   }
   free(vecx);
   free(vecy);
   free(base_MatA);
   free(MatA);
   printf("\nThe program successfully terminated.\n\n");

   return 0;
}

void input_data(FILE* fp, int* rows, int* cols)
{
   // input data from file
   char*  bufchar;
   double bufnum;
   char   temp[MAXLENOFLINE];

   while(fgets(temp, MAXLENOFLINE, fp) != NULL) {
      (*rows)++;
   }

   bufnum = atof(bufchar = strtok(temp, " \t,"));
   if(((bufnum = atof(bufchar)) == 0) && *bufchar != '0') {
   } else {
      (*cols)++;
   }

   while((bufchar = strtok(NULL, " \t,")) != NULL) {
      if(((bufnum = atof(bufchar)) == 0) && *bufchar != '0') {
         continue;
      } else {
         (*cols)++;
      }
   }

   fseek(fp, 0, SEEK_SET);
}

void make_MatA(FILE* fp, double** MatA, int rows)
{
   // make a matrixA from file
   int    row, col;
   char*  bufchar;
   double bufnum;
   char   temp[MAXLENOFLINE];

   for(row = 0; row < rows; row++) {
      fgets(temp, MAXLENOFLINE, fp);
      bufnum = atof(bufchar = strtok(temp, " \t,")); // 'comma', 'space', and 'tab' as delimiters.
      if((bufnum = atof(bufchar)) == 0 && *bufchar != '0') {
         col = 0;
      } else {
         MatA[row][0] = bufnum;
         col = 1;
      }
      while((bufchar = strtok(NULL, " \t,")) != NULL) {
         if(((bufnum = atof(bufchar)) == 0) && *bufchar != '0') {
            continue;
         } else {
            MatA[row][col] = bufnum;
            col++;
         }
      }
   }
}

void make_MatB(double** MatA, double vecx[], double eigen, int dim)
{
   // Change MatA to "A - eigenvalue*vecx*(t^vecx)"(=B)
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

void Mat_mul_vec(double** MatA, double vecy[], double vecx[], int dim)
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
   // copy each vector component from vec2 to vec1
   for(int i = 0; i < dim; i++) {
      vec1[i] = vec2[i];
   }
}

int pmd(double** MatA, double vecx[], double vecy[], double* eigen, int* power, int dim)
{
   // Power method
   *eigen = -1.0;
   double eigen1;
   for(*power = 1; *power < MAXPOWER; (*power)++) {
      normalize_vector(vecx, dim);
      Mat_mul_vec(MatA, vecy, vecx, dim);                                       // vecy = MatA * vecx
      eigen1 = inner_product(vecy, vecy, dim) / inner_product(vecy, vecx, dim); // Rayleigh quotient
      if(fabs((eigen1 - *eigen) / (*eigen)) < EPSILON) {                        // convergence judgement
         *eigen = eigen1;
         vector_copy(vecx, vecy, dim);
         normalize_vector(vecx, dim);
         return 0;
      }
      *eigen = eigen1;
      vector_copy(vecx, vecy, dim);
   }
   return 1; // When eigenvalue don`t come to convergence.
}

void random_makex0(double vecx[], int dim)
{
   // make vector x(0) by randomly in order to try power method by another x(0)
   for(int i = 0; i < dim; i++) {
      vecx[i] = rand() / RAND_MAX + 0.5; // 0.5 <= vecx[i] < 1.5
   }
}

void print_result(double vecx[], int i1, double eigen, int dim, int power)
{
   // display the result of each calculation of a eigen value and a eigen vector.
   printf("Eigenvalue%2d = %f\n", i1, eigen);
   printf("vector v%2d = (", i1);
   for(int i = 0; i < dim; i++) {
      printf("%9f, ", vecx[i]);
   }
   printf("\b\b )\n");
   printf("The number of iterations (the number of power) is %d.\n\n", power);
}

void print_error(int i1, int numfindeigen)
{
   // display error message that eigenvalue wasn`t found.
   if(numfindeigen == i1) {
      printf("Eigenvalue%d wasn't found.\n", i1);
   } else {
      printf("Eigenvalue%d wasn't found.\nTherefore, %d eigenvalues were"
             " not found.\n\nThe program aborted.\n\n", i1, numfindeigen - i1 + 1);
   }
}
