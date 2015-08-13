#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

int rank;
int size;

//include datatype to be tested
#include "../headers/datatype_ax.h"
MPI_Datatype MPI_particle;

#include "../headers/mpi_pass.h"
#include "../headers/compare_ax.h"
#include "../headers/mpi_io.h"



void func(particle ** buffers,int nEach, int * buf_index){
	int i,j,k;
	for(i=0;i<nEach;i++){
		for(j=0;j<nEach;j++){
			//remove division by 0 from particles interacting with themselves
			if(i==j&&buf_index[0]==buf_index[1]){continue;}
			
			for(k = 0; k<nEach;k++){
				//remove division by 0 from particles interacting with themselves
				if(i==k&&buf_index[0]==buf_index[2]){continue;}
				if(k==j&&buf_index[2]==buf_index[1]){continue;}
				
				findForce(buffers[0]+i,buffers[1]+j,buffers[2]+k);
			}
		}
	}
	

}



int main(int argc, char ** argv){


	//MPI Initialization
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	MPI_Status status_ignore;
	//MPI Particle Initialization
	//MPI_Datatype MPI_particle;
	create_MPI_struct(&MPI_particle);
	MPI_Type_commit(&MPI_particle);

	char * readFName =NULL;
	char * writeFName = NULL;
	char * defaultFName = "default.dat";
	int writeData = 0;
	int compareData = 0;
	//change to allow command line arguments
	if(size == 1){
		writeFName = defaultFName;
		writeData = 1;
		
	}else{
		readFName = defaultFName;
		compareData = 1;
	}
	


	//Setup
		
		
	int nParticles = 727;
	int nEach = nParticles/size;
	double diff;
	particle * buffers[4];
	particle * spare_particle_pointer;
	buffers[0] = calloc(sizeof(particle), nEach);
	buffers[1] = calloc(sizeof(particle), nEach);
	buffers[2] = calloc(sizeof(particle), nEach);
	buffers[3] = calloc(sizeof(particle), nEach);
	
	int buf_index[3] = {rank, rank, rank};
	
	//diff =compareMultipleParticles(buffers[0], buffers[1], nEach);
	//Read or Randomize and print
	if(readFName == NULL){
		initialize_2(buffers[3], nEach);
	}else{
		readParticles(readFName, buffers[3], nEach);
		
		//fprintParticles(stdout, buffers[3], nEach);
	}
	
	
	
	int i;
	for(i=0;i<nEach;i++){
		buffers[0][i] = buffers[3][i];
		buffers[0][i].dvx = 0;
		buffers[0][i].dvy = 0;
		buffers[0][i].dvz = 0;		
		buffers[1][i] = buffers[0][i];
		buffers[2][i] = buffers[0][i];
	}
	
	//diff =compareMultipleParticles(buffers[0], buffers[3], nEach);

	//printf("rank %d diff = %g \t\t expected different \n", rank, diff);
	//Loop
		//Pass
		//Calculate
		//Collect
		
	
	int j;
	for(i=0;i<size;i++){
		//pass right buffer 2
		MPI_pass(buffers, 2, buffers[3], nEach, 1, buf_index);
		for(j=0;j<size;j++){
			//Pass right buffer 1
			MPI_pass(buffers, 1, buffers[3], nEach, 1, buf_index);
			//Do some stuff
			func(buffers, nEach, buf_index);
			
		}
	}



	//Combine results
	for(i=0;i<nEach;i++){
		buffers[0][i].dvx += buffers[1][i].dvx+buffers[2][i].dvx;
		buffers[0][i].dvx /= 6;
		buffers[1][i].dvx = buffers[0][i].dvx;
		buffers[2][i].dvx = buffers[0][i].dvx;
		
		buffers[0][i].dvy += buffers[1][i].dvy+buffers[2][i].dvy;
		buffers[0][i].dvy /= 6;
		buffers[1][i].dvy = buffers[0][i].dvy;
		buffers[2][i].dvy = buffers[0][i].dvy;
		
		buffers[0][i].dvz += buffers[1][i].dvz+buffers[2][i].dvz;
		buffers[0][i].dvz /= 6;
		buffers[1][i].dvz = buffers[0][i].dvz;
		buffers[2][i].dvz = buffers[0][i].dvz;
	}

	if(rank == 0){
		//fprintParticles(stdout, buffers[3], nEach);
		//fprintParticles(stdout, buffers[0], nEach);

	}

	//Check results
	//use buffers[3]
	
	if(compareData == 1){
		diff =compareMultipleParticles(buffers[0], buffers[3], nEach);
		printf("rank %d diff = %g \t\texpect same now \n", rank, diff);
	}
	if(writeData == 1){
		if(writeFName == NULL){
			writeFName = defaultFName;
		}
		writeParticles(writeFName, buffers[0], nEach);
	}

	//freeing and finalization
	free(buffers[0]);
	free(buffers[1]);
	free(buffers[2]);
	free(buffers[3]);


	//MPI Finalization
	MPI_Type_free(&MPI_particle);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();	
}
