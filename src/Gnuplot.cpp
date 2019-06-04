/*
g++  -o ./bin/Gnuplot  ../src/Gnuplot.cpp -lgsl -lgslcblas -lm 
./bin/Gniplot
*/

#include <stdio.h>
#include <gsl/gsl_fit.h>

int main (void)
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

  gsl_fit_linear(x, 1, y, 1, n,
                 &c0, &c1, &cov00, &cov01, &cov11,
                 &sumsq);

  printf ("best fit: Y = %g + %g X\n", c0, c1);
  printf ("covariance matrix:\n");
  printf ("[ %g, %g\n  %g, %g]\n", cov00, cov01, cov01, cov11);
  printf ("sumsq = %g\n", sumsq);
  printf ("\n");
  
  // plot
  FILE *pipe = popen("gnuplot -persist", "w"); // Open a pipe to gnuplot
  if (pipe) // If gnuplot is found
  { 
     fprintf(pipe, "set term wx\n");         // set the terminal
     fprintf(pipe, "set xlabel 'X'\n");
     fprintf(pipe, "set ylabel 'Y'\n");
     fprintf(pipe, "set xrange [0:20]\n");
     fprintf(pipe, "set yrange [2:14]\n");
     fprintf(pipe, "set title '<X,Y> and Linear fit:y=%.4f*x+%.4f'\n",c1,c0);
      
     /* In this case, the datafile is written directly to the gnuplot pipe with no need for a temporary file.
           The special filename '-' specifies that the data are inline; i.e., they follow the command.
        1 sending gnuplot the plot '-' command 
        2 followed by data points 
        3 followed by the letter "e" 
     */
     
     // 1 sending gnuplot the plot '-' command
     fprintf(pipe, "plot '-' title '<x,y>' with points  pt 7 lc rgb 'blue',\
                         '-' title 'Line' with  linespoints  pt  6 lc rgb 'red'\n");
     
     // 2 followed by data points: <x,y>
     for (int i = 0; i < n; i++)
     {
        fprintf(pipe, "%lf %lf\n", x[i], y[i]);
     }
     // 3 followed by the letter "e" 
     fprintf(pipe, "e");
     
     // linear fit
     fprintf(pipe,"\n"); // start a new draw item
     fprintf(pipe, "%lf %lf\n", 0.0, c0+c1*0,0);
     for (int i = 0; i < n; i++)
     {
        fprintf(pipe, "%lf %lf\n", x[i], c0+c1*x[i]);
     }
     fprintf(pipe, "%lf %lf\n", 20.0,c0+c1*20,0);
     fprintf(pipe, "e");
      
     fflush(pipe);
     fprintf(pipe, "exit \n"); // exit gnuplot
     pclose(pipe);             //close pipe
  }
  
  return 0;
}