#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>

typedef struct particle_s{
	double x;
	double y;
	double z;
	double vx;
	double vy;
	double vz;
	double dvx;
	double dvy;
	double dvz;
	double mass;
} particle;


int getInput(FILE * fp, particle * particles, int n);

double findForce(particle * a, particle * b, particle * c);
	//Force on a as a function of coordinates of particles a,b,c
	
//int updateEuler(double h, particle * a);
	//euler, rk4, ... or something
	//questionable naming
	
	

//function definitions
int randInput(FILE * fp, particle * particles, int n){
	int i;
	double buf;
	srand(1);
	for (i = 0; i<n;i++){
		particles[i].x = (double)rand()/(double)RAND_MAX;
		particles[i].y = (double)rand()/(double)RAND_MAX;
		particles[i].z = (double)rand()/(double)RAND_MAX;
		
		particles[i].vx = 0;
		particles[i].vy = 0;
		particles[i].vz = 0;
		
		particles[i].mass = 1;
		fscanf(fp, "%lf\t%lf\t%lf\n", particles[i].x, particles[i].y, particles[i].z);
		
	}
	fprintf(stderr,"file written\n");
	
	
	return 0;
	
}

int getInput(FILE * fp, particle * particles, int n){
	int i;
	double buf;
	srand(1);
	for (i = 0; i<n;i++){
		fscanf(fp,"%lf\t%lf\t%lf\n", &particles[i].x, &particles[i].y, &particles[i].z);
		particles[i].mass = 1;
		
	}
	fprintf(stderr,"file read\n");
	
	
	return 0;
	
}


int updateEuler(double h, particle * particles, int n){
	//euler
	int i,j,k;
	for(k=0;k<n;k++){
		for(j=0;j<k;j++){
			for(i=0;i<j;i++){
				findForce(particles + i, particles + j, particles + k);
			}
		}	
	}
	for(i=0;i<n;i++){
		particles[i].x += h* particles[i].vx;
		particles[i].y += h* particles[i].vy;
		particles[i].z += h* particles[i].vz;
		
		particles[i].vx += h* particles[i].dvx;
		particles[i].vy += h* particles[i].dvy;
		particles[i].vz += h* particles[i].dvz;
		
		
		particles[i].dvx =0;
		particles[i].dvy =0;
		particles[i].dvz =0;
	}
	//for i
	//v += h*dv
	
	
	return 1;
	
}

void printParticles(particle * particles, int n){
	int i;
	printf("dpos\tpos\n");
	for (i = 0; i<n;i++){
		printf("%lf\t%lf\n", particles[i].dvx, particles[i].x);
		printf("%lf\t%lf\n", particles[i].dvy, particles[i].y);
		printf("%lf\t%lf\n", particles[i].dvz, particles[i].z);
		printf("\n");
	}
	
	
}


