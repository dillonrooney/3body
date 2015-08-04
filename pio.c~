#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

//include datatype
//#include "datatype_ax.h"
//
int rank;
int size;



int main(int argc, char ** argv){
	

	MPI_Init(&argc,&argv);
	int nEach = 4;
	int data1[nEach];
	int data2[nEach];
	
	int i;
	

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	for(i=0;i<nEach;i++){
		data1[i] = rank*10 + i+1;
	}
	
	MPI_File pofp, pifp;
	/*
	MPI_File_open(MPI_COMM_WORLD, "out.dat", MPI_MODE_WRONLY |MPI_MODE_CREATE, MPI_INFO_NULL, &pofp);
	MPI_File_seek(pofp, (MPI_Offset)(nEach*rank*sizeof(int)), MPI_SEEK_SET);
	MPI_File_write(pofp, data1, nEach, MPI_INT, MPI_STATUS_IGNORE);
	MPI_File_close(&pofp);

	for(i=0;i<nEach;i++){
		data1[i] = 0;
	}
	*/
	MPI_File_open(MPI_COMM_WORLD, "out.dat", MPI_MODE_RDONLY, MPI_INFO_NULL, &pifp);
	MPI_File_seek(pifp, (MPI_Offset)(nEach*rank*sizeof(int)), MPI_SEEK_SET);
	MPI_File_read(pifp, data2, nEach, MPI_INT, MPI_STATUS_IGNORE);
	MPI_File_close(&pifp);
	
	printf("%d\t%d\t%d\t%d\t%d\n", rank, data1[0], data1[1], data1[2], data1[3]);
	printf("%d\t%d\t%d\t%d\t%d\n", rank, data2[0], data2[1], data2[2], data2[3]);
	
  MPI_Finalize();
}
