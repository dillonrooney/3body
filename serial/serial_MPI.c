#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>

#include "../headers/datatype_ax.h"
MPI_Datatype MPI_particle;
int rank;
int size;

#include "../headers/mpi_io.h"



	
	

//function definitions
int randInput(FILE * fp, particle * particles, int n){
	int i;
	double buf;
	srand(1);
	for (i = 0; i<n;i++){
		particles[i].x = 0*(double)rand()/(double)RAND_MAX +i;
		particles[i].y = 0*(double)rand()/(double)RAND_MAX;
		particles[i].z = 0*(double)rand()/(double)RAND_MAX;
		
		particles[i].vx = 0;
		particles[i].vy = 0;
		particles[i].vz = 0;
		
		particles[i].mass = 1;
		//fscanf(fp, "%lf\t%lf\t%lf\n", particles[i].x, particles[i].y, particles[i].z);
		
	}
	fprintf(stderr,"file written\n");
	
	
	return 0;
	
}


int updateLeapFrog(double h, particle * particles, int n){
	//leapfrog with half step updating positions
	int i,j,k;
	for(i=0;i<n;i++){
		particles[i].x += 0.5*h* particles[i].vx;
		particles[i].y += 0.5*h* particles[i].vy;
		particles[i].z += 0.5*h* particles[i].vz;
	}
	for(k=0;k<n;k++){
		for(j=0;j<k;j++){
			for(i=0;i<j;i++){
				findForce(particles + i, particles + j, particles + k);
			}
		}	
	}
	for(i=0;i<n;i++){
		
		particles[i].vx += h* particles[i].dvx;
		particles[i].vy += h* particles[i].dvy;
		particles[i].vz += h* particles[i].dvz;
		
		particles[i].x += 0.5*h* particles[i].vx;
		particles[i].y += 0.5*h* particles[i].vy;
		particles[i].z += 0.5*h* particles[i].vz;
		
		particles[i].dvx =0;
		particles[i].dvy =0;
		particles[i].dvz =0;
	}
	//for i
	//v += h*dv
	
	printf("leapfrogging\n");
	return 1;
	
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

void updateForce( particle * particles, int n){
	int i,j,k;
	for(k=0;k<n;k++){
		for(j=0;j<k;j++){
			for(i=0;i<j;i++){
				findForce(particles + i, particles + j, particles + k);
			}
		}	
	}
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

double energy_change(particle * particles, int n, int printing){
	static double energy;
	int i,j,k;
	double d21, d22, d23, rrrcubed;
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
				currentEnergy+=(d21*d22*d23+3*(d21+d22-d23)*(-d21+d22+d23)*(d21-d22+d23)/8)/(d21*d22*d23*d21*d22*d23*sqrt(d21*d22*d23));
			}
			
		}
		
	}
	printf("energy = %lf\n",currentEnergy);
	double difference = currentEnergy - energy;
	if(printing == 1){
		printf("energy difference = %lf\n", difference);
	}
	energy = currentEnergy;
	return difference;
}


int main(int argc, char ** argv){
	
	MPI_Init(&argc,&argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(size != 1){
		printf("too many processes\n");
		MPI_Finalize();
		return 1;		
	}
	//MPI_Datatype MPI_particle;
	create_MPI_struct(&MPI_particle);
	MPI_Type_commit(&MPI_particle);
	
	
	int n = 72;
	particle * particles = malloc(sizeof(particle)* n);
	FILE * fp = fopen("input.dat", "r");
	randInput(fp, particles, n);
	//getInput(fp, particles, n);
	fclose(fp);
	
	updateForce(particles, n);
	
	writeParticles("serialOut72.dat", particles, n);
	
	
	free(particles);
	MPI_Type_free(&MPI_particle);
	MPI_Finalize();
	return 0;
}
