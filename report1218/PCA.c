#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// when reading a line of a file, the upper limit to the number of read characters
#define MAXLENOFLINE 2000

// the number of trials to find eigen vectors when pmd can`t by a vector_x(0)
#define MAXTRIAL 3

// the number in order for judging whether or not a eigenvalue comes to convergence.
#define EP1 1e-15

// when excecuting Power method, the upper limit to the number of power of vector_x(0).
#define MAXPOWER 100000


// Prototypes

// input data from file
void input_data(FILE*, int*, int*);

// make a transpose matrix of MatrixX(dataX) from file
void make_tMatX(FILE*, double**, int);

// display input data and MatrixC
void display_data_MatC(double**, double**, int, int);

// Change MatC to "X - eigenvalue*vecx*(t^vecx)"(=B)
void make_MatB(double**, double[], double, int);

// normalize vector_x
void normalize_vector(double[], int);

// calculate vecy ( = MatC * vecx )
void Mat_mul_vec(double**, double[], double[], int);

// calculate <vec1,vec2>
double inner_product(double[], double[], int);

// copy each vector component from vec2 to vec1
void vector_copy(double[], double[], int);

// Power method
int pmd(double**, double[], double[], double*, int*, int);

// make vector x(0) by randomly in order to try power method by another x(0)
void random_makex0(double[], int);

// display the result of each calculation of a eigen vector.
void print_result(double[], int, int, int);

// display error message that a eigenvector wasn`t     found.
void print_error(int, int);

// Change tMatX to MatC(covariance matrix)
void make_MatC(double**, double**, int, int);

// calculate nfvector principal component vector and save them to convertedtMatX.
void cal_pricomponent(double**, double**, double[], int, int, int);

// display the result of calculation of principal components.
void print_pricomponents(double**, int, int, int);


/*
 * filename: file's name you perform PCA to
 * numfindvectors: The numbef of principal direction vectors you want to find ( 1 <= numfindvectors <= n (n=dim) )
 *                numfindvectors is 1 by defalut.
 */
