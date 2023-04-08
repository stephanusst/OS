#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long num_steps=10;//8
double step;

#define PAD 8
#define NUM_THREADS 2

void main(int argc, char *argv[]){
  int i, nthreads; 
  double pi, sum[NUM_THREADS][PAD];
  double begin, end, time_spent;

  num_steps=atoi(argv[1]);
  step=1.0/(double) num_steps;
  omp_set_num_threads(NUM_THREADS);

  //Number of thread
  printf("Num= %d\n",NUM_THREADS);
  printf("Num_steps= %d\n", num_steps);

  //clock_t begin=clock();
  begin=omp_get_wtime();
  #pragma omp parallel
  {
	long i;
        int id, nthrds;
	double x;
	id= omp_get_thread_num();
	nthrds= omp_get_num_threads();
	if (id==0)
	  nthreads= nthrds;
	    for (i=id, sum[id][0]=0.0; i<num_steps; i=i+nthrds){
	      x=(i+0.5)*step;
	      sum[id][0]+=4.0/(1.0+x*x);
              printf("id:%i, li:%i, sum=%f\n", id, i,  sum[id][0]);
	    }
  }
  //clock_t end = clock();
  end= omp_get_wtime();
  time_spent=(end-begin);

  for (i=0,pi=0.0;i<nthreads;i++)
	pi +=sum[i][0]*step;

  //report
  printf("Pi=%1.16f\n", pi);
  printf("time= %f\n", time_spent);
}
