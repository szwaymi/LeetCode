
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char *gpcEnd;

#define M_TEST_EXAM	longestPalindrome

unsigned int rSearch(char *pcString) {

	char *pcRight = gpcEnd;

	while (pcRight != pcString) {
		while (*pcRight != *pcString) {
			pcRight--;
		}
		if (pcRight == pcString) { return 0; }
		if (pcRight - pcString == 1) { return 1; }

		char *pcSR = pcRight - 1;
		char *pcSL = pcString + 1;
		while (pcSL < pcSR && *pcSL == *pcSR) {
			pcSL++;
			pcSR--;
		}
		if (*pcSL == *pcSR) {
			return (unsigned int)(pcRight - pcString);
		}
		pcRight--;
	}
	return 0;
}
char * longestPalindrome(char * pcString) {
	gpcEnd = pcString;
	while (*gpcEnd) {
		gpcEnd++;
	}
	gpcEnd--;

	unsigned int iMax = 0;
	char *pcMax = pcString;
	while (*pcString) {
		unsigned int iTemp;
		iTemp = rSearch(pcString);
		if (iTemp > iMax) {
			iMax = iTemp;
			pcMax = pcString;
		}
		pcString++;
	}
	pcMax[iMax + 1] = 0;
	return pcMax;
}
int main(void) {

	//[Test Data]
	//	Structres
	struct sData {
		char *pcString;
	};
	struct sTest{
		unsigned int iNO;
		unsigned int iExp;
		char **ppcExp;
		struct sData mData;
	};
	//	Macros
#define M_TEST_EXP(N, ...) char *pcExp_##N[] = {__VA_ARGS__}
#define M_TEST_COLLECTION(N,S) {N, sizeof(pcExp_##N) / sizeof(char *),pcExp_##N, {S}}
	//	Collections
	M_TEST_EXP(1, "bab", "aba");
	M_TEST_EXP(94, "a");
	M_TEST_EXP(100, "aca");
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
		pcString = (char *)malloc(sizeof(char) * strlen(mTest[iCon].mData.pcString) + 1);
		//strcpy_s(pcString, strlen(mTest[iCon].mData.pcString) + 1, mTest[iCon].mData.pcString);
        strcpy(pcString, mTest[iCon].mData.pcString);
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
	return 0;
}
