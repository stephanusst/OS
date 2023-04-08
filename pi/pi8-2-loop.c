#include <omp.h>
#include <stdio.h>

static long num_steps=100000000;//8
double step;

#define PAD 8
#define NUM_THREADS 2

void main(){
  int i, nthreads;
  double pi,sum=0.0;
  double begin, end, time_spent;

  step=1.0/(double) num_steps;
  omp_set_num_threads(NUM_THREADS);

  //Number of thread
  printf("Num= %d\n",NUM_THREADS);
  printf("Num_steps= %d\n", num_steps);

  //clock_t begin=clock();
  begin=omp_get_wtime();
  #pragma omp parallel
  {
    double x;
    #pragma omp for reduction(+:sum)
    for (i=0; i<num_steps; i++){
	      x=(i+0.5)*step;
	      sum=sum+4.0/(1.0+x*x);
	    }
  }
  pi=step*sum;

  end= omp_get_wtime();
  time_spent=(end-begin);

  //report
  printf("Pi=%f\n", pi);
  printf("time= %f\n", time_spent);
}