int main(int argc, char const* argv[]) // ./program "filename" "numfindvectors"
{
   // The Code about input from the file is as below.
   // this program uses 'comma', 'space', and 'tab' as delimiters.
   FILE* fp;
   int   rows = 0; // row of tMatX
   int   cols = 0; // column of tMatX
   int   row;      // in order for "for loop"

   if(argc < 3 || 4 < argc) {
      printf("Command-line input needs to be below. \n");
      printf("./program filename numfindvectors(the number of principal vectors you want to find)"
             "(-display(If you add -display option, input data, the covariance matrix and"
             " principal components are displayed.))\n\nThe program aborted.\n\n");

      return 1;
   }
   if((fp = fopen(argv[1], "r")) == NULL) {
      printf("An error was encountered while reading the file.\n\nThe program aborted.\n\n");

      return 1;
   }

   input_data(fp, &rows, &cols);   // input data from file

   // make 2-dimention array dynamically(t^Matx)
   double** tMatX;
   double*  base_tMatX;
   tMatX      = (double**) malloc(sizeof(double*) * rows);
   base_tMatX = (double*) malloc(sizeof(double) * rows * cols);
   for(row = 0; row < rows; row++) {
      tMatX[row] = base_tMatX + row * cols;
   }

   make_tMatX(fp, tMatX, rows); // make a transpose matrix of MatrixX(dataX) from file

   fclose(fp);
   // The Code about inputing from the file is as above.


   // Variables Declaratioin
   int     numfindvectors;  // The numbef of eigen vectors you want to find
   int     nfvector;        // in order for "for loop"
   int     dim   = cols;    // (it doesn`t mean mathmatical dim(MatrixC)), it means MatrixC is dim*dim.
   double  eigen = 0.0;     // eigenvalue
   int     power;           // In pmd, this is used as iteration variable. (The number of iterations)
   double* vecx;            // x_(k)
   double* vecy;            // vecy = MatC * vecx
   int     checker;         // this contains the information about whether or not pmd found a eigenvector correctly.
   int     display = 0;     // If this is 1, input data, covariance matrix and principal components are calculated and
                            // displayed. If 0, not.
   int      trial;          // In order for MAXTRIAL`s for loop
   double** convertedtMatX; // used to contain principal components when display == 1.
   double*  base_convertedtMatX;
   // tMatX : a transpose matrix of "MatrixX" in Report2017-1.pdf
   // MatC : The covariance matrix of MatrixX.
   // int rows : row of tMatX
   // int cols : column of tMatX
   vecx = (double*) malloc(sizeof(double) * dim);
   vecy = (double*) malloc(sizeof(double) * dim); // vecy = MatC * vecx

   // Define the numfindvectors (the numbef of eigen vectors you want to find)
   numfindvectors = atoi(argv[2]);
   if(numfindvectors > dim || numfindvectors < 1) {
      printf("The number of eigenvectors are %d.\n", dim);
      printf("numfindvectors should be %d at most and 1 at least.\n\nThe program aborted.\n\n", dim);

      return 1;
   }

   // make 2-dimention array dynamically(MatC)
   double** MatC;
   double*  base_MatC;
   MatC      = (double**) malloc(sizeof(double*) * dim);
   base_MatC = (double*) calloc(dim * dim, sizeof(double));
   for(row = 0; row < dim; row++) {
      MatC[row] = base_MatC + row * dim;
   }
   make_MatC(MatC, tMatX, rows, cols); // make MatrixC from a transpose matrix of MatrixX.

   // if -display opition is ON.
   if(argc == 4) {
      if(strncmp(argv[3], "-dis", 4) == 0) {
         display = 1;

         // make convertedtMatX which contains projected tMatX
         convertedtMatX      = (double**) malloc(sizeof(double*) * rows);
         base_convertedtMatX =   (double*) calloc(rows * numfindvectors, sizeof(double));
         for(row = 0; row < rows; row++) {
            convertedtMatX[row] = base_convertedtMatX + row * numfindvectors;
         }

         // display input data and MatrixC
         display_data_MatC(tMatX, MatC, rows, cols);
      }
   }


   // find the eigenvalues by power method
   for(nfvector = 1; nfvector <= numfindvectors; nfvector++) {
      make_MatB(MatC, vecx, eigen, dim); // Change MatC to "C - eigenvalue*vecx*t^vecx"(=B)
      for(row = 0; row < dim; row++) {
         vecx[row] = 1.0;
      }
      for(trial = 0; trial < MAXTRIAL; trial++) {
         if((checker = pmd(MatC, vecx, vecy, &eigen, &power, dim)) == 0) { // excecute the power method
            if(display) {
               cal_pricomponent(tMatX, convertedtMatX, vecx, nfvector, rows, cols);
            }
            print_result(vecx, nfvector, cols, power);
            break;
         } else {
            random_makex0(vecx, dim);           // try power method by another vector_x(0)
         }
      }
      if(trial == MAXTRIAL) {                   // When nfvector eigenvalue wasn`t found.
         print_error(nfvector, numfindvectors); // display an error message that how many eigenvectors can`t be found.
         return 1;
      }
   }

   if(display) {
      print_pricomponents(convertedtMatX, rows, cols, numfindvectors);
      free(base_convertedtMatX);
      free(convertedtMatX);
   }
   free(vecx);
   free(vecy);
   free(base_tMatX);
   free(tMatX);
   free(base_MatC);
   free(MatC);

   printf("The program successfully terminated.\n\n");

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

void make_tMatX(FILE* fp, double** tMatX, int rows)
{
   // make a transpose matrix of MatrixX(dataX) from file
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
         tMatX[row][0] = bufnum;
         col = 1;
      }
      while((bufchar = strtok(NULL, " \t,")) != NULL) {
         if(((bufnum = atof(bufchar)) == 0) && *bufchar != '0') {
            continue;
         } else {
            tMatX[row][col] = bufnum;
            col++;
         }
      }
   }
}

void display_data_MatC(double** tMatX, double** MatC, int rows, int cols)
{
   // display input data and MatrixC
   int row, col;

   // display input data
   printf("A transpose matrix of MatrixX (Input data) is as below.\n");
   for(row = 0; row < rows; row++) {
      printf("data No.%3d = ( ", row + 1);
      for(col = 0; col < cols; col++) {
         printf("%9f, ", tMatX[row][col]);
      }
      printf("\b\b )\n");
   }
   printf("\n");

   // display MatrixC
   printf("MatrixC (covariance matrix) is as below.\n");
   for(row = 0; row < cols; row++) {
      for(col = 0; col < cols; col++) {
         printf("%9f ", MatC[row][col]);
      }
      printf("\b\n");
   }
   printf("\n");
}

void make_MatB(double** MatC, double vecx[], double eigen, int dim)
{
   // Change MatC to "X - eigenvalue*vecx*(t^vecx)"(=B)
   int row, col;
   for(row = 0; row < dim; row++) {
      for(col = 0; col < dim; col++) {
         MatC[row][col] -= eigen * vecx[row] * vecx[col];
      }
   }
}

void normalize_vector(double vecx[], int dim)
{
   // normalize vector_x
   double sum = 0;
   double norm;
   int    row;
   for(row = 0; row < dim; row++) {
      sum += pow(vecx[row], 2);
   }
   norm = sqrt(sum);
   for(row = 0; row < dim; row++) {
      vecx[row] /= norm;
   }
}

void Mat_mul_vec(double** MatC, double vecy[], double vecx[], int dim)
{
   // calculate vecy ( = MatC * vecx )
   int row, col;
   for(row = 0; row < dim; row++) {
      vecy[row] = 0.0;
      for(col = 0; col < dim; col++) {
         vecy[row] += MatC[row][col] * vecx[col];
      }
   }
}

