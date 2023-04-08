#include <omp.h>
#include <stdio.h>
#include <time.h>

static long num_steps=100000000;//8
double step;
#define NUM_THREADS 2

void main(){
  int i, nthreads; 
  double pi, sum[NUM_THREADS];
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
    int i, id, nthrds;
    double x; //create a scalar local to each thread to accumulate partial sums
    id= omp_get_thread_num();
    nthrds= omp_get_num_threads();
    if (id==0)
      nthreads= nthrds;
    for (i=id, sum[id]=0.0; i<num_steps; i=i+nthrds){
      x=(i+0.5)*step;
      sum[id]+=4.0/(1.0+x*x);
    }
  }
  //clock_t end = clock();
  end= omp_get_wtime();
  time_spent=(end-begin);

  for (i=0,pi=0.0;i<nthreads;i++)
    pi +=sum[i]*step;

  //report
  printf("Pi=%f\n", pi);
  printf("time= %f\n", time_spent);
}
