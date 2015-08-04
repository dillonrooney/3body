#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

//global variables
	int rank;
	int size;
	MPI_Datatype MPI_particle;

//include datatype to be tested
#include "datatype_ax.h"
//
//include compare
#include "compare_ax.h"
//include read and write functions
#include "mpi_io.h"


int main(int argc, char ** argv){
	

	MPI_Init(&argc,&argv);
	particle thing1,thing2;
	int nEach = 15;
	particle things1[nEach];
	particle things2[nEach];
	int i;
	MPI_Status status_ignore;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//MPI_Datatype MPI_particle;
	create_MPI_struct(&MPI_particle);
	MPI_Type_commit(&MPI_particle);
	
	
	for(i=0;i<nEach;i++){
		basicParticle(things1+i);
	}
	
	writeParticles("testFile.dat",things1, nEach);
	MPI_Barrier(MPI_COMM_WORLD);
	readParticles("testFile.dat", things2, nEach);
	
	double difference = compareMultipleParticles(things1, things2, nEach);
	//difference = 1;
	if(difference == 0){
		printf("rank %d read eqal\n", rank);
	}else {
		printf("rank %d difference = %g\n", rank, difference);
	}
	
	int j;
	for(i=0;i<nEach;i++){
		things2[i].x += i*rank*1E-17;
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	difference = compareMultipleParticles(things1, things2, nEach);
	if(difference == 0){
		printf("rank %d read eqal\n", rank);
	}else {
		printf("rank %d difference = %g\n", rank, difference);
	}
	
	
	

	MPI_Type_free(&MPI_particle);
	MPI_Finalize();	
}
