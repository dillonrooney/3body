
int pieceSize(int nTot, int nPieces, int piece){
	//rank, size
	int nEach = nTot/nPieces;
	int spare = nTot % nPieces;
	if(nTot%size !=0 && spare>piece){
		nEach++;
	}
	return nEach;
}

int pieceStart(int nTot, int nPieces, int piece){
	int nEach = nTot/nPieces;
	int start = piece * nEach;
	int spare = nTot % nPieces;
	if(spare>piece){
		start += piece;
	}else{
		start += spare;
	}
	return start;
}