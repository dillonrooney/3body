#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

//include datatype
#include "datatype_ax.h"

//include mpi_pass to be tested
#include "mpi_pass"


//Global variables
int rank;
int size;




int main(int argc, char ** argv){
	
	
	
	
	//MPI initializtion
	MPI_Init(&argc,&argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//MPI datatype initializtion
	MPI_Datatype MPI_particle;
	create_MPI_struct(&MPI_particle);
	MPI_Type_commit(&MPI_particle);
	
	
	//Setup
		
		
	int Nparticles;
	int nEach = 10;
	particle * buffers[4];
	particle * spare_particle_pointer;
	buffers[0] = calloc(sizeof(particle), nEach);
	buffers[1] = calloc(sizeof(particle), nEach);
	buffers[2] = calloc(sizeof(particle), nEach);
	buffers[3] = calloc(sizeof(particle), nEach);
	
	int buf_index[3];
	
	
	if(rank == 0){
		printf("this is rank 0\n")
		//Rank 0 is doing stuff
		MPI_barrier(MPI_COMM_WORLD);
		//Rank 1 is doing stuff
		MPI_barrier(MPI_COMM_WORLD);
		//Rank ???
		
	}else if(rank == 1){
		//Rank 0 is doing stuff
		MPI_barrier(MPI_COMM_WORLD);
		printf("this is rank 1\n");
		MPI_barrier(MPI_COMM_WORLD);
		//Rank ???
	}else{
		
		//Rank 0 is doing stuff
		MPI_barrier(MPI_COMM_WORLD);
		//Rank 1 is doing stuff
		MPI_barrier(MPI_COMM_WORLD);
		//Rank ???
	}
	
	
	
	
	
	//freeing and finalization
	free(buffers[0]);
	free(buffers[1]);
	free(buffers[2]);
	free(buffers[3]);


	//MPI Finalization
	MPI_Type_free(&MPI_particle);
	MPI_Finalize();	

	
}