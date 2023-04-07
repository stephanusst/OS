#include <stdio.h>
#include "omp.h"

void main(){
#pragma omp parallel num_threads(2)
  {
    int ID= omp_get_thread_num();
    printf(" Hello(%d)", ID);
    printf(" world(%d)\n",ID);
  }
}