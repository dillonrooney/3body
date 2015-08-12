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
	int timing = 0;
	char * timingFName= NULL;
	int readInput = 0;
	char * readFName = NULL;
	int writeOutput;
	char * writeFName= NULL;
	int compareResults = NULL;
	int genInput;
	
	int verbosity = 0;
	
	
} clOptions;

void getCla(int argc, char** argv, clOptions * in){
	//char * file = malloc(sizeof(char)* 1000);
	FILE * configFp;
	int fileNameLength =200;
		//200 characters seems reasonable
	if(argc == 1){
		configFp = fopen(argv[1], "r");
		//check opened file?
		
		fscanf(configFp, "%d\t%*s\n", &(in->timing));
		
		(in->timingFName) = malloc(sizeof(char)*fileNameLength);
		fscanf(configFp, "%s\t%*s\n", (in->timingFName));
		
		fscanf(configFp, "%d\t%*s\n", &(in->readInput));
		
		(in->readFName) = malloc(sizeof(char)*fileNameLength);
		fscanf(configFp, "%s\t%*s\n", (in->readFName));
		
		fscanf(configFp, "%d\t%*s\n", &(in->writeOutput));
		
		(in->writeFName) = malloc(sizeof(char)*fileNameLength);
		fscanf(configFp, "%s\t%*s\n", (in->writeFName));
		
		fscanf(configFp, "%d\t%*s\n", &(in->writeOutput));
		
	}
	
	
	
	
	
	
	
	
}