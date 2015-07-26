#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

//include datatype to be tested
#include "datatype_ax.h"


MPI_pass(particle ** buffers, int passBuffer, particle * spare_buffer, int nEach, int passDistance, int * buf_index){
	
	particle * spare_particle_pointer;
	//MPI call
	MPI_Sendrecv(buffers[passBuffer], nEach, MPI_particle, (rank+passDistance+size)%size, (rank+passDistance+size)%size, 
		spare_buffer, nEach, MPI_particle, (rank-passDistance+size)%size, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	// Swap buffers
	spare_particle_pointer = buffers[passBuffer];
	buffers[passBuffer] = spare_buffer;
	spare_buffer = spare_particle_pointer
	// Re-calculate what is in each buffer for later use
	buf_index[passBuffer] = (buf_index[passBuffer]+passDistance+size)%size
}

void func(buffers,int nEach, int * buf_index){
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
	MPI_Datatype MPI_particle;
	create_MPI_struct(&MPI_particle);
	MPI_Type_commit(&MPI_particle);





	//Setup
		
		
	int Nparticles;
	int nEach;
	particle * buffers[4];
	particle * spare_particle_pointer;
	buffers[0] = calloc(sizeof(particle), nEach);
	buffers[1] = calloc(sizeof(particle), nEach);
	buffers[2] = calloc(sizeof(particle), nEach);
	buffers[3] = calloc(sizeof(particle), nEach);
	
	int buf_index[3];
	
	//Read or Randomize and print
	//TODO
	
	//Loop
		//Pass
		//Calculate
		//Collect
		
	
	int i,j;
	for(i=0;i<n;i++){
		//pass right buffer 2
		MPI_pass(buffers, 2, buffers[3], nEach, 1, buf_index);
		for(j=0;j<n;j++){
			//Pass right buffer 1
			MPI_pass(buffers, 1, buffers[3], nEach, 1, buf_index);
			//Do some stuff
			func();
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

	//Check results



	//freeing and finalization
	free(buffers[0]);
	free(buffers[1]);
	free(buffers[2]);
	free(buffers[3]);


	//MPI Finalization
	MPI_Type_free(&MPI_particle);
	MPI_Finalize();	
}
