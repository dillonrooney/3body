#include<stdio.h>
#include<stdlib.h>

/*
//  NEEDED  //
timing output file
timing output options

nParticles

Generation function and requirements (seed, rng, ...)
OR
Input file

Output file

verbosities


*/




typedef struct options_s{
	int nParticles;
	int timing;
	char * timingFName;
	int readInput;
	char * readFName;
	int writeOutput;
	char * writeFName;
	int genFunction;
	int genFunctionSeed;
	int compareResults;
	int verbosity;
	
	
} clOptions;

int getCla(int argc, char** argv, clOptions * in){
	//char * file = malloc(sizeof(char)* 1000);
	FILE * configFp;
	int fileNameLength =200;
		//200 characters seems reasonable
	if(argc == 2){
		configFp = fopen(argv[1], "r");
		//check opened file?
		if(configFp == NULL){
			printf("could not open file: %s", argv[1]);
			return 0;
		}
		fscanf(configFp, "%d\t%*s\n", &(in->nParticles));
		
		fscanf(configFp, "%d\t%*s\n", &(in->timing));
		
		(in->timingFName) = malloc(sizeof(char)*fileNameLength);
		fscanf(configFp, "%s\t%*s\n", (in->timingFName));
		
		fscanf(configFp, "%d\t%*s\n", &(in->readInput));
		
		(in->readFName) = malloc(sizeof(char)*fileNameLength);
		fscanf(configFp, "%s\t%*s\n", (in->readFName));
		
		fscanf(configFp, "%d\t%*s\n", &(in->writeOutput));
		
		(in->writeFName) = malloc(sizeof(char)*fileNameLength);
		fscanf(configFp, "%s\t%*s\n", (in->writeFName));
		
		fscanf(configFp, "%d\t%*s\n", &(in->genFunction));
		fscanf(configFp, "%d\t%*s\n", &(in->genFunctionSeed));
		fscanf(configFp, "%d\t%*s\n", &(in->compareResults));
		fscanf(configFp, "%d\t%*s\n", &(in->verbosity));
		
	}else{
		printf("unknown command line arguments\n");
		return 0;
	}
	
	return 1;
}