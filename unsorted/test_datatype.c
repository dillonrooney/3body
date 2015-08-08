#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

//include datatype to be tested
#include "datatype_ax.h"
//


int main(int argc, char ** argv){
	
	int rank;
	int size;
	MPI_Init(&argc,&argv);
	
	
	MPI_Comm_rank(MPI_COMM_WORLD, rank);
	MPI_Comm_size(MPI_COMM_WORLD, size);
	
	if(rank == 0){
		printf("this is rank 0\n");
		
		
	}else if(rank==1){
		printf("this is rank 1\n");
		
	}
	
	
	
	
	
	
	
	
  MPI_Finalize();
}