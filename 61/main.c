
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct ListNode{
    int val;
    struct ListNode *next;
};
struct ListNode* rotateRight(struct ListNode* pmHead, int iRotates){
    if(pmHead == NULL || iRotates == 0){
        return pmHead;
    }
	unsigned int iLength = 0;
	struct ListNode *pmCheck = pmHead;
	while (pmCheck->next) {
		pmCheck = pmCheck->next;
		iLength++;
	}
	iLength++;
	pmCheck->next = pmHead;
	printf("%d ", iLength);
	//Tail
	struct ListNode *pmResult = pmHead;
	unsigned int iTail = ((iLength - 1) + (iLength - 1) * iRotates) % iLength;
	unsigned int iHead = (iLength - 1) * iRotates % iLength;
	printf("%d %d\n", iHead, iTail);
	pmCheck = pmHead;
	unsigned int iCon;
	for (iCon = 0; iCon < iLength; iCon++) {
		struct ListNode *pmNext = pmCheck->next;
		if (iCon == iHead) {
			pmResult = pmCheck;
		}
		if (iCon == iTail) {
			pmCheck->next = NULL;
		}
		pmCheck = pmNext;
	}
	return pmResult;

	/*
    unsigned int iLen = iRotates + 1;
    struct ListNode **ppmNodes = (struct ListNode **)malloc(sizeof(struct ListNode *) * iLen);
    unsigned int iLoc = 0;
    struct ListNode *pmCheck;
    while(iRotates > -1){
        pmCheck = pmHead;
        while(pmCheck){
            ppmNodes[iLoc] = pmCheck;
            iLoc++;
            iLoc %= iLen;
            iRotates--;
            pmCheck = pmCheck->next;
        }
    }
    for(unsigned int iCon = 0 ; iCon < iLen ; iCon++){
        printf("%d ", ppmNodes[iCon]->val);
    }
    ppmNodes[(iLoc + iLen - 1) % iLen]->next = pmHead;
    ppmNodes[iLoc]->next = NULL;
	*/
    //return ppmNodes[(iLoc + 1) % iLen];
	return NULL;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = {__VA_ARGS__}
#define M_TEST_EXP(N, ...) int iExp_##N[] = {__VA_ARGS__}
#define M_TEST_COLLECTION(N, R) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int), R}, {iExp_##N, sizeof(iExp_##N) / sizeof(int)}}
    //  Structure
    struct sInput{
        int *piSeries;
        int iLength;
        int iRotates;
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
    //      #1
	M_TEST_INPUT(1, 1, 2, 3, 4, 5);
	M_TEST_EXP(1, 4, 5, 1, 2, 3);
    //      #2
    M_TEST_INPUT(2, 0, 1, 2);
    M_TEST_EXP(2, 2, 0, 1);
    //      #6
    M_TEST_INPUT(6, 1);
    M_TEST_EXP(6, 1);
	//		#1024
	M_TEST_INPUT(1024, 1, 2, 3);
	M_TEST_EXP(1024, 3, 2, 1);
    struct sTest mTest[]={
        //M_TEST_COLLECTION(1, 2),
        //M_TEST_COLLECTION(2, 4),
        //M_TEST_COLLECTION(6, 1),
		M_TEST_COLLECTION(1024,20),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
        printf("Result = ");
        
        struct ListNode *list = NULL;
        for(unsigned int iCon = 0 ; iCon < mTest[iConTest].mInput.iLength ; iCon++){
            struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
            node->val = mTest[iConTest].mInput.piSeries[mTest[iConTest].mInput.iLength - 1 - iCon];
            node->next = list;
            list = node;
        }
        struct ListNode *pmResult =
            rotateRight(list, mTest[iConTest].mInput.iRotates);
        
        struct ListNode *pmCheck = pmResult;
        while(pmCheck){
            printf("%d ", pmCheck->val);
            pmCheck = pmCheck->next;
        }
        
        //Comparison
        int iTest = 1;
        pmCheck = pmResult;
        unsigned int iCon = 0;
        while(pmCheck){
            if(pmCheck->val != mTest[iConTest].mExp.piSeries[iCon]){
                iTest = 0;
                break;
            }
            iCon++;
            pmCheck = pmCheck->next;
        }
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
