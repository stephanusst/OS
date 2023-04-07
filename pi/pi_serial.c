#include <stdio.h>
#include <time.h>
#include <omp.h>
static long num_steps=100000000;//8 zeros
double step;

int main(){
  int i;
  double x,pi, sum=0.0;
  step=1.0/(double) num_steps;
  double begin, end, time_spent;

  //clock_t begin=clock();
  begin=omp_get_wtime();
  for (i=0;i<num_steps;i++){
    x=(i+0.5)*step;
    sum=sum+4.0/(1.0+x*x);
  }
  //clock_t end=clock();
  end=omp_get_wtime();
  time_spent=end-begin;

  pi=step*sum;

  printf("pi= %f\n",pi);
  printf("time= %f\n", time_spent);
  return 0;
}

