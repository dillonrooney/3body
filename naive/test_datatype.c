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
	particle thing1,thing2;
	particle things[15];
	int i;
	MPI_Status status_ignore;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	MPI_Datatype MPI_particle;
	create_MPI_struct(&MPI_particle);
	MPI_Type_commit(&MPI_particle);
	if(rank == 0){
		for(i=0;i<15;i++){
			basicParticle(things + i);
			things[i].z = i*i;
		}
		basicParticle(&thing1);
		printf("this is rank 0\n");
		MPI_Send(things, 10, MPI_particle, 1, 0, MPI_COMM_WORLD);


		
	}else if(rank==1){
		printf("this is rank 1\n");
		MPI_Recv(things, 10, MPI_particle, 0, 0, MPI_COMM_WORLD, &status_ignore);
		fprintParticles(stdout, things, 15);
	}
	
	
	
	
	
	
	

	MPI_Type_free(&MPI_particle);
	MPI_Finalize();	
}
