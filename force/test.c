#include<stdlib.h>
#include<stdio.h>

//Global variables
//to allow compatibility with other stuff
int rank = 0;
int size = 1;


#include "datatype_ax_serial.h"

//Functions
void testInitLinear(int n){
	particle * stuff = malloc(n * sizeof(particle));
	initialize_linearx(stuff, n);
	fprintParticles(stdout, stuff, n);
	free(stuff);
}

void calcForces(particle * particles, int n){
	int i;
	int j;
	int k;
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			for(k=0;k<j;k++){
				findForce(particles +i, particles + j, particles + k);
			}
		}
	}
	
	
}

void leapFrogStep(particle * particles, int n){	
	
}

void totalMomentum(particle * particles, int n, double * out){
	int i;
	double xM, yM, zM;
	xM=0;
	yM=0;
	zM=0;
	for(i=0;i<n;i++){
		xM+=particles[i].mass * particles[i].vx;
		yM+=particles[i].mass * particles[i].vy;
		zM+=particles[i].mass * particles[i].vz;
	}
	out[0] = xM;
	out[1] = yM;
	out[2] = zM;
}

int testMomentum(){
	int n = 10;
	int i;
	double momentum[3];
	int failed = 0;
	particle * stuff = malloc(n * sizeof(particle));
	initialize_linearx(stuff, n);
	//zero momentum
	totalMomentum(stuff, n, momentum);
	if(momentum[0] != 0 || momentum[1] != 0 || momentum[2] != 0){
		failed++;
		printf("nonzero momentum found x=%lf y=%lf z=%lf, expected zero momentum\n", momentum[0], momentum[1], momentum[2]);
	}
	
	//some momentum expected 
	stuff[0].vx = 1;
	stuff[1].vx = 2;
	stuff[1].vy = 2;
	
	totalMomentum(stuff, n, momentum);
	if(momentum[0] != 3 || momentum[1] != 2 || momentum[2] != 0){
		failed++;
		printf("unexpected momentum found x=%lf y=%lf z=%lf, expected 3,2,0\n", momentum[0], momentum[1], momentum[2]);
	}
	//non-equal masses
	stuff[0].mass = 2;
	
	totalMomentum(stuff, n, momentum);
	if(momentum[0] != 4 || momentum[1] != 2 || momentum[2] != 0){
		failed++;
		printf("unexpected momentum found x=%lf y=%lf z=%lf, expected 4,2,0\n", momentum[0], momentum[1], momentum[2]);
	}
	//fprintParticles(stdout, stuff, n);
	
	free(stuff);
	
	
	if(failed == 0){
		printf("momentum calculation passed\n");
	}
	return !failed;
}

double kineticEnergy(particle * particles, int n){
	int i;
	double out = 0;
	double energyContribution;
	for(i=0;i<n;i++){
		energyContribution= particles[i].vx * particles[i].vx;
		energyContribution+= particles[i].vy * particles[i].vy;
		energyContribution+= particles[i].vz * particles[i].vz;
		energyContribution *= particles[i].mass*0.5;
		out += energyContribution ;
	}
	
	return out;
}

double findPotentialEnergy(particle * a, particle * b, particle * c){
	double out= 0;
	double d21, d22, d23;
	d21 = (a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y) + (a->z - b->z)*(a->z - b->z);
	d22 = (c->x - b->x)*(c->x - b->x) + (c->y - b->y)*(c->y - b->y) + (c->z - b->z)*(c->z - b->z);
	d23 = (a->x - c->x)*(a->x - c->x) + (a->y - c->y)*(a->y - c->y) + (a->z - c->z)*(a->z - c->z);
	double d6 = d21*d22*d23;
	double d3 = sqrt(d6);
	double d15 = d6 * d6 * d3;
	out+=(d6+(3.0/8.0)*(d21+d22-d23)*(-d21+d22+d23)*(d21-d22+d23))/(d15);
	return out;
}

double potentialEnergy(particle * particles, int n){
	int i;
	int j;
	int k;
	double out = 0;
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			for(k=0;k<j;k++){
				out += findPotentialEnergy(particles +i, particles + j, particles + k);
			}
		}
	}
	return out;
}

double totalEnergy(particle * particles, int n){
	double out = 0;
	out += kineticEnergy(particles, n);
	out += potentialEnergy(particles, n);
	return out;
}

int testEnergy(){
	int failed = 0;
	
	int n = 3;
	particle * particles = malloc(n * sizeof(particle));
	initialize_linearx(particles, n);
	double kinetic = kineticEnergy(particles, n);
	if(kinetic != 0){
		failed ++;
		printf("nonzero kinetic energy %lf found\n", kinetic);
	}
	double potential = potentialEnergy(particles, n);
	if(potential != -0.25){
		failed ++;
		printf("unexpected potential energy %lf found. expected -0.25\n", potential);
	}
	//double distances, expect force ~2^-9
	particles[0]. x = 0;
	particles[1].x = 2;
	particles[2].x = 4;
	potential = potentialEnergy(particles, n);
	if(potential != -0.00048828125){
		failed ++;
		printf("unexpected potential energy %lf found. expected -0.00048828125\n", potential);
	}
	//equilateral triangle
	initialize_equilateral(particles, n);
	potential = potentialEnergy(particles, n);
	if(potential != 1.375){
		failed ++;
		printf("unexpected potential energy %g found. expected 1.375\n", potential - 1.375);
	}
	
	if(failed == 0){
		printf("energy test passed\n");
	}
	return !failed;
}

int main(int argc, char ** argv){
	testInitLinear(3);
	testMomentum();
	testEnergy();
	
	return 0;
}

