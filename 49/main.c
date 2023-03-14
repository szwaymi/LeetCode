
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DBPRINT(...)

struct sRating {
	unsigned int iScore;
	struct sRating *pmNext;
};
struct sEvaluation {
	unsigned int iID;
	unsigned char iRatings;
	struct sRating mRatings;
};

int rCompare(struct sEvaluation *pmEvaA, struct sEvaluation *pmEvaB){
    int iResult = 0;
    unsigned int iMin = pmEvaA->iRatings;
    int iMatch = 0;
    
    iMatch = (int)pmEvaA->iRatings - (int)pmEvaB->iRatings;
    if(iMin > pmEvaB->iRatings){
        iMin = pmEvaB->iRatings;
    }

    unsigned int iCon;
    struct sRating *pmRatingA = &pmEvaA->mRatings;
    struct sRating *pmRatingB = &pmEvaB->mRatings;
    for(iCon = 0 ; iCon < iMin ; iCon++){
        iResult = (int)pmRatingA->iScore - (int)pmRatingB->iScore;
        if(iResult != 0){
            break;
        }
        pmRatingA = pmRatingA->pmNext;
        pmRatingB = pmRatingB->pmNext;
    }
    if(iCon == iMin && iMatch != 0){
        return iMatch;
    }
    return iResult;
}

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
		} while (rCompare(&pmEvaluations[0], &pmEvaluations[iRight]) <= 0 && iLeft < iRight);
                 //pmEvaluations[0].mRatings.iScore <= pmEvaluations[iRight].mRatings.iScore
		do {
			iLeft++;
		} while (rCompare(&pmEvaluations[0], &pmEvaluations[iLeft]) > 0 && iLeft < iRight);
        //pmEvaluations[0].mRatings.iScore > pmEvaluations[iLeft].mRatings.iScore && iLeft < iRight);
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
    printf("\n");
	struct sEvaluation *pmEvaluations = (struct sEvaluation *)malloc(sizeof(struct sEvaluation) * iLength);
	unsigned int iCon;
	for (iCon = 0; iCon < (unsigned int)iLength; iCon++) {
		pmEvaluations[iCon].iID = iCon;
		pmEvaluations[iCon].iRatings = 1;
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
		DBPRINT("(%X %d) ", pmEvaluations[iCon].mRatings.iScore, pmEvaluations[iCon].iRatings);
	}
    DBPRINT("\n");
	rSortEvaluation(pmEvaluations, iLength);
    for(unsigned int iConT = 0 ; iConT < iLength ; iConT++){
        DBPRINT("(%X %d) ", pmEvaluations[iConT].mRatings.iScore, pmEvaluations[iConT].iRatings);
    }
	
	//Calculate Number of Groups
	int iGroups = 1;
	for (iCon = 1; iCon < (unsigned int)iLength; iCon++) {
        if(rCompare(&pmEvaluations[iCon], &pmEvaluations[iCon - 1]) != 0){
			iGroups++;
		}
	}
    DBPRINT("%d Groups\n", iGroups);
	int *piGroupLengthes = (int *)malloc(sizeof(int) * iGroups);
	char *** pppcGroups = (char ***)malloc(sizeof(char **) * iGroups);

	//Calculate Group Length
	unsigned int iConGroups;
	unsigned int iLoc = 0;
	for (iConGroups = 0; iConGroups < iGroups; iConGroups++) {
		int iGroupLength = 0;
        do{
            iLoc++;
            iGroupLength++;
        }while(iLoc < iLength  && rCompare(&pmEvaluations[iLoc], &pmEvaluations[iLoc - 1]) == 0);
		piGroupLengthes[iConGroups] = iGroupLength;
		pppcGroups[iConGroups] = (char **)malloc(sizeof(int *) * iGroupLength);
        DBPRINT("%d ", iGroupLength);
	}
    
    //Collect Data into Pointers
	iLoc = 0;
	for (iConGroups = 0; iConGroups < iGroups; iConGroups++) {
		unsigned int iConLength;
		for (iConLength = 0; iConLength < piGroupLengthes[iConGroups]; iConLength++) {
			pppcGroups[iConGroups][iConLength] = ppcStrs[pmEvaluations[iLoc].iID];
            struct sRating *pmRating;
            while(pmEvaluations[iLoc].mRatings.pmNext){
                pmRating = pmEvaluations[iLoc].mRatings.pmNext;
                pmEvaluations[iLoc].mRatings.pmNext = pmRating->pmNext;
                free(pmRating);
            }
            free(pmEvaluations[iLoc].mRatings.pmNext);
			iLoc++;
		}
	}

    free(pmEvaluations);
    
	*piGroups = iGroups;
	*ppiGroupLengthes = piGroupLengthes;

	return pppcGroups;
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
        M_TEST_COLLECTION(1),
		M_TEST_COLLECTION(2),
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
        char ***ppcResults;
		ppcResults = groupAnagrams(mTest[iConTest].mInput.ppcStrs, mTest[iConTest].mInput.iLength, &iGroups, &piGroupsLength);
        unsigned int iConGroups;
        for(iConGroups = 0 ; iConGroups < iGroups ; iConGroups++){
            unsigned int iConLength;
            printf("[");
            for(iConLength = 0 ; iConLength < piGroupsLength[iConGroups] ; iConLength++){
                printf("\"");
                printf("%s",ppcResults[iConGroups][iConLength]);
                printf("\" ");
            }
            printf("]\n");
        }
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
