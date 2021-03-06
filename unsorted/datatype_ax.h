//requirements
//C structure
//MPI structure
//Force Calculation
//printf
//various initializations



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

//Must be added to main
/*
MPI_Datatype new_type;

create_MPI_struct(&new_type);

*/
create_MPI_struct(&new_type){
	particle example;
	int example_address;
	int other_address;
	
	// int quark_address, flavor_address, color_address, charge_address, mass_address,
    // x_address, y_address, z_address, px_address, py_address, pz_address;
// int flavor_offset, color_offset, charge_offset, mass_offset, ...
// ...
// MPI_Get_address(&tau, &tau_address);
// MPI_Get_address(&tau.flavor, &flavor_address);
// MPI_Get_address(&tau.color, &color_address);
// MPI_Get_address(&tau.charge, &charge_address);
// MPI_Get_address(&tau.mass, &mass_address);
// ...
// flavor_offset = flavor_address - tau_address;
// color_offset = color_address - tau_address;
// charge_offset = charge_address - tau_address;
// mass_offset = mass_address - tau_address;

MPI_Get_address(&example, &example_address);
int array_of_displacements[10];
MPI_Get_address(&example.x, &other_address);
array_of_displacements[0]=other_address-example_address;
MPI_Get_address(&example.y, &other_address);
array_of_displacements[1]=other_address-example_address;
MPI_Get_address(&example.z, &other_address);
array_of_displacements[2]=other_address-example_address;
MPI_Get_address(&example.vx, &other_address);
array_of_displacements[3]=other_address-example_address;
MPI_Get_address(&example.vy, &other_address);
array_of_displacements[4]=other_address-example_address;
MPI_Get_address(&example.vz, &other_address);
array_of_displacements[5]=other_address-example_address;
MPI_Get_address(&example.dvx, &other_address);
array_of_displacements[6]=other_address-example_address;
MPI_Get_address(&example.dvy, &other_address);
array_of_displacements[7]=other_address-example_address;
MPI_Get_address(&example.dvz, &other_address);
array_of_displacements[8]=other_address-example_address;
MPI_Get_address(&example.mass, &other_address);
array_of_displacements[9]=other_address-example_address;


//(10, array_of_block_lengths, array_of_displacements, array_of_types, &new_type);
int array_of_block_lengths[10] = {sizeof(double),sizeof(double),sizeof(double),sizeof(double),sizeof(double),sizeof(double),sizeof(double),sizeof(double),sizeof(double),sizeof(double)};
MPI_Datatype array_of_types [10]  = {MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE, MPI_DOUBLE};

MPI_Type_create_struct(10, array_of_block_lengths, array_of_displacements, array_of_types, &new_type);

}





double findForce(particle * a, particle * b, particle * c){
	printf("finding forces\n");
	//I need to be more explicit on possible multiple counting
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


void fprintParticles(FILE*fp, particle * particles, int n){
	int i;
	for(i=0;i<n;i++){
		fprintf(fp, "%d\t%lf\t%lf\t%lf\n\t\t%lf\t%lf\t%lf\t%lf\n",i,particles[i].x,particles[i].y,particles[i].z,particles[i].vx,particles[i].vy,particles[i].vz, particles[i].mass);		
	}
}

void basicParticle(particle * in){
	
	in->x = 1;
	in->y = 2;
	in->z = 3;
	in->vx = 21;
	in->vy = 22;
	in->vz = 23;
	in->dvx = 121;
	in->dvy = 122;
	in->dvz = 123;
	in->mass = 9;

}
