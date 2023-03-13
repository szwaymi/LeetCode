
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct sRating {
	unsigned int iScore;
	struct sRating *pmNext;
};
struct sEvaluation {
	unsigned int iID;
	unsigned char iRatings;
	struct sRating mRatings;
};

void rSortEvaluation(struct sEvaluation *pmEvaluations, unsigned int iLength) {

	if (iLength == 1) {
		return;
	}

	unsigned int iLeft;
	unsigned int iRight;
	iLeft = 0;
	iRight = iLength;

	do {
		do {
			iRight--;
		} while (
			pmEvaluations[0].mRatings.iScore <= pmEvaluations[iRight].mRatings.iScore && iLeft < iRight);
		do {
			iLeft++;
		} while (pmEvaluations[0].mRatings.iScore > pmEvaluations[iLeft].mRatings.iScore && iLeft < iRight);
		if (iLeft < iRight) {
			struct sEvaluation mEvaluation;
			memcpy(&mEvaluation, &pmEvaluations[iLeft], sizeof(struct sEvaluation));
			memcpy(&pmEvaluations[iLeft], &pmEvaluations[iRight], sizeof(struct sEvaluation));
			memcpy(&pmEvaluations[iRight], &mEvaluation, sizeof(struct sEvaluation));
		}
	} while (iLeft < iRight);

	{
		struct sEvaluation mEvaluation;
		memcpy(&mEvaluation, &pmEvaluations[0], sizeof(struct sEvaluation));
		memcpy(&pmEvaluations[0], &pmEvaluations[iRight], sizeof(struct sEvaluation));
		memcpy(&pmEvaluations[iRight], &mEvaluation, sizeof(struct sEvaluation));
	}

	if (iRight > 1) {
		rSortEvaluation(&pmEvaluations[0], iRight);
	}
	if (iLength - iRight - 1 > 1) {
		rSortEvaluation(&pmEvaluations[iRight + 1], iLength - iRight - 1);
	}
	return;
}

char *** groupAnagrams(char ** ppcStrs, int iLength, int *piGroups, int** ppiGroupLengthes){
	
	struct sEvaluation *pmEvaluations = (struct sEvaluation *)malloc(sizeof(struct sEvaluation) * iLength);
	unsigned int iCon;
	for (iCon = 0; iCon < (unsigned int)iLength; iCon++) {
		pmEvaluations[iCon].iID = iCon;
		pmEvaluations[iCon].iRatings = 0;
		pmEvaluations[iCon].mRatings.iScore = 0;
		pmEvaluations[iCon].mRatings.pmNext = NULL;

		char *pcCheck = ppcStrs[iCon];
		while (*pcCheck) {
			unsigned int iMask = 1 << (*pcCheck - 'a');
			struct sRating *pmNext = &pmEvaluations[iCon].mRatings;
			struct sRating *pmRating;
			do {
				pmRating = pmNext;
				if ((iMask & pmRating->iScore) ^ iMask) {
					pmRating->iScore |= iMask;
					break;
				}
				pmNext = pmRating->pmNext;
			} while (pmNext);
			if (pmNext == NULL) {
				pmNext = (struct sRating *)malloc(sizeof(struct sRating));
				pmNext->iScore = iMask;
				pmNext->pmNext = NULL;
				pmRating->pmNext = pmNext;
				pmEvaluations[iCon].iRatings++;
			}
			pcCheck++;
		}
		printf("%X %d ", pmEvaluations[iCon].mRatings.iScore, pmEvaluations[iCon].iRatings);
	}

	printf("\n");
	rSortEvaluation(pmEvaluations, iLength);
	/*
	//Calculate Number of Groups
	int iGroups = 0;
	unsigned int iScore = 0x80000000;
	for (iCon = 0; iCon < (unsigned int)iLength; iCon++) {
		if (pmEvaluation[iCon].mRatings.iScore != iScore) {
			iGroups++;
			iScore = pmEvaluation[iCon].mRatings.iScore;
		}
	}
	printf("%d Groups\n", iGroups);
	int *piGroupLengthes = (int *)malloc(sizeof(int) * iGroups);
	char *** pppcGroups = (char ***)malloc(sizeof(char **) * iGroups);

	//Calculate Group Length
	unsigned int iConGroups;
	unsigned int iLoc = 0;
	for (iConGroups = 0; iConGroups < iGroups; iConGroups++) {
		int iGroupLength = 0;
		iScore = pmEvaluation[iLoc].mRatings.iScore;
		while (iLoc < iLength && pmEvaluation[iLoc].mRatings.iScore == iScore) {
			iLoc++;
			iGroupLength++;
		}
		piGroupLengthes[iConGroups] = iGroupLength;
		pppcGroups[iConGroups] = (char **)malloc(sizeof(int *) * iGroupLength);
		printf("%d ", iGroupLength);
	}
	iLoc = 0;
	for (iConGroups = 0; iConGroups < iGroups; iConGroups++) {
		unsigned int iConLength;
		for (iConLength = 0; iConLength < piGroupLengthes[iConGroups]; iConLength++) {
			pppcGroups[iConGroups][iConLength] = ppcStrs[pmEvaluation[iLoc].iID];
			iLoc++;
		}
	}

	*piGroups = iGroups;
	*ppiGroupLengthes = piGroupLengthes;

	return pppcGroups;
	*/
	return NULL;
}

int main(void){
    //Test Data
    //  Macro
    //"eat","tea","tan","ate","nat","bat"
#define M_TEST_INPUT(N, ...) char *pcStrs_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP
#define M_TEST_COLLECTION(N) {N, {pcStrs_##N, sizeof(pcStrs_##N) / sizeof(char *)},{1}}
    //  Structure
    struct sInput{
		char **ppcStrs;
		unsigned int iLength;
    };
    struct sExp{
		int iA;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    M_TEST_INPUT(1, "eat","tea","tan","ate","nat","bat");
	M_TEST_INPUT(2, "");
	M_TEST_INPUT(102, "ddddddddddg", "dgggggggggg");
    struct sTest mTest[]={
        //M_TEST_COLLECTION(1),
		//M_TEST_COLLECTION(2),
		M_TEST_COLLECTION(102),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
        printf("Result = ");
		int iGroups;
		int *piGroupsLength;
		groupAnagrams(mTest[iConTest].mInput.ppcStrs, mTest[iConTest].mInput.iLength, &iGroups, &piGroupsLength);
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
