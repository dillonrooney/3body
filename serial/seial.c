#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>

typedef struct particle_s{
	double pos;
	double dpos;
	
} particle;


int getInput(FILE * fp, particle * particles, int n);

double findForce(particle * a, particle * b, particle * c);
	//Force on a as a function of coordinates of particles a,b,c
	
//int update(particle * a);
	//euler, rk4, ... or something
	//questionable naming
	
	

//function definitions
int getInput(FILE * fp, particle * particles, int n){
	int i;
	double buf;
	for (i = 0; i<n;i++){
		fscanf(fp, "%lf\n", &buf);
		particles[i].dpos = 0;
		particles[i].pos = buf;
	}
	fprintf(stderr,"file read\n");
	
	
	return 0;
	
}


int update(particle * particles, int n){
	int i,j,k;
	for(k=0;k<n;k++){
		for(j=0;j<k;j++){
			for(i=0;i<j;i++){
				findForce(particles + i, particles + j, particles + k);
			}
		}	
	}
	
	return 1;
	
}

void printParticles(particle * particles, int n){
	int i;
	printf("dpos\tpos\n", particles[i].dpos, particles[i].pos);
	for (i = 0; i<n;i++){
		printf("%lf\t%lf\n", particles[i].dpos, particles[i].pos);
	}
	
	
}


double findForce(particle * a, particle * b, particle * c){
	a->dpos += 1;
	b->dpos += 1;
	c->dpos += 1;
	
	
	return 0;
}


int main(int argc, char ** argv){
	int n = 1000;
	particle * particles = malloc(sizeof(particle)* n);
	FILE * fp = fopen("input.dat", "r");
	getInput(fp, particles, n);
	fclose(fp);
	
	int i;
	double time;
	struct timeval t1,t2;
	
	for(i=3;i<n;i+=3){
		gettimeofday(&t1, NULL);
		update(particles, i);
		gettimeofday(&t2, NULL);
		time = t2.tv_sec + 0.000001*t2.tv_usec - t1.tv_sec - 0.000001*t1.tv_usec;
		printf("%d\t%lf\n",i,time);
		
	}
	
	
	//printParticles(particles, n);	
	//update(particles, n);	
	//printParticles(particles, n);
	
	
	
	free(particles);
	return 1;
}