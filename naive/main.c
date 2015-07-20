//Notes
//Requirements
//MPI:pass(communicator/etc, amount, buffer, direction, distance)
//do stuff
//should have 4 buffers (1 spare to recieve)???


//calculate forces()

typedef struct coordinate_s{
	//mass
	//position
	double pos;
	//position change
	double dpos;
	
	
}coordinate;







//includes

//function declarations

//function definitions



//main
int main(int argc, char** argv){
	int n_each_max;
	
	coordinate* particle_buffers[4];
	int particle_sections[4];
	int particle_totals[4];
	
	
	particle_buffers[0] = malloc(n_each_max * sizeof (coordinate));
	particle_buffers[1] = malloc(n_each_max * sizeof (coordinate));
	particle_buffers[2] = malloc(n_each_max * sizeof (coordinate));
	particle_buffers[3] = malloc(n_each_max * sizeof (coordinate));
	
	
	
	
	
	return 0;
}