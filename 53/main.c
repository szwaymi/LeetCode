
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int maxSubArray(int* piSeries, int iLength) {

	struct sResult{
		int iLoc;
		int iMax;
		struct sResult *pmNext;
	};

	if (iLength == 1) {
		return *piSeries;
	}

	struct sMax{
		unsigned int iLength;
		struct sResult mResult;
	};

	struct sMax mLeft;
	struct sMax mRight;

	mLeft.mResult.iLoc = 0;
	mLeft.mResult.pmNext = NULL;
	mLeft.iLength = 0;
	mRight.mResult.iLoc = iLength - 1;
	mRight.mResult.pmNext = NULL;
	mRight.iLength = 0;

	int iCon;
	int iMax;
	int iSum;

	iSum = 0;
	iMax = 0x80000000;
	for (iCon = 0; iCon < iLength; iCon++) {
		iSum += piSeries[iCon];
		if (iSum >= iMax) {
			iMax = iSum;
			mRight.mResult.iLoc = iCon;
			struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
			pmResult->iLoc = iCon;
			pmResult->iMax = iSum;
			pmResult->pmNext = mRight.mResult.pmNext;
			mRight.mResult.pmNext = pmResult;
			mRight.iLength++;
		}
	}
	mRight.mResult.iMax = iMax;

	iSum = 0;
	iMax = 0x80000000;
	for (iCon = 0; iCon < iLength; iCon++) {
		iSum += piSeries[iLength - 1 - iCon];
		if (iSum >= iMax) {
			iMax = iSum;
			mLeft.mResult.iLoc = iLength - 1 - iCon;
			struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
			pmResult->iLoc = iLength - 1 - iCon;
			pmResult->iMax = iSum;
			pmResult->pmNext = mLeft.mResult.pmNext;
			mLeft.mResult.pmNext = pmResult;
			mLeft.iLength++;
		}
	}
	mLeft.mResult.iMax = iMax;

	printf("%d %d\n", mLeft.mResult.iLoc, mRight.mResult.iLoc);

	if (mRight.mResult.iLoc < mLeft.mResult.iLoc && mLeft.iLength == 1 && mRight.iLength == 1){
		iSum = 0x80000000;
		for (iCon = 0; iCon < iLength; iCon++) {
			if (piSeries[iCon] > iSum) {
				iSum = piSeries[iCon];
			}
		}
		
	}
	else {

		iSum = 0x80000000;
		while (mLeft.mResult.pmNext) {
			struct sResult *pmLeft = mLeft.mResult.pmNext;
			mLeft.mResult.pmNext = pmLeft->pmNext;
			if (pmLeft->iMax == mLeft.mResult.iMax) {
				struct sResult *pmRight = NULL;
				struct sResult *pmTemp = mRight.mResult.pmNext;
				int iDiff = 0x7FFFFFFF;
				while (pmTemp) {
					if (pmTemp->iMax == mRight.mResult.iMax) {
						int iTemp = abs(pmTemp->iLoc - pmLeft->iLoc);
						if (iTemp < iDiff) {
							iDiff = iTemp;
							pmRight = pmTemp;
						}
					}
					pmTemp = pmTemp->pmNext;
				}
				int iTemp = 0;
				for (iCon = pmLeft->iLoc; iCon <= pmRight->iLoc; iCon++) {
					iTemp += piSeries[iCon];
				}
				if (iTemp > iSum) {
					iSum = iTemp;
				}
			}
			free(pmLeft);
		}

		while (mRight.mResult.pmNext) {
			struct sResult *pmResult = mRight.mResult.pmNext;
			mRight.mResult.pmNext = pmResult->pmNext;
			free(pmResult);
		}
	
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
	M_TEST_INPUT(11, 1, -1, 1);
	M_TEST_INPUT(13, -1, 0, -2);
	M_TEST_INPUT(129, -2, 1);
	M_TEST_INPUT(134, -1, -2);
	M_TEST_INPUT(140, -1);
	M_TEST_INPUT(154, -2, -1);
	M_TEST_INPUT(171, -1, 0, -2, 2);
	M_TEST_INPUT(178, 0, -3, 1, 1);
	M_TEST_INPUT(184, 1, 2, -1, -2, 2, 1, -2, 1);
	M_TEST_INPUT(1024, -10, -1, -1, 1, 2, 3);
	M_TEST_INPUT(1025, -100, -2, 1, 1, 1, 1,-300);
	struct sTest mTest[] = {
		M_TEST_COLLECTION(178, 0),
		/*
		M_TEST_COLLECTION(1, 6),
		M_TEST_COLLECTION(2, 1),
		M_TEST_COLLECTION(3, 23),
		M_TEST_COLLECTION(3, 23),
		M_TEST_COLLECTION(11, 1),
		M_TEST_COLLECTION(13, 0),
		M_TEST_COLLECTION(129, 1),
		M_TEST_COLLECTION(134, -1),
		M_TEST_COLLECTION(140, -1),
		M_TEST_COLLECTION(154, -1),
		M_TEST_COLLECTION(171, 2),
		M_TEST_COLLECTION(178, 2),
		M_TEST_COLLECTION(184, 3),
		M_TEST_COLLECTION(1024, 6),
		M_TEST_COLLECTION(1025, 4),
		*/
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
