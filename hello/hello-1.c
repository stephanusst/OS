#include <stdio.h>
#include "omp.h"

void main(){
omp_set_num_threads(2);
#pragma omp parallel
	{
	  int ID= omp_get_thread_num();
	  printf(" Hello(%d)", ID);
	  printf(" world(%d)\n",ID);
	}
}
