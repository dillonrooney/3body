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