
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "verify.h"

#define M_TEST_EXAM	rVRF_LongestPalindrome

int main(void) {

	//[Test Data]
	//	Structres
	struct sTest{
		unsigned int iNO;
		unsigned int iExp;
		char **ppcExp;
        char *pcData;
	};
	//	Macros
#define M_TEST_EXP(N, ...) char *pcExp_##N[] = {__VA_ARGS__}
#define M_TEST_COLLECTION(N,S) {N, sizeof(pcExp_##N) / sizeof(char *),pcExp_##N, S}
	//	Data
	M_TEST_EXP(1, "bab", "aba");
	M_TEST_EXP(94, "a");
	M_TEST_EXP(100, "aca");
    //  Test Collection
	struct sTest mTest[] = {
		M_TEST_COLLECTION(1, "babad"),
		M_TEST_COLLECTION(94, "a"),
		M_TEST_COLLECTION(100, "aacabdkacaa"),
	};

	unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
	unsigned int iCon;
	for (iCon = 0; iCon < iLength; iCon++) {
		unsigned int iConExp;
		printf("Test Case [%d], Expectation = ", mTest[iCon].iNO);
		for (iConExp = 0; iConExp < mTest[iCon].iExp; iConExp++) {
			printf("(%s)", mTest[iCon].ppcExp[iConExp]);
			if (iConExp != mTest[iCon].iExp - 1) { printf(" "); }
		}
		char *pcResult;
		char *pcString;
		pcString = (char *)malloc(sizeof(char) * strlen(mTest[iCon].pcData) + 1);
		//strcpy_s(pcString, strlen(mTest[iCon].mData.pcString) + 1, mTest[iCon].mData.pcString);
        strcpy(pcString, mTest[iCon].pcData);
		pcResult = M_TEST_EXAM(pcString);
		printf(", Result = (%s) ", pcResult);
		for (iConExp = 0; iConExp < mTest[iCon].iExp; iConExp++) {
			if (strcmp(mTest[iCon].ppcExp[iConExp], pcResult) == 0) { break; }
		}
		free(pcString);
		char iTest;
		iTest = iConExp < mTest[iCon].iExp;
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
    if(iCon == iLength){
        printf("[PASS]");
    }else{
        printf("[FAIL]");
    }
    printf("\n");
	return 0;
}
