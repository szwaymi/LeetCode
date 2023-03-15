
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int maxSubArray(int* piSeries, int iLength) {

	if (iLength == 1) {
		return *piSeries;
	}

	int iLeft = 0;
	int iRight = iLength - 1;

	int iMin;
	int iCon;
	int iSum;

	iMin = 0x7FFFFFFF;
	iSum = 0;
	for (iCon = 0; iCon < iLength; iCon++) {
		iSum += piSeries[iCon];
		if (iSum < iMin) {
			iMin = iSum;
			iLeft = iCon + 1;
		}
	}
	if (iLeft == iLength - 1) { return piSeries[iLeft]; }

	iMin = 0x7FFFFFFF;
	iSum = 0;
	for (iCon = iLength; iCon > 0; iCon--) {
		iSum += piSeries[iCon - 1];
		if (iSum < iMin) {
			iMin = iSum;
			iRight = iCon - 2;
		}
	}

	printf("%d %d\n", iLeft, iRight);

	iSum = 0;
	for (iCon = iLeft; iCon <= iRight; iCon++) {
		iSum += piSeries[iCon];
	}
	return iSum;
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
	M_TEST_INPUT(2, 1);
	M_TEST_INPUT(3, 5, 4, -1, 7, 8);
	M_TEST_INPUT(129, -2, 1);
	M_TEST_INPUT(134, -1, -2);
	M_TEST_INPUT(140, -1);
	M_TEST_INPUT(154, -2, -1);
	M_TEST_INPUT(1024, -10, -1, -1, 1, 2, 3);
	M_TEST_INPUT(1025, -100, -2, 1, 1, 1, 1,-300);
	struct sTest mTest[] = {
		/*
		M_TEST_COLLECTION(1, 6),
		M_TEST_COLLECTION(2, 1),
		M_TEST_COLLECTION(3, 23),
		M_TEST_COLLECTION(129, 1),
		M_TEST_COLLECTION(134, -1),
		M_TEST_COLLECTION(140, -1),
		M_TEST_COLLECTION(154, -1),
		M_TEST_COLLECTION(1024, 6),
		*/
		M_TEST_COLLECTION(1025, 1),
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
