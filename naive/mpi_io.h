
writeParticles(char * fileName, particle * data,int  nEach){
	MPI_File pofp;
	
	MPI_File_open(MPI_COMM_WORLD, fileName, MPI_MODE_WRONLY |MPI_MODE_CREATE, MPI_INFO_NULL, &pofp);
	MPI_File_seek(pofp, (MPI_Offset)(nEach*rank*sizeof(particle)), MPI_SEEK_SET);
	MPI_File_write(pofp, data, nEach, MPI_particle, MPI_STATUS_IGNORE);
	MPI_File_close(&pofp);

}

readParticles(char * fileName, particle * data, int nEach){
	MPI_File pifp;
	MPI_File_open(MPI_COMM_WORLD, fileName, MPI_MODE_RDONLY, MPI_INFO_NULL, &pifp);
	MPI_File_seek(pifp, (MPI_Offset)(nEach*rank*sizeof(particle)), MPI_SEEK_SET);
	MPI_File_read(pifp, data, nEach, MPI_particle, MPI_STATUS_IGNORE);
	MPI_File_close(&pifp);
	
}	
