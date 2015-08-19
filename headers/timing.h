#include <sys/time.h>
#include "../headers/cla.h"
//assumes rank and size exists
struct timeval GLOBAL_CLOCK_START;


void clock_start(){
	gettimeofday(&GLOBAL_CLOCK_START, NULL);
}


void clock_stop(char * programName, clOptions options, char * tag){
	
	double diffs, diffu, diff;
	
	struct timeval stop_timeval;
	
	gettimeofday(&stop_timeval, NULL);
	diffs = (double)stop_timeval.tv_sec - (double)GLOBAL_CLOCK_START.tv_sec;
	diffu = (double)stop_timeval.tv_usec - (double)GLOBAL_CLOCK_START.tv_usec;
	diff = diffs + diffu * 1E-6;
	FILE * fp;
	
	if (rank == 0){
		fp = fopen(options.timingFName, "a");
		fprintf(fp, "%s%t%s\t%d\t%d\t%lf\n", programName, tag, options.nParticles, size, diff);
		fclose(fp);
	}
	
	
}