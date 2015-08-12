#include<stdio.h>
#include<stdlib.h>

#include "../headers/split.h"


int testAccumulation(int nTot, int nPieces){
	int i;
	int out =0;
	int accStart = 0;
	int approx = nTot/nPieces;
	int currentPieceSize;
	for(i=0;i<nPieces;i++){
		if(accStart != pieceStart(nTot, nPieces, i)){
			out++;
		}
		currentPieceSize = pieceSize(nTot, nPieces, i);
		if(currentPieceSize != approx && currentPieceSize != approx+1){
			out++;
		}
		accStart += currentPieceSize;
	}
	if(accStart!=nTot){
		out++;
	}
	return out;
}


int main(int argc, char** argv){
		int i;
		int verbosity = 0;
		int failed = 0;
		if (argc == 1 && argv[1][0] == 'v'){
			verbosity = 1;
		}
		int n = 10;
		if(verbosity == 1){
			printf("expect 4, 3, 3\n")
		}
		for(i=0;i<3;i++){
			if((i==0 && pieceSize(10, 3, i) !=4)||(i!=0 && pieceSize(10, 3, i) !=3)){
				printf("unexpected split of 10 into 3 pieces: piece %d = %d\n", i, pieceSize(10, 3, i));
				failed = 1;
			}
			if(verbosity == 1){
				printf("%d, " , pieceSize(10, 3, i))
			}
		}
		if(verbosity == 1){
			printf("\n");
		}
		int nTests = 7;
		int totals[nTests] = {2,123,665, 999, 500, 1000000, 9493759837};
		int pieces[nTests] = {1, 12, 23, 154, 50, 1024, 234};
		for(i=0;i<nPieces;i++){
			failed += testAccumulation(totals, pieces);
		}
		if(failed == 0){
			printf("split.h test passed\n");
		}else{
			printf("split.h test failed %d\n", failed);
		}
	return 0;
}