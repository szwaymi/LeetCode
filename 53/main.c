
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int maxSubArray(int* piSeries, int iLength) {

	int iMin;
	int iMax;
	int iSum;
	unsigned int iCon;
	unsigned int iLeft;
	unsigned int iRight;

	iMin = 0x7FFFFFFF;
	iMax = 0x80000000;
	iSum = 0;
	for (iCon = 0; iCon < iLength; iCon++) {
		iSum += piSeries[iCon];
		if (iSum > iMax) {
			iMax = iSum;
			iRight = iCon;
		}
		if (iSum < 0 && iSum < iMin) {
			iMin = iSum;
			iLeft = iCon + 1;
		}
	}
	printf("%d %d\n", iLeft, iRight);

	return 100;
	/*
	unsigned int iTemp;
	int iResult[2];
	if (iLeft > iRight) { iTemp = iRight; }
	iResult[0] = 0;
	for (iCon = iTemp; iCon <= iRight; iCon++) {
		iResult[0] += piSeries[iCon];
	}
	if (iLeft > iRight) { 
		iTemp = iLeft;
		for (iCon = iTemp; iCon <= iRight; iCon++) {
			iResult[0] += piSeries[iCon];
		}
	}

	*/

	/*
	int iMax = 0x80000000;

	int *piCaches = (int *)malloc(sizeof(int) * iLength);
	unsigned int iConLeft;
	unsigned int iConRight;

	int iSum = 0;
	for (iConRight = 0; iConRight < iLength; iConRight++) {
		iSum += piSeries[iConRight];
		piCaches[iConRight] = iSum;
		if (iSum > iMax) {
			iMax = iSum;
		}
	}

	for(iConLeft = 1; iConLeft < iLength ; iConLeft++)
	{
		for (iConRight = iConLeft; iConRight < iLength; iConRight++) {
		}
	}

	free(piCaches);
	*/
	return iSum;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP
#define M_TEST_COLLECTION(N) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int)} , {0}}
    //  Structure
    struct sInput{
		int *piSeries;
		int iLength;
    };
    struct sExp{
		int *piSeries;
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
		//M_TEST_COLLECTION(1),
		//M_TEST_COLLECTION(140),
		M_TEST_COLLECTION(154)
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
        printf("Result = ");
		int iResult = maxSubArray(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
		printf("%d", iResult);
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