double inner_product(double vec1[], double vec2[], int dim)
{
   // calculate <vec1,vec2>
   double inner_product = 0;
   for(int row = 0; row < dim; row++) {
      inner_product += vec1[row] * vec2[row];
   }

   return inner_product;
}

void vector_copy(double vec1[], double vec2[], int dim)
{
   // copy each vector component from vec2 to vec1
   for(int row = 0; row < dim; row++) {
      vec1[row] = vec2[row];
   }
}

int pmd(double** MatC, double vecx[], double vecy[], double* eigen, int* power, int dim)
{
   // Power method return 0(come to convergence), 1(not)
   *eigen = -1.0;
   double eigen1;
   for(*power = 1; *power < MAXPOWER; (*power)++) {
      normalize_vector(vecx, dim);
      Mat_mul_vec(MatC, vecy, vecx, dim);                                       // vecy = MatC * vecx
      eigen1 = inner_product(vecy, vecy, dim) / inner_product(vecy, vecx, dim); // Rayleigh quotient
      if(fabs((eigen1 - *eigen) / (*eigen)) < EP1) {                            // convergence judgement
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
   for(int row = 0; row < dim; row++) {
      vecx[row] = rand() / RAND_MAX + 0.5; // 0.5 <= vecx[row] < 1.5
   }
}

void print_result(double vecx[], int nfvector, int cols, int power)
{
   // display the result of each calculation of a eigen vector.
   printf("the %2d principal vector = (", nfvector);
   for(int col = 0; col < cols; col++) {
      printf("%9f, ", vecx[col]);
   }
   printf("\b\b )\n");

   printf("The number of iterations (the number of power) is %2d.\n\n", power);
}

void print_error(int nfvector, int numfindvectors)
{
   // display error message that a eigenvector wasn`t found.
   if(numfindvectors == nfvector) {
      printf("The %d principal vector wasn't found.\n", nfvector);
   } else {
      printf("The %d principal vector wasn't found.\nTherefore, %d principal vectors were"
             " not found.\n\n The program aborted.\n\n", nfvector, numfindvectors - nfvector + 1);
   }
}

void make_MatC(double** MatC, double** tMatX, int rows, int cols)
{
   // Change tMatX to MatC(covariance matrix)
   // tMatX means a transpose matrix of "MatrixX" in Report2017-1.pdf(
   // https://www.google.com/url?q=https%3A%2F%2Fwww.dropbox.com%2Fs%2F90k0qi1n1qcqk3g%2FReport2017-1.pdf%3Fdl%3D0&sa=D&sntz=1&usg=AFQjCNHzLZGT0fVnsCbjEmLJXksMepp5fg
   // )

   int     col1, col2, row; // These are in order for "for loop".
   double* mean_of_col;     // This is X(a)-bar

   // make X(a)-bar
   mean_of_col = (double*) calloc(cols, sizeof(double));
   for(col1 = 0; col1 < cols; col1++) {
      for(row = 0; row < rows; row++) {
         mean_of_col[col1] += tMatX[row][col1];
      }
      mean_of_col[col1] /= rows;
   }

   for(col1 = 0; col1 < cols; col1++) {
      for(col2 = 0; col2 < cols; col2++) {
         for(row = 0; row < rows; row++) {
            MatC[col1][col2] += (tMatX[row][col1] - mean_of_col[col1]) * (tMatX[row][col2] - mean_of_col[col2]);
         }
         MatC[col1][col2] /= (rows - 1.0);
      }
   }

   free(mean_of_col);
}

void cal_pricomponent(double** tMatX, double** convertedtMatX, double vecx[], int nfvector, int rows, int cols)
{
   // calculate nfvector principal component vector and save them to convertedtMatX.
   for(int row = 0; row < rows; row++) {
      for(int col = 0; col < cols; col++) {
         convertedtMatX[row][nfvector - 1] += tMatX[row][col] * vecx[col];
      }
   }
}

void print_pricomponents(double** convertedtMatX, int rows, int cols, int numfindvectors)
{
   // display the result of calculation of principal components.
   // principal component = (tMatx) * (Matrix of vecx(1~numfindvectors))
   printf("principal components (a transpose matrix of MatrixX"
          " converted with change of basis by principal vectors) are as below.\n");
   for(int row = 0; row < rows; row++) {
      printf("data No.%3d = ( ", row + 1);
      for(int col = 0; col < numfindvectors; col++) {
         printf("%9f, ", convertedtMatX[row][col]);
      }
      if(numfindvectors == cols) { // Just in order for visibility
         printf("\b\b )\n");
      } else {
         printf("...\n");          // This "..." indicates all components don't be displayed.
      }
   }
   printf("\n");
}
