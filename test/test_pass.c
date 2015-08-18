#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

//Global variables
int rank;
int size;
MPI_Datatype MPI_particle;

//include datatype
#include "../headers/datatype_ax.h"

//include mpi_pass to be tested
#include "../headers/mpi_pass.h"




int main(int argc, char ** argv){
	
	
	
	
	//MPI initializtion
	MPI_Init(&argc,&argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//MPI datatype initializtion
	create_MPI_struct(&MPI_particle);
	MPI_Type_commit(&MPI_particle);
	
	
	//Setup
	
	FILE * ofp;		
	int i;	
	int Nparticles;
	int nEach = 10;
	particle * buffers[4];
	particle * spare_particle_pointer;
	buffers[0] = calloc(sizeof(particle), nEach);
	buffers[1] = calloc(sizeof(particle), nEach);
	buffers[2] = calloc(sizeof(particle), nEach);
	buffers[3] = calloc(sizeof(particle), nEach);
	
	int buf_index[3] = {rank, rank, rank};
	
	
	MPI_pass(buffers, 1, nEach, 1, buf_index);
	if(rank == 0){
		ofp = fopen("rk1.dat", "w" );
		fprintf(ofp,"this is rank 0\n");
		for(i=0;i<nEach;i++){
			basicParticle(buffers[1]+i);
			buffers[2][i].x = i;
		}
		fprintParticles(ofp, buffers[1],nEach);
		fprintParticles(ofp, buffers[2],nEach);
		MPI_pass(buffers, 1, nEach, 1, buf_index);
		fprintf(ofp, "buffer 1 should have moved\n");
		fprintParticles(ofp, buffers[1],nEach);
		MPI_Barrier(MPI_COMM_WORLD);
		//Rank 1 is doing stuff
		MPI_Barrier(MPI_COMM_WORLD);
		//Rank ???
		fclose(ofp);
	}else if(rank == 1){
		//Rank 0 is doing stuff
		MPI_pass(buffers, 1, nEach, 1, buf_index);
		MPI_Barrier(MPI_COMM_WORLD);
		printf("this is rank 1\n");
		fprintParticles(stdout,buffers[1], nEach);
		MPI_Barrier(MPI_COMM_WORLD);
		//Rank ???
	}else{
		
		//Rank 0 is doing stuff
		MPI_pass(buffers, 1, nEach, 1, buf_index);
		MPI_Barrier(MPI_COMM_WORLD);
		//Rank 1 is doing stuff
		MPI_Barrier(MPI_COMM_WORLD);
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

	return 0;
}
