
#include <stdlib.h>
#include <stdio.h>

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

int** combinationSum(int* piCandidates, int iLength, int iTarget, int* piResults, int** ppiLengthes){

	rTST_QuickSort(piCandidates, iLength);
	struct sResult {
		int *piSeries;
		unsigned int iNumber;
		struct sResult *pmNext;
	};
	int iResults = 0;
	struct sResult *pmResults = NULL;

	unsigned int iConNumber;
    unsigned int iNumber = iTarget / piCandidates[0];
	
	unsigned char *piAccs = (unsigned char *)malloc(sizeof(unsigned char) * (iNumber + 1));
    for(iConNumber = 1 ; iConNumber <= iNumber ; iConNumber++){
		unsigned int iConCombine;
		//Initial for each
		for (iConCombine = 0; iConCombine < iConNumber + 1; iConCombine++) {
			piAccs[iConCombine] = 0;
		}
        do{
			//Calculate Sum
            int iSum = 0;
            for(iConCombine = 0 ; iConCombine < iConNumber ; iConCombine++){
				printf("%d ", piAccs[iConNumber - iConCombine - 1]);
				if (piAccs[iConNumber - iConCombine - 1] == 4) {
					printf("X");
				}
                iSum += piCandidates[piAccs[iConNumber - iConCombine - 1]];
                if(iSum > iTarget){
					piAccs[iConNumber - iConCombine - 1] = iLength;
                    break;
                }
            }
			//Produce result
            if(iSum == iTarget && iConCombine == iConNumber){
				struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
				pmResult->pmNext = pmResults;
				pmResults = pmResult;
				pmResult->iNumber = iConNumber;
				pmResult->piSeries = (int *)malloc(sizeof(int) * iConNumber);
				unsigned int iConCombine;
				for (iConCombine = 0; iConCombine < iConNumber; iConCombine++) {
					pmResult->piSeries[iConCombine] = piCandidates[piAccs[iConCombine]];
				}
				iResults++;
            }
			//Acc to next
            piAccs[0]++;
            for(iConCombine = 0 ; iConCombine < iConNumber ; iConCombine++){
                if(piAccs[iConCombine] >= iLength){
                    piAccs[iConCombine] = 0;
                    piAccs[iConCombine + 1]++;
                }else{
                    unsigned int iConBit;
                    for(iConBit = 0 ; iConBit < iConCombine ; iConBit++){
                        piAccs[iConBit] = piAccs[iConCombine];
                    }
                    break;
                }
            }
        }while(piAccs[iConNumber] == 0);
    }	
	*piResults = iResults;
	int **ppiResults = (int **)malloc(sizeof(int *) * iResults);
	int *piLengthes = (int *)malloc(sizeof(int) * iResults);
	unsigned int iConResults;
	for (iConResults = 0; iConResults < iResults; iConResults++) {
		struct sResult *pmResult = pmResults;
		pmResults = pmResults->pmNext;
		ppiResults[iConResults] = pmResult->piSeries;
		piLengthes[iConResults] = pmResult->iNumber;
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
    M_TEST_INPUT(1, 2, 3, 6, 7);
	M_TEST_EXP_SERIES(1, 2, 2, 3, 7);
	M_TEST_EXP_LENGTH(1, 3, 1);
	M_TEST_INPUT(2, 2, 3, 5);
	M_TEST_EXP_SERIES(2, 2, 2, 2, 2, 2, 3, 3, 3, 5);
	M_TEST_EXP_LENGTH(2, 4, 3, 2);
	M_TEST_INPUT(86, 7, 3, 2);
	M_TEST_EXP_SERIES(86, 1);
	M_TEST_EXP_LENGTH(86, 1);
	M_TEST_INPUT(124, 2, 22, 4, 17, 28, 13, 39, 27, 24, 37, 12, 30, 5, 23, 29, 8, 16, 34, 15, 36, 14, 10, 31);
	M_TEST_EXP_SERIES(124, 1);
	M_TEST_EXP_LENGTH(124, 1);
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, 7),
		//M_TEST_COLLECTION(2, 8),
		//M_TEST_COLLECTION(44, 11),
		//M_TEST_COLLECTION(86, 18),
		//M_TEST_COLLECTION(124, 30),
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
