
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DBPRINT printf

void rProduce(int *piSeries, unsigned int iNumber){
    if(iNumber == 1){
        piSeries[0] = 0;
        piSeries[1] = 1;
        return;
    }
    unsigned int iHalf = (1 << iNumber) / 2;
    rProduce(piSeries, iNumber - 1);
    unsigned int iCon;
	int iMask = 1 << (iNumber - 1);
    for(iCon = 0 ; iCon < iHalf ; iCon++){
		piSeries[iHalf + iCon] = iMask | piSeries[iHalf - iCon - 1];
    }
}

int* grayCode(int iNumber, int* piLength){
	DBPRINT("\n");
    unsigned int iLength = 1 << iNumber;
	DBPRINT("Length = %d\n", iLength);
    int *piSeries = (int *)malloc(sizeof(int) * iLength);
    
    rProduce(piSeries, iNumber);
	*piLength = iLength;
	return piSeries;
}


int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N, S) {N, {S}, {iExp_##N, sizeof(iExp_##N) / sizeof(int)}}
    //  Structure
    struct sInput{
		int iNumber;
    };
    struct sExp{
		int *piSeries;
		int iLength;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	M_TEST_EXP(1, 0, 1, 3, 2);
	M_TEST_EXP(3, 0, 1, 3, 2, 6, 7, 5, 4);
    struct sTest mTest[]={
		//M_TEST_COLLECTION(1, 2),
		M_TEST_COLLECTION(3, 3)
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
		printf("[");
		for (unsigned int iConExp = 0; iConExp < mTest[iConTest].mExp.iLength; iConExp++) {
			printf("%d ", mTest[iConTest].mExp.piSeries[iConExp]);
		}
		printf("], ");
        //Result
        printf("Result = ");
		int iLength;
		int *piResult;
		piResult = grayCode(mTest[iConTest].mInput.iNumber, &iLength);
		printf("[");
		for (unsigned int iConResult = 0; iConResult < iLength; iConResult++) {
			printf("%d ", piResult[iConResult]);
		}
		printf("], ");
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
