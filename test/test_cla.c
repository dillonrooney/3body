#include<stdio.h>
#include<stdlib.h>

#include "../headers/cla.h"

int main(int argc, char ** argv){
	clOptions options;
	printf("argc=%d\n", argc);
	
	if(getCla(argc, argv, &options)){
	printf("%d\tnParticles\n", options.nParticles);
	printf("%d\ttiming\n", options.timing);
	printf("%s\ttimingFName\n", options.timingFName);
	printf("%d\treadInput\n", options.readInput);
	printf("%s\treadFName\n", options.readFName);
	printf("%d\twriteOutput\n", options.writeOutput);
	printf("%s\twriteFName\n", options.writeFName);
	printf("%d\tgenFunction\n", options.genFunction);
	printf("%d\tgenFunctionSeed\n", options.genFunctionSeed);
	printf("%d\tcompareResults\n", options.compareResults);
	printf("%d\tverbosity\n", options.verbosity);
	}else{
		printf("Cla reading failed");
		return 1;
	}
	
	
	return 0;
}