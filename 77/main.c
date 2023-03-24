
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static unsigned int giID;
static int **gppiResults;
static int *gpiTemp;
static giChose;
void rProduce(int iRange, int iChose) {
	if (iChose == 0) {
		for (unsigned int iCon = 0; iCon < giChose; iCon++) {
			gppiResults[giID][iCon] = gpiTemp[iCon];
		}
		giID++;
		printf("\n");
		return;
	}
	if (iRange == 0) { return; }
	unsigned int iCon;
	for (iCon = iChose; iCon <= iRange; iCon++) {
		printf("%d ", iCon);
		gpiTemp[iChose - 1] = iCon;
		rProduce(iCon - 1, iChose - 1);
	}
}
int** combine(int iRange, int iChose, int* piResults, int** ppiLengthes) {
	int iResults = 1;
	unsigned int iCon;
	gpiTemp = (int *)malloc(sizeof(int) * iChose);
	int iA;
	int iB;
	if (iChose > iRange / 2) {
		iA = iChose;
		iB = iRange - iChose;
	}
	else {
		iA = iRange - iChose;
		iB = iChose;
	}

	for (iCon = iA; iCon < iRange; iCon++) {
		iResults *= (iCon + 1);
	}
	for (iCon = 0; iCon < iB; iCon++) {
		iResults /= (iCon + 1);
	}


	printf("[%d]\n", iResults);
	int **ppiResults = (int **)malloc(sizeof(int *) * iResults);
	int *piLengthes = (int *)malloc(sizeof(int) * iResults);
	for (iCon = 0; iCon < iResults; iCon++) {
		ppiResults[iCon] = (int *)malloc(sizeof(int) * iChose);
		piLengthes[iCon] = iChose;
	}
	giChose = iChose;
	giID = 0;
	gppiResults = ppiResults;
	rProduce(iRange, iChose);
	*piResults = iResults;
	*ppiLengthes = piLengthes;
	free(gpiTemp);
	return ppiResults;
}
int main(void){

    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP(N, K,...) int iExp_##N[][K]={__VA_ARGS__};int *piExp_##N[sizeof(iExp_##N) / sizeof(iExp_##N[0])];int *piCols_##N[sizeof(iExp_##N) / sizeof(iExp_##N[0])];for(unsigned int iCon = 0; iCon < sizeof(iExp_##N) / sizeof(iExp_##N[0]) ; iCon++){piExp_##N[iCon] = iExp_##N[iCon];piCols_##N[iCon] = K;}
#define M_TEST_COLLECTION(N, R, C) {N, {R, C}, {piExp_##N, sizeof(iExp_##N) / sizeof(iExp_##N[0]), piCols_##N}}
    //  Structure
    struct sInput{
		int iRange;
		int iChose;
    };
    struct sExp{
		int **ppiSeries;
		int iResults;
		int *piCols;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	M_TEST_EXP(24, 2, { 1,1 });
	M_TEST_EXP(1, 2, { 1,2 }, { 1,3 }, { 1,4 }, { 2,3 }, { 2,4 }, { 3,4 });
	M_TEST_EXP(2, 2, { 1,1 });
    struct sTest mTest[]={
		M_TEST_COLLECTION(24, 13, 13),
		M_TEST_COLLECTION(2, 2, 2),
		M_TEST_COLLECTION(1, 4, 2),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
        printf("Result = ");
		int iResults;
		int *piLengthes;
		int **ppiResults = 
		combine(mTest[iConTest].mInput.iRange, mTest[iConTest].mInput.iChose, &iResults, &piLengthes);
		for (unsigned int iCon = 0; iCon < iResults; iCon++) {
			printf("[");
			for (unsigned int iConSeries = 0; iConSeries < piLengthes[iCon]; iConSeries++) {
				printf("%d ", ppiResults[iCon][iConSeries]);
			}
			printf("]");
		}
        //Comparison
        int iTest = 1;
        if(iTest){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        printf("\n");
        if(!iTest){
            break;
        }
    }
    printf("All Test Case : ");
    if(iConTest < iLengthTest){
        printf("[FAIL]");
    }else{
        printf("[PASS]");
    }
    printf("\n");
}
