//in c file, include
/*
#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

//include datatype to be tested
#include "datatype_ax.h"

*/




MPI_pass(particle ** buffers, int passBuffer, particle * spare_buffer, int nEach, int passDistance, int * buf_index){
	
	//check for NULL pointers
	if(buffers == NULL || buffers[passBuffer]==NULL ||buf_index == NULL || spare_buffer == NULL){
		printf("error: invalid call to MPI_pass: NULL argument detected\n")
	}
	
	
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