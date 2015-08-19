
#include<stdio.h>
#include<stdlib.h>

#include "mpi.h"

int rank,size;

#include "../headers/timing.h"
#include "../headers/cla.h"



void takeTime(int n){
	int i,j,k;
	double stuff = 0 ;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				stuff += k;
				stuff *= 0.5;
			}
		}	
	}
}

int main(int argc, char** argv){
	
	size = 10;
	rank = 0;
	
	MPI_Init(&argc,&argv);
	clOptions options;
	if(getCla(argc, argv, &options)){
		//NOTHING TO WORRY ABOUT
	}else{
		printf("command line options failure\n");
		
		return 1;
	}
	
	clock_start();
	takeTime(10);
	clock_stop(argv[0], options, "words");
	
	clock_start();
	takeTime(100);
	clock_stop(argv[0], options, "x1000");
	
	clock_start();
	takeTime(1000);
	clock_stop(argv[0], options, "E6");
	
	char * newtag;
	newtag = "hardcoded_string";
	
	clock_start();
	takeTime(100);
	clock_stop(argv[0], options, newtag);
	
	MPI_Finalize();
	
}
