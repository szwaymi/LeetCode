
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* mergeKLists(struct ListNode** ppmLists, int iLength) {
	struct ListNode *pmHead = NULL;
	struct ListNode **ppmNode = &pmHead;

	struct {
		int iLoc;
		int iValue;
	}mMin;
	unsigned int iCon;
	unsigned int iAcc;
	do {
		iAcc = 0;
		mMin.iValue = 0x7FFFFFFF;
		mMin.iLoc = -1;
		for (iCon = 0; iCon < iLength; iCon++) {
			if (ppmLists[iCon] == NULL) {
				iAcc++;
			}
			else{
				if (ppmLists[iCon]->val < mMin.iValue) {
					mMin.iValue = ppmLists[iCon]->val;
					mMin.iLoc = iCon;
				}
			}
		}
		if (iAcc < iLength) {
			struct ListNode *pmNode = (struct ListNode *)malloc(sizeof(struct ListNode));
			pmNode->val = mMin.iValue;
			*ppmNode = pmNode;
			ppmNode = &pmNode->next;
			ppmLists[mMin.iLoc] = ppmLists[mMin.iLoc]->next;
		}
	} while (iAcc < iLength);

	*ppmNode = NULL;

	return pmHead;
}

int main(void) {

	//Test Data
	//  Macro
#define M_TEST_INPUT_COLL(N, D) int *piSeries_##N[D]; int iSeriesL_##N[D];
#define M_TEST_INPUT_DATA(N, B, ...) int iSeries_##N ##B[] = __VA_ARGS__ ;piSeries_##N[B] = iSeries_##N##B;iSeriesL_##N[B] = sizeof(iSeries_##N##B) / sizeof(int)
#define M_TEST_EXP(N, ...) int iExp_##N[] =  __VA_ARGS__ 
#define M_TEST_COLLECTION(N) {N, {piSeries_##N, iSeriesL_##N, sizeof(iSeriesL_##N) / sizeof(int)}, {iExp_##N, sizeof(iExp_##N) / sizeof(int)}}
	//  Structure
	struct sInput {
		int **ppiSeries;
		int *piLengthes;
		int iLength;
	};
	struct sExp {
		int *piSeries;
		int iLength;
	};
	struct sTest {
		unsigned int iNO;
		struct sInput mInput;
		struct sExp mExp;
	};
	//  Data
	//		#1
	M_TEST_INPUT_COLL(1, 3);
	M_TEST_INPUT_DATA(1, 0, { 1, 4, 5 });
	M_TEST_INPUT_DATA(1, 1, { 1, 3, 4 });
	M_TEST_INPUT_DATA(1, 2, { 2, 6 });
	M_TEST_EXP(1, { 1, 1, 2, 3, 4, 4, 5, 6 });
	struct sTest mTest[] = {
		M_TEST_COLLECTION(1),
	};
	unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
	unsigned int iConTest;
	for (iConTest = 0; iConTest < iLengthTest; iConTest++) {
		printf("Test Case [%d], ", mTest[iConTest].iNO);
		//Expectaion
		printf("Expecation = ");
		//Result
		printf("Result = ");
		struct ListNode **ppmLists = (struct ListNode **)malloc(sizeof(struct ListNode) * mTest[iConTest].mInput.iLength);
		for (unsigned int iCon = 0; iCon < mTest[iConTest].mInput.iLength; iCon++) {
			struct ListNode **ppmNode = &ppmLists[iCon];
			for (unsigned int iConS = 0; iConS < mTest[iConTest].mInput.piLengthes[iCon]; iConS++) {
				struct ListNode *pmNode = (struct ListNode *)malloc(sizeof(struct ListNode));
				pmNode->val = mTest[iConTest].mInput.ppiSeries[iCon][iConS];
				*ppmNode = pmNode;
				ppmNode = &pmNode->next;
			}
			*ppmNode = NULL;
		}
		struct ListNode* pmResult =
			mergeKLists(ppmLists, mTest[iConTest].mInput.iLength);
		while (pmResult) {
			printf("%d ", pmResult->val);
			pmResult = pmResult->next;
		}
		printf("\n");
		//Comparison
		int iTest = 1;
		if (iTest) {
			printf("[PASS]");
		}
		else {
			printf("[FAIL]");
		}
		printf("\n");
		if (!iTest) {
			break;
		}
	}
	printf("All Test Case : ");
	if (iConTest < iLengthTest) {
		printf("[FAIL]");
	}
	else {
		printf("[PASS]");
	}
	printf("\n");

}
