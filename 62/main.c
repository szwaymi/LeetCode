
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int rVRF_Produce(int iM, int iN) {
	if (iN == 2) {
		return iM;
	}
	unsigned int iCon;
	int iSum = 0;
	for (iCon = 0; iCon < iM; iCon++) {
		iSum += rVRF_Produce(iCon + 1, iN - 1);
	}
	return iSum;
}
int rVRF_uniquePaths(int iM, int iN) {
	if (iN == 1) {
		return 1;
	}
	return rVRF_Produce(iM, iN);
}
static struct {
	int **piCaches;
	int iN;
}gmMeta;
int rProduce(int iM, int iN) {
	if (iN == 2) {
		return iM;
	}
	if (iN < gmMeta.iN && gmMeta.piCaches[iM][iN - 2] != -1) {
		return gmMeta.piCaches[iM][iN - 2];
	}
	unsigned int iCon;
	int iSum = 0;
	for (iCon = 0; iCon < iM; iCon++) {
		iSum += rProduce(iCon + 1, iN - 1);
	}
	if (iN < gmMeta.iN) {
		gmMeta.piCaches[iM][iN - 2] = iSum;
	}

	return iSum;
}
int uniquePaths(int iM, int iN) {
	if (iN == 1) {
		return 1;
	}
	gmMeta.iN = iN;
	unsigned int iCon;
	gmMeta.piCaches = (int **)malloc(sizeof(int *) * (iM + 1));
	for (iCon = 0; iCon < (iM + 1); iCon++) {
		gmMeta.piCaches[iCon] = (int *)malloc(sizeof(int) * (iN - 2));
		unsigned int iConN;
		for (iConN = 0; iConN < (iN - 2); iConN++) {
			gmMeta.piCaches[iCon][iConN] = -1;
		}
	}
	int iResult = rProduce(iM, iN);
	for (iCon = 0; iCon < (iM + 1); iCon++) {
		free(gmMeta.piCaches[iCon]);
	}
	free(gmMeta.piCaches);
	return iResult;
}


int main(void){
	printf("%d ", uniquePaths(13, 23));
	printf("%d", rVRF_uniquePaths(4,3));
	
	/*
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP
#define M_TEST_COLLECTION(NO, M, N, E) {NO, {M, N},{E}}
    //  Structure
    struct sInput{
		int iM;
		int iN;
    };
    struct sExp{
		int iNumber;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    struct sTest mTest[]={
		M_TEST_COLLECTION(1, 3, 7, 28),
		M_TEST_COLLECTION(2, 3, 2, 3),
		M_TEST_COLLECTION(44, 13, 23, 1024),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
		int iResult;
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %d, ", mTest[iConTest].mExp.iNumber);
		//Verification
		iResult = rVRF_Produce(mTest[iConTest].mInput.iM, mTest[iConTest].mInput.iN);
		printf("Verification = %d, ", iResult);
        //Result
		iResult = uniquePath(mTest[iConTest].mInput.iM, mTest[iConTest].mInput.iN);
        printf("Result = %d ", iResult);
        //Comparison
        int iTest = iResult == mTest[iConTest].mExp.iNumber;
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
	*/
}