double findForce(particle * a, particle * b, particle * c){
	double ra,rb,rc;
	//ra is the distance between particle b and particle c
	double rabx = a->x - b->x;
	double raby = a->y - b->y;
	double rabz = a->z - b->z;
	
	double rbcx = b->x - c->x;
	double rbcy = b->y - c->y;
	double rbcz = b->z - c->z;
	
	double rcax = c->x - a->x;
	double rcay = c->y - a->y;
	double rcaz = c->z - a->z;
	
	ra = sqrt(rbcx*rbcx +rbcy*rbcy + rbcz*rbcz);
	double ra1 = ra;
	double ra2 = ra*ra;
	double ra3 = ra2*ra;
	double ra4 = ra3*ra;
	double ra5 = ra4*ra;
	double ra6 = ra5*ra;
	rb = sqrt(rbcx*rbcx +rbcy*rbcy + rbcz*rbcz);
	double rb1 = rb;
	double rb2 = rb*rb;
	double rb3 = rb2*rb;
	double rb4 = rb3*rb;
	double rb5 = rb4*rb;
	double rb6 = rb5*rb;
	rc = sqrt(rbcx*rbcx +rbcy*rbcy + rbcz*rbcz);
	double rc1 = rc;
	double rc2 = rc*rc;
	double rc3 = rc2*rc;
	double rc4 = rc3*rc;
	double rc5 = rc4*rc;
	double rc6 = rc5*rc;
	
	double du_dra = -3/(4*ra4*rb3*rc3) + 15*rb/(ra6*rc5) + 15*rc/(ra6*rb5) +3/(rb5*rc5) -3/(40*ra6*rb3*rc1) -3/(40*ra6*rc3*rb1) -3/(24*ra4*rb5*rc1) -3/(24*ra4*rc5*rb1) -3/(8*ra2*rb5*rc3) -3/(8*ra2*rc5*rb3);
	
	double du_drb = -3/(4*rb4*ra3*rc3) + 15*ra/(rb6*rc5) + 15*rc/(rb6*ra5) +3/(ra5*rc5) -3/(40*rb6*ra3*rc1) -3/(40*rb6*rc3*ra1) -3/(24*rb4*ra5*rc1) -3/(24*rb4*rc5*ra1) -3/(8*rb2*ra5*rc3) -3/(8*rb2*rc5*ra3);
	
	double du_drc = -3/(4*rc4*ra3*rb3) + 15*ra/(rc6*rb5) + 15*rb/(rc6*ra5) +3/(ra5*rb5) -3/(40*rc6*ra3*rb1) -3/(40*rc6*rb3*ra1) -3/(24*rc4*ra5*rb1) -3/(24*rc4*rb5*ra1) -3/(8*rc2*ra5*rb3) -3/(8*rc2*rb5*ra3);
	
	a->dvx += -rabx*du_drc/rc;
	a->dvx += rcax*du_drb/rb;
	
	b->dvx += -rbcx*du_dra/ra;
	b->dvx += rabx*du_drc/rc;
	
	c->dvx += -rcax*du_drb/rb;
	c->dvx += rbcx*du_dra/ra;
	
	a->dvy += -raby*du_drc/rc;
	a->dvy += rcay*du_drb/rb;
	
	b->dvy += -rbcy*du_dra/ra;
	b->dvy += raby*du_drc/rc;
	
	c->dvy += -rcay*du_drb/rb;
	c->dvy += rbcy*du_dra/ra;
	
	a->dvz += -rabz*du_drc/rc;
	a->dvz += rcaz*du_drb/rb;
	
	b->dvz += -rbcz*du_dra/ra;
	b->dvz += rabz*du_drc/rc;
	
	c->dvz += -rcaz*du_drb/rb;
	c->dvz += rbcz*du_dra/ra;
	

	return 0;
}

double energy_change(particle * particles, int n){
	static double energy;
	int i,j,k;
	double d21, d22, d23;
	double currentEnergy=0;
	for (i=0;i<n;i++){
		//kinetic
		currentEnergy+=0.5*particles[i].mass*(particles[i].vx*particles[i].vx + particles[i].vy*particles[i].vy +particles[i].vz*particles[i].vz );
		for(j=0;j<i;j++){
			for(k=0;k<j;k++){
				//potential
				d21 = (particles[i].x - particles[j].x)*(particles[i].x - particles[j].x) + (particles[i].y - particles[j].y)*(particles[i].y - particles[j].y) + (particles[i].z - particles[j].z)*(particles[i].z - particles[j].z);
				d22 = (particles[k].x - particles[j].x)*(particles[k].x - particles[j].x) + (particles[k].y - particles[j].y)*(particles[k].y - particles[j].y) + (particles[k].z - particles[j].z)*(particles[k].z - particles[j].z);
				d23 = (particles[i].x - particles[k].x)*(particles[i].x - particles[k].x) + (particles[i].y - particles[k].y)*(particles[i].y - particles[k].y) + (particles[i].z - particles[k].z)*(particles[i].z - particles[k].z);
				currentEnergy+=(1+3*(d21+d22-d23)*(-d21+d22+d23)*(d21-d22+d23))/(d21*d22*d23);
			}
			
		}
		
	}
	double difference = currentEnergy - energy;
	printf("energy difference = %lf\n", difference);
	energy = currentEnergy;
	return difference;
}


int main(int argc, char ** argv){
	int n = 100;
	particle * particles = malloc(sizeof(particle)* n);
	FILE * fp = fopen("input.dat", "r");
	getInput(fp, particles, n);
	fclose(fp);
	
	int i;
	double time;
	struct timeval t1,t2;
	
	for(i=3;i<n;i+=3){
		gettimeofday(&t1, NULL);
		energy_change(particles, i);
		updateEuler(0.1, particles, i);
		energy_change(particles, i);
		gettimeofday(&t2, NULL);
		time = t2.tv_sec + 0.000001*t2.tv_usec - t1.tv_sec - 0.000001*t1.tv_usec;
		printf("%d\t%lf\n",i,time);
	}
	
	
	//printParticles(particles, n);	
	//updateEuler(double h, particles, n);	
	//printParticles(particles, n);
	
	
	
	free(particles);
	return 1;
}