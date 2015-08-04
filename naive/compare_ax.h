#include<float.h>


double compare_positions(particle*in1, particle * in2){
	double tolerance = 10;
	//multiple of machine precision tolerated
	
	double x_diff = in1-> x - in2->x;
	double y_diff = in1->y - in2 ->y;
	double z_diff = in1->z - in2 ->z;
	
	double rel_x_diff = 0.5*fabs(x_diff/(fabs(in1-> x) + fabs(in2->x)));
	if(fabs(x_diff)<tolerance*DBL_MIN){
		x_diff =0;
	}else if(rel_x_diff < tolerance*DBL_EPSILON){
		x_diff =0;
	}
	
	double rel_y_diff = 0.5*fabs(y_diff/(fabs(in1-> y) + fabs(in2->y)));
	if(fabs(y_diff)<tolerance*DBL_MIN){
		y_diff =0;
	}else if(rel_y_diff < tolerance*DBL_EPSILON){
		y_diff =0;
	}
	
	double rel_z_diff = 0.5*fabs(z_diff/(fabs(in1-> z) + fabs(in2->z)));
	if(fabs(z_diff)<tolerance*DBL_MIN){
		z_diff =0;
	}else if(rel_z_diff < tolerance*DBL_EPSILON){
		z_diff =0;
	}
	
	double out;
	//infinity norm
	out = rel_x_diff>rel_y_diff?rel_x_diff:rel_y_diff;
	out = rel_z_diff>out?rel_z_diff:out;
	
	return out;
	
}



double compare_velocities(particle*in1, particle * in2){
	double tolerance = 10;
	//multiple of machine precision tolerated
	
	double vx_diff = in1-> vx - in2->vx;
	double vy_diff = in1->vy - in2 ->vy;
	double vz_diff = in1->vz - in2 ->vz;
	
	double rel_vx_diff = 0.5*fabs(vx_diff/(fabs(in1-> vx) + fabs(in2->vx)));
	if(fabs(vx_diff)<tolerance*DBL_MIN){
		vx_diff =0;
	}else if(rel_vx_diff < tolerance*DBL_EPSILON){
		vx_diff =0;
	}
	
	double rel_vy_diff = 0.5*fabs(vy_diff/(fabs(in1-> vy) + fabs(in2->vy)));
	if(fabs(vy_diff)<tolerance*DBL_MIN){
		vy_diff =0;
	}else if(rel_vy_diff < tolerance*DBL_EPSILON){
		vy_diff =0;
	}
	
	double rel_vz_diff = 0.5*fabs(vz_diff/(fabs(in1-> vz) + fabs(in2->vz)));
	if(fabs(vz_diff)<tolerance*DBL_MIN){
		vz_diff =0;
	}else if(rel_vz_diff < tolerance*DBL_EPSILON){
		vz_diff =0;
	}
	
	double out;
	//infinity norm
	out = rel_vx_diff>rel_vy_diff?rel_vx_diff:rel_vy_diff;
	out = rel_vz_diff>out?rel_vz_diff:out;
	
	return out;
	
}




double compare_acceleration(particle*in1, particle * in2){
	double tolerance = 10;
	//multiple of machine precision tolerated
	
	double dvx_diff = in1-> dvx - in2->dvx;
	double dvy_diff = in1->dvy - in2 ->dvy;
	double dvz_diff = in1->dvz - in2 ->dvz;
	
	double rel_dvx_diff = 0.5*fabs(dvx_diff/(fabs(in1-> dvx) + fabs(in2->dvx)));
	if(fabs(dvx_diff)<tolerance*DBL_MIN){
		dvx_diff =0;
	}else if(rel_dvx_diff < tolerance*DBL_EPSILON){
		dvx_diff =0;
	}
	
	double rel_dvy_diff = 0.5*fabs(dvy_diff/(fabs(in1-> dvy) + fabs(in2->dvy)));
	if(fabs(dvy_diff)<tolerance*DBL_MIN){
		dvy_diff =0;
	}else if(rel_dvy_diff < tolerance*DBL_EPSILON){
		dvy_diff =0;
	}
	
	double rel_dvz_diff = 0.5*fabs(dvz_diff/(fabs(in1-> dvz) + fabs(in2->dvz)));
	if(fabs(dvz_diff)<tolerance*DBL_MIN){
		dvz_diff =0;
	}else if(rel_dvz_diff < tolerance*DBL_EPSILON){
		dvz_diff =0;
	}
	
	double out;
	//infinity norm
	out = rel_dvx_diff>rel_dvy_diff?rel_dvx_diff:rel_dvy_diff;
	out = rel_dvz_diff>out?rel_dvz_diff:out;
	
	return out;
	
}

double compare_particle(particle*in1, particle * in2){
	double posRelDiff = compare_positions(in1, in2);
	double velRelDiff = compare_velocities(in1, in2);
	double accRelDiff = compare_acceleration(in1, in2);
	
	
	//mass
	double massRelDiff = 0;
	double out;
	//infinity norm
	out = posRelDiff>velRelDiff?posRelDiff:velRelDiff;
	out = accRelDiff>out?accRelDiff:out;
	return out;
}

double compareMultipleParticles(particle*in1, particle * in2, int nEach){
	
	double out = 0;
	int i;
	for (i=0;i<nEach;i++){
		out += compare_particle(in1+i, in2+i);
	}

	return out;	
}
