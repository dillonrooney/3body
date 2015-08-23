#include<float.h>
#include<math.h>

double rel_diff(double in1, double in2, double minTol, double epsTol){
	//returns a result of the difference as approximately the the smallest multiple of either the smallest double value(DBL_MIN) or the difference between adjacent doubles (DBL_EPSILON)
	//effectively relative to smallest possible difference
	
	double out;
	out = 0;
	double diff = in1-in2;
	double absDiff = fabs(diff);
	double magnitude = (fabs(in1) + fabs(in2))*0.5;
	double relDiff = absDiff/magnitude;
	//important to have split the two here
	absDiff = absDiff/DBL_MIN;
	if(absDiff < minTol){
		return 0;
	}
	//
	//in case one is very close to 0, leading to large differences
	// x-y/0.5 x+y <z epsilon
	//x^2  - y^2 /0.5 (x+y)^2  
	//assume x = y + d and d small
	//x^2 - x^2 + xd + d^2 / 2x^2
	//0 + xd + 0 /2x^2
	// d/2x 
	// also d/x = epsilon
	// 1/2 >z

	relDiff = relDiff/DBL_EPSILON;
	//	~0 if diff small;  ~1 if diff large
	if(relDiff < epsTol){
		return 0;
	}
	
	//out = min(relDiff, absDiff);
	out = absDiff<relDiff?absDiff:relDiff;
	
	if(out < 0.49){
		printf("unexpected small output of rel_diff  = %g\n", out);
	}
	return out;
	
}

double normThreeCoords(double x, double y, double z, int normType){
	//assuming x,y,z >= 0 and abs (|x|) not necessary

	double out = 0;
	//infinity = 0;
	if(normType == 0){
		out = x>y?x:y;
		out = out>z?out:z;
		return out;
	}
	//Cartesian = 2;
	// it seems a bit odd to be using with 
	else if(normType == 0){
		out = x*x + y*y + z*z;
		return sqrt(out);
	}
	// Manhattan = 1;
	else if(normType == 0){
		out = x+y+z;
		return out;
	}else{
		printf("error: unknown norm type = %d\n", normType);
		return NAN;
	}
}



double compare_positions(particle*in1, particle * in2){
	double x,y,z, minTol, epsTol;
	//multiple of machine precision tolerated
	minTol = 10;
	epsTol = 10;
	
	x = rel_diff(in1-> x, in2->x, minTol, epsTol);
	y = rel_diff(in1-> y, in2->y, minTol, epsTol);
	z = rel_diff(in1-> z, in2->z, minTol, epsTol);
	
	double out;
	//infinity norm
	out = normThreeCoords(x, y, z, 0);
	
	return out;
	
}



double compare_velocities(particle*in1, particle * in2){
	double x,y,z, minTol, epsTol;
	//multiple of machine precision tolerated
	minTol = 10;
	epsTol = 10;
	
	x = rel_diff(in1-> vx, in2->vx, minTol, epsTol);
	y = rel_diff(in1-> vy, in2->vy, minTol, epsTol);
	z = rel_diff(in1-> vz, in2->vz, minTol, epsTol);
	
	double out;
	//infinity norm
	out = normThreeCoords(x, y, z, 0);
	
	return out;
}




double compare_acceleration(particle*in1, particle * in2){
	double x,y,z, minTol, epsTol;
	//multiple of machine precision tolerated
	minTol = 10;
	epsTol = 10;
	
	x = rel_diff(in1-> dvx, in2->dvx, minTol, epsTol);
	y = rel_diff(in1-> dvy, in2->dvy, minTol, epsTol);
	z = rel_diff(in1-> dvz, in2->dvz, minTol, epsTol);
	
	double out;
	//infinity norm
	out = normThreeCoords(x, y, z, 0);
	
	return out;
	
}

double compare_particle(particle*in1, particle * in2){
	double posRelDiff = compare_positions(in1, in2);
	double velRelDiff = compare_velocities(in1, in2);
	double accRelDiff = compare_acceleration(in1, in2);
	
	
	double out;
	out = normThreeCoords(posRelDiff, velRelDiff, accRelDiff, 0);
	//mass
	double massDiff = rel_diff(in1->mass, in2->mass, 0, 2);
	if(massDiff != 0){
		//non equal masses;
		out += massDiff;
	}
	return out;
}

double compareMultipleParticles(particle*in1, particle * in2, int nEach){
	
	//0:allocate
	double * comparisonData = malloc(3*nEach*sizeof(double));
	//1:collect
	int i;
	double minTol = 0;
	double epsTol = 0;
	for (i=0;i<nEach;i++){
		comparisonData[3*i] = rel_diff((in1+i)-> dvx, (in2+i)->dvx, minTol, epsTol);
		comparisonData[3*i+1] = rel_diff((in1+i)-> dvy, (in2+i)->dvy, minTol, epsTol);
		comparisonData[3*i+2] = rel_diff((in1+i)-> dvz, (in2+i)->dvz, minTol, epsTol);
	}
	//2:mean
	double mean = 0;
	double count = 3*i;
	for(i=0;i<count;i++){
		mean += comparisonData[i];
	}
	mean = mean/count;
	//3:standard deviation
	double variance = 0;
	double current;
	for(i=0;i<count;i++){
		current = comparisonData[i] - mean;
		variance += current* current;
	}
	variance = variance/count;
	double stdev = sqrt(variance);
	//4:histogram
	//later...
	//5:print
	
	printf("comparison of dv statistics:rank %d: mean=%lf\tstdev=%lf\n", rank, mean, stdev);
	
	
	free(comparisonData);
	
	
	
	double out = 0;
	double newDiff;
	//int i;
	for (i=0;i<nEach;i++){
		newDiff  = compare_particle(in1+i, in2+i);
		if(isnan(newDiff)){
			return newDiff;
		}
		out = out<newDiff?newDiff:out;
		//out += compare_particle(in1+i, in2+i);
	}

	return out;	
}
