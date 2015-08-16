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
#include "../headers/cla.h"



void func(particle ** buffers, int * nEach, int * buf_index){
	int i,j,k;
	for(i=0;i<nEach[0];i++){
		for(j=0;j<nEach[1];j++){
			//remove division by 0 from particles interacting with themselves
			if(i==j&&buf_index[0]==buf_index[1]){continue;}
			
			for(k = 0; k<nEach[2];k++){
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
	
	clOptions options;
	if(getCla(argc, argv, &options)){
		//NOTHING TO WORRY ABOUT
	}else{
		printf("command line options failure\n");
		
		return 1;
	}
	
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
	

	//Setup
		
		
	int nParticles = options.nParticles;
	int nEachMax = pieceSize(nParticles, size, 0);
	double diff;
	particle * buffers[4];
	particle * spare_particle_pointer;
	buffers[0] = calloc(sizeof(particle), nEachMax);
	buffers[1] = calloc(sizeof(particle), nEachMax);
	buffers[2] = calloc(sizeof(particle), nEachMax);
	buffers[3] = calloc(sizeof(particle), nEachMax);
	
	int buf_index[3] = {rank, rank, rank};
	int nEach[3];
	nEach[0] = pieceSize(nParticles, size, rank);
	nEach[1] = pieceSize(nParticles, size, rank);
	nEach[2] = pieceSize(nParticles, size, rank);
	
	//diff =compareMultipleParticles(buffers[0], buffers[1], nEachMax);
	//Read or Randomize and print
	if(options.Input == 1){
		readParticles(readFName, buffers[3], nParticles, size, rank);
	}else if(options.genFunction == 2){
		initialize_2(buffers[3], nEachMax);
		
		//fprintParticles(stdout, buffers[3], nEachMax);
	}else{
		
	}
	
	
	
	int i;
	for(i=0;i<nEachMax;i++){
		buffers[0][i] = buffers[3][i];
		buffers[0][i].dvx = 0;
		buffers[0][i].dvy = 0;
		buffers[0][i].dvz = 0;		
		buffers[1][i] = buffers[0][i];
		buffers[2][i] = buffers[0][i];
	}
	
	//diff =compareMultipleParticles(buffers[0], buffers[3], nEachMax);

	//printf("rank %d diff = %g \t\t expected different \n", rank, diff);
	//Loop
		//Pass
		//Calculate
		//Collect
		
	
	int j;
	for(i=0;i<size;i++){
		//pass right buffer 2
		MPI_pass(buffers, 2, buffers[3], nEachMax, 1, buf_index);
		nEach[2] = pieceSize(nParticles, size, buf_index[2]);
		for(j=0;j<size;j++){
			//Pass right buffer 1
			MPI_pass(buffers, 1, buffers[3], nEachMax, 1, buf_index);
			nEach[1] = pieceSize(nParticles, size, buf_index[1]);
			//Do some stuff
			func(buffers, nEach, buf_index);
			
		}
	}



	//Combine results
	for(i=0;i<nEachMax;i++){
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
		//fprintParticles(stdout, buffers[3], nEachMax);
		//fprintParticles(stdout, buffers[0], nEachMax);

	}

	//Check results
	//use buffers[3]
	
	if(options.compareData == 1){
		diff =compareMultipleParticles(buffers[0], buffers[3], nEach[0]);
		printf("rank %d diff = %g\n", rank, diff);
	}
	if(options.writeData == 1){
		writeParticles(options.writeFName, buffers[0], nParticles, size, rank);
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
