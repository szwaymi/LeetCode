
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void rTST_QuickSort(int *piValues, unsigned int iSize) {

	unsigned int iLeft;
	unsigned int iRight;
	iLeft = 0;
	iRight = iSize;

	do {
		do {
			iRight--;
		} while (piValues[0] <= piValues[iRight] && iLeft < iRight);
		do {
			iLeft++;
		} while (piValues[0] > piValues[iLeft] && iLeft < iRight);
		if (iLeft < iRight) {
			unsigned int iTemp;
			iTemp = piValues[iLeft];
			piValues[iLeft] = piValues[iRight];
			piValues[iRight] = iTemp;
		}
	} while (iLeft < iRight);

	unsigned int iTemp;
	iTemp = piValues[0];
	piValues[0] = piValues[iRight];
	piValues[iRight] = iTemp;

	if (iRight > 1) {
		rTST_QuickSort(&piValues[0], iRight);
	}
	if (iSize - iRight - 1 > 1) {
		rTST_QuickSort(&piValues[iRight + 1], iSize - iRight - 1);
	}
	return;
}
struct sResult{
    int *piSeries;
    int iLength;
    struct sResult *pmNext;
};
static struct{
    int *piSeries;
    int iLength;
    int iTarget;
    int iNumber;
    int *piResult;
    struct sResult *pmResults;
    int iResults;
}gmMeta;

void rMatch(int iNumber, int iSum, int iLoc){
    if(iNumber == 0){
        if(iSum == gmMeta.iTarget){
            struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
            pmResult->pmNext = gmMeta.pmResults;
            gmMeta.pmResults = pmResult;
            
            pmResult->iLength = gmMeta.iNumber;
            
            pmResult->piSeries = (int *)malloc(sizeof(int) * pmResult->iLength);
            
            memcpy(pmResult->piSeries, gmMeta.piResult, sizeof(int) * pmResult->iLength);
            gmMeta.iResults++;
        }
        return;
    }
    unsigned int iCon;
    for(iCon = iLoc ; iCon < gmMeta.iLength ; iCon++){
        gmMeta.piResult[iNumber - 1] = gmMeta.piSeries[iCon];
        int iTemp = iSum + gmMeta.piSeries[iCon];
        if(iTemp > gmMeta.iTarget){
            break;
        }
        rMatch(iNumber - 1, iTemp, iCon);
    }
}
int** combinationSum(int* piCandidates, int iLength, int iTarget, int* piResults, int** ppiLengthes){

    
    printf("\n");
	rTST_QuickSort(piCandidates, iLength);
    
    int iNumber = iTarget / piCandidates[0];
    
    gmMeta.piSeries = piCandidates;
    gmMeta.iLength = iLength;
    gmMeta.iTarget = iTarget;
    gmMeta.piResult = (int *)malloc(sizeof(int) * iNumber);
    gmMeta.pmResults = NULL;
    gmMeta.iResults = 0;
    unsigned int iCon;
    for(iCon = 1 ; iCon <= iNumber ; iCon++){
        gmMeta.iNumber = iCon;
        rMatch(iCon, 0, 0);
    }
    
	*piResults = gmMeta.iResults;
    int **ppiResults = (int **)malloc(sizeof(int *) * gmMeta.iResults);
    int *piLengthes = (int *)malloc(sizeof(int) * gmMeta.iResults);
	unsigned int iConResults;
	for (iConResults = 0; iConResults < gmMeta.iResults; iConResults++) {
		struct sResult *pmResult = gmMeta.pmResults;
		gmMeta.pmResults = gmMeta.pmResults->pmNext;
		ppiResults[iConResults] = pmResult->piSeries;
		piLengthes[iConResults] = pmResult->iLength;
		free(pmResult);
	}
	*ppiLengthes = piLengthes;
    return ppiResults;
}

int main(void){

#define M_TEST_EXP_SERIES(N, ...) int iExp_Ser_##N[] = {__VA_ARGS__}
#define M_TEST_EXP_LENGTH(N, ...) int iExp_Len_##N[] = {__VA_ARGS__}
#define M_TEST_INPUT(N, ...) int iCandiates_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N, T) {N, {T, iCandiates_##N, sizeof(iCandiates_##N) / sizeof(int)}, {sizeof(iExp_Len_##N) / sizeof(int), iExp_Ser_##N, iExp_Len_##N}}
    struct sInput{
        int iTarget;
        int *piCandiates;
        unsigned int iLength;
    };
	struct sExp {
		int iResults;
		int *piResults;
		int *piLengthes;
	};
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
		struct sExp mExp;
    };
    //#1
    M_TEST_INPUT(1, 2, 3, 6, 7);
	M_TEST_EXP_SERIES(1, 2, 2, 3, 7);
	M_TEST_EXP_LENGTH(1, 3, 1);
    //#2
	M_TEST_INPUT(2, 2, 3, 5);
	M_TEST_EXP_SERIES(2, 2, 2, 2, 2, 2, 3, 3, 3, 5);
	M_TEST_EXP_LENGTH(2, 4, 3, 2);
    //#86
	M_TEST_INPUT(86, 7, 3, 2);
	M_TEST_EXP_SERIES(86, 1);
	M_TEST_EXP_LENGTH(86, 1);
    //#124
	M_TEST_INPUT(124, 2, 22, 4, 17, 28, 13, 39, 27, 24, 37, 12, 30, 5, 23, 29, 8, 16, 34, 15, 36, 14, 10, 31);
	M_TEST_EXP_SERIES(124, 1);
	M_TEST_EXP_LENGTH(124, 1);
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, 7),
		//M_TEST_COLLECTION(2, 8),
		//M_TEST_COLLECTION(44, 11),
		//M_TEST_COLLECTION(86, 18),
		M_TEST_COLLECTION(124, 30),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
		
		//Test Case
        printf("Test Case [%d], ", mTest[iConTest].iNO);

		//Expectation
		printf("Expectation = ");
		unsigned int iConExp;
		unsigned int iLocExp = 0;
		for (iConExp = 0; iConExp < mTest[iConTest].mExp.iResults; iConExp++) {
			printf("[");
			unsigned int iConSeries;
			for(iConSeries = 0 ; iConSeries < mTest[iConTest].mExp.piLengthes[iConExp] ; iConSeries++){
				printf("%d ", mTest[iConTest].mExp.piResults[iConSeries + iLocExp]);
			}
			iLocExp += mTest[iConTest].mExp.piLengthes[iConExp];
			printf("]");
		}

		//Result
        int iResults;
        int *piLengthes;
        int **ppiResults;
        ppiResults = combinationSum(mTest[iConTest].mInput.piCandiates, mTest[iConTest].mInput.iLength, mTest[iConTest].mInput.iTarget, &iResults, &piLengthes);
		printf("Result = ");
		unsigned int iConResults;
		for (iConResults = 0; iConResults < iResults; iConResults++) {
			printf("[");
			unsigned int iConSeries;
			for (iConSeries = 0; iConSeries < piLengthes[iConResults]; iConSeries++) {
				printf("%d ", ppiResults[iConResults][iConSeries]); 
			}
			printf("] ");
		}

		//Comparison
		/*
		int iTest;
		//	Result Numbers
		iTest = mTest[iConTest].mExp.iResults == iResults;
		//	
		if (iTest) {
			for (iConExp = 0; iConExp < mTest[iConTest].mExp.iResults; iConExp++) {
				for (iConResults = 0; iConResults < iResults; iConResults++) {

				}
			}

		}
		*/

        printf("\n");
    }
    
}
