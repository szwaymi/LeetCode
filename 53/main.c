
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int maxSubArray(int* piSeries, int iLength) {
	int iMax = 0x80000000;
	unsigned int iConLeft;
	unsigned int iConRight;
	for (iConLeft = 0; iConLeft < iLength; iConLeft++) {
		int iSum = 0;
		for (iConRight = iConLeft; iConRight < iLength; iConRight++) {
			iSum += piSeries[iConRight];
			if (iSum > iMax) {
				iMax = iSum;
			}
		}
	}
	return iMax;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, S) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int)} , {S}}
    //  Structure
    struct sInput{
		int *piSeries;
		int iLength;
    };
    struct sExp{
		int iSum;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	M_TEST_INPUT(1, -2, 1, -3, 4, -1, 2, 1, -5, 4);
	M_TEST_INPUT(140, -1);
	M_TEST_INPUT(154, -2, -1);
    struct sTest mTest[]={
		M_TEST_COLLECTION(1, 6),
		M_TEST_COLLECTION(140, -1),
		M_TEST_COLLECTION(154, -1),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %d, ", mTest[iConTest].mExp.iSum);
        //Result
        printf("Result = ");
		int iResult = maxSubArray(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
		printf("%d ", iResult);
        //Comparison
        int iTest = iResult == mTest[iConTest].mExp.iSum;
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
