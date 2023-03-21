
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int rProduce(int iM, int iN) {
	if (iN == 2) {
		return iM;
	}
	unsigned int iCon;
	int iSum = 0;
	for (iCon = 0; iCon < iM; iCon++) {
		iSum += rProduce(iCon + 1, iN - 1);
	}
	return iSum;
}

int uniquePaths(int iM, int iN) {
	if (iN == 1) {
		return 1;
	}
	return rProduce(iM, iN);
}

int main(void){
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
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %d, ", mTest[iConTest].mExp.iNumber);
        //Result
		int iResult = rProduce(mTest[iConTest].mInput.iM, mTest[iConTest].mInput.iN);
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
}
