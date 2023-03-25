
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* reverseKGroup(struct ListNode* pmList, int iLength) {

	struct ListNode **ppmHead = &pmList;
	struct ListNode *pmCheck = pmList;
	struct ListNode *pmLast;

	while (pmCheck) {
		unsigned int iCon;
		for (iCon = 0; iCon < iLength; iCon++) {
			if (pmCheck == NULL) { break; }
			pmCheck = pmCheck->next;
		}
		if (iCon == iLength) {
			struct ListNode *pmHead = *ppmHead;
			struct ListNode *pmTail = pmCheck;
			struct ListNode *pmLast;

			pmCheck = pmHead;
			pmLast = pmCheck;
			pmCheck = pmCheck->next;
			for (iCon = 1; iCon < iLength; iCon++) {
				struct ListNode *pmNext = pmCheck->next;
				pmCheck->next = pmLast;
				pmLast = pmCheck;
				pmCheck = pmNext;
			}
			*ppmHead = pmLast;
			pmHead->next = pmTail;
			pmCheck = pmTail;
			ppmHead = &pmHead->next;
		}
	}

	return pmList;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N, K) {N, {iSeries_##N, K, sizeof(iSeries_##N) / sizeof(int)}, {iExp_##N, sizeof(iExp_##N) / sizeof(int)}}
    //  Structure
    struct sInput{
		int *piSeries;
		int iGroup;
		int iLength;
    };
    struct sExp{
		int *piExp;
		int iLength;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	//		#1
	M_TEST_INPUT(1, 1, 2, 3, 4, 5);
	M_TEST_EXP(1, 2, 1, 4, 3, 5);
	//		#2
	M_TEST_INPUT(2, 1, 2, 3, 4, 5);
	M_TEST_EXP(2, 3, 2, 1, 4, 5);
    struct sTest mTest[]={
		M_TEST_COLLECTION(2, 3),
		M_TEST_COLLECTION(1, 2),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
		struct ListNode *pmList;
		struct ListNode **ppmNode = &pmList;
		for (unsigned int iCon = 0; iCon < mTest[iConTest].mInput.iLength; iCon++) {
			struct ListNode *pmNode = (struct ListNode *)malloc(sizeof(struct ListNode));
			pmNode->val = mTest[iConTest].mInput.piSeries[iCon];
			*ppmNode = pmNode;
			ppmNode = &pmNode->next;
		}
		*ppmNode = NULL;
        printf("Result = ");
		struct ListNode* pmResult =
			reverseKGroup(pmList, mTest[iConTest].mInput.iGroup);
		pmList = pmResult;
		for (unsigned int iCon = 0; iCon < mTest[iConTest].mInput.iLength; iCon++) {
			struct ListNode *pmNode = pmList;
			printf("%d ", pmNode->val);
			pmList = pmList->next;
			free(pmNode);
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
