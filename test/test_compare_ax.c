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
	int nEach = 5;
	particle things1[nEach];
	particle things2[nEach];
	int i;
	MPI_Status status_ignore;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(size != 1){
		printf("%d/%d: too many processes\n", rank, size);
		
		MPI_Finalize();	
		return 1;
	}
	
	//MPI_Datatype MPI_particle;
	create_MPI_struct(&MPI_particle);
	MPI_Type_commit(&MPI_particle);
	
	
	double epsilon = DBL_EPSILON;
	double min = DBL_MIN;
	printf("epsilon = %g\n", epsilon);
	printf("dbl min = %g\n", min);
	
	
	
	
	for(i=0;i<nEach;i++){
		basicParticle(things1+i);
		basicParticle(things2+i);
	}
	
	printf("things1 \n");
	fprintParticles(stdout, things1,nEach);
	printf("things2 \n");
	fprintParticles(stdout, things2,nEach);
	
	double diff, diffx, diffv, diffa;
	diff = compareMultipleParticles(things1, things2, nEach);
	printf("total diff of %d = %g\t expected 0\n", nEach, diff);
	
	diffx = compare_positions(things1, things2);
	printf("pos diff of %d = %g\t expected 0\n", 1, diffx);
	
	diffv = compare_positions(things1, things2);
	printf("vel diff of %d = %g\t expected 0\n", 1, diffv);
	
	diffa = compare_positions(things1, things2);
	printf("acc diff of %d = %g\t expected 0\n", 1, diffa);
	
	printf("\nchanging the values of stuff\n");
	
	printf("0 and 1\t expected ~1/eps = %g\n",1/epsilon);
	things1[0].x = 0;
	things2[0].x = 1;
	
	diff = compareMultipleParticles(things1, things2, nEach);
	printf("total diff of %d = %g\n", nEach, diff);
	
	diffx = compare_positions(things1, things2);
	printf("pos diff of %d = %g\n", 1, diffx);
	
	printf("\n0 and dbl_min\t expected 0\n");
	things1[0].x = 0;
	things2[0].x = min;
	
	diff = compareMultipleParticles(things1, things2, nEach);
	printf("total diff of %d = %g\n", nEach, diff);
	
	diffx = compare_positions(things1, things2);
	printf("pos diff of %d = %g\n", 1, diffx);
	
	printf("\n0 and eps\t expected 1/eps = %g\n", 1/epsilon);
	things2[0].x = epsilon;
	diff = compareMultipleParticles(things1, things2, nEach);
	printf("total diff of %d = %g\n", nEach, diff);
	diffx = compare_positions(things1, things2);
	printf("pos diff of %d = %g\n", 1, diffx);
	
	printf("\n1 and 1+eps\t expected 0\n");
	things1[0].x = 1;
	things2[0].x = 1+ epsilon;
	diff = compareMultipleParticles(things1, things2, nEach);
	printf("total diff of %d = %g\n", nEach, diff);
	diffx = compare_positions(things1, things2);
	printf("pos diff of %d = %g\n", 1, diffx);
	
	printf("\n1^20 and 10^20+eps*10^20\t expected 0\n");
	things1[0].x = 1E20;
	things2[0].x = 1E20 + 1E20 * epsilon;
	diff = compareMultipleParticles(things1, things2, nEach);
	printf("total diff of %d = %g\n", nEach, diff);
	diffx = compare_positions(things1, things2);
	printf("pos diff of %d = %g\n", 1, diffx);
	
	
	
	double y;
	printf("\ncomparing 1 and 1+y, expect eps*10\n");
	things2[0].x = 1;
	for(y = 10;y>0;y*=0.5){
		things1[0]. x = 1+y;
		diffx = compare_positions(things1, things2);
		if(diffx == 0){
			printf("at y = %g, 1+y compares equal to 1\n", y);
			break;
		}
	}
	
	printf("\ncomparing 0 and y, expect min*10\n");
	things2[0].x = 0;
	for(y = 10;y>0;y*=0.5){
		things1[0]. x = y;
		diffx = compare_positions(things1, things2);
		if(diffx == 0){
			printf("at y = %g, y compares equal to 0\n", y);
			break;
		}
	}
	
	printf("x position compared\n");

	MPI_Type_free(&MPI_particle);
	MPI_Finalize();
	return 0;	
}
