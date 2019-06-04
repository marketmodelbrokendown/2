/*
g++ -o  ./bin/GSL_fit ../src/GSL.cpp -lgsl -lgslcblas -lm
./bin/GSL_fit 
*/
#include<iostream>
#include<stdio.h>
#include <gsl/gsl_fit.h>
using namespace std;
int main()
{
    FILE *fw=fopen("home:\\yyu\\Desktop\\Practices\\Bonus\\data\\*.csv","r");
    int i,j;
    double a[20][2];
    for(i=0;i<20;i++)
            {
                for(j=0;j<2;j++)
                {
                    fscanf(fw,"%lf",&a[i][j]);
                          
                }
                  
            }  
    fclose(fw);   
  int n=20;
  double x[20];
  double y[20];
  for(i=0;i<20;i++)
  {
    x[i]=a[i][0];
  }
  for(i=0;i<20;i++)
  {
     y[i]=a[i][1];
  }
  
  double c0, c1, cov00, cov01, cov11, sumsq;

  gsl_fit_linear (x, 1, y, 1, n,
                   &c0, &c1, &cov00, &cov01, &cov11,
                   &sumsq);

  printf ("best fit: Y = %g + %g X\n", c0, c1);
  printf ("covariance matrix:\n");
  printf ("[ %g, %g\n  %g, %g]\n",
          cov00, cov01, cov01, cov11);
  printf ("sumsq = %g\n", sumsq);

  printf ("\n");
    return 0;
}