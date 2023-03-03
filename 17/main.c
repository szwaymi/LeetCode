
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct {
	char *pcAlphabet[8];
	char *pcTemp;
	char *pcDigits;
	char **ppcResults;
	unsigned int iResult;
}gmMeta = {
	{"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"}
};

void rStrCpy(char *pcDes, char *pcSrc) {
	do {
		*pcDes = *pcSrc;
		pcDes++;
		*pcSrc++;
	} while (*pcSrc);
	*pcDes = NULL;
}

void rPermutation(char *pcDigits, char *pcTemp) {
	if (*pcDigits == NULL) {
		strcpy_s(gmMeta.ppcResults[gmMeta.iResult], strlen(gmMeta.pcTemp) +1 , gmMeta.pcTemp);
		//strcpy_s()
		//rStrCpy(gmMeta.ppcResults[gmMeta.iResult], gmMeta.pcTemp);
		//printf("%s\n", gmMeta.pcTemp);
		gmMeta.iResult++;
	}else{
		char *pcAlphabet = gmMeta.pcAlphabet[*pcDigits - '2'];
		do {
			*pcTemp = *pcAlphabet;
			rPermutation(pcDigits + 1, pcTemp + 1);
			pcAlphabet++;
		} while (*pcAlphabet);
	}
}

char ** letterCombinations(char * pcDigits, int* piResults){

	//Get Result Numbers
	int iResults = 1;
	char *pcV = pcDigits;
    while(*pcV){
        iResults *= strlen(gmMeta.pcAlphabet[*pcV - '2']);
        pcV++;
    }
    
	gmMeta.pcDigits = pcDigits;

	unsigned int iLength = (unsigned int)strlen(pcDigits) + 1;
    gmMeta.ppcResults = (char **)malloc(sizeof(char *) * iResults);
    for(unsigned int iCon = 0 ; iCon < iResults ; iCon++){
        gmMeta.ppcResults[iCon] = (char *)malloc(sizeof(char) * iLength);
    }

	gmMeta.pcTemp = (char *)malloc(sizeof(char) * iLength);
	gmMeta.pcTemp[iLength - 1] = NULL;
    *piResults = iResults;

	gmMeta.iResult = 0;
	
	rPermutation(pcDigits, gmMeta.pcTemp);
	free(gmMeta.pcTemp);

	return gmMeta.ppcResults;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_DATA_OUT(N, ...) char *pcOut_##N[] = { __VA_ARGS__ };
#define M_TEST_COLLECTION(N, S) {N, S, {sizeof(pcOut_##N) / sizeof(char *), pcOut_##N}}
    //  Structure
    struct sOutput{
        unsigned int iNumber;
        char **ppcOut;
    };
    struct sTest{
        unsigned int iNO;
        char *pcInput;
        struct sOutput mOutput;
    };
    //  Data
    M_TEST_DATA_OUT(1, "ad","ae","af","bd","be","bf","cd","ce","cf");
	M_TEST_DATA_OUT(2, "");
    struct sTest mTest[] = {
        M_TEST_COLLECTION(1, "23"),
		M_TEST_COLLECTION(2, ""),
    };
    
    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    
    for(iConTest = 0 ; iConTest < iLength ; iConTest++){
        
		printf("Test Case [%d], Expactation = ", mTest[iConTest].iNO);
        for(unsigned int iConExp = 0 ; iConExp < mTest[iConTest].mOutput.iNumber ; iConExp++){
            printf("[%s] ", mTest[iConTest].mOutput.ppcOut[iConExp]);
        }
		printf("\n");

		int iResults;
		char **ppcResults;
		ppcResults = letterCombinations(mTest[iConTest].pcInput, &iResults);
		for (unsigned int iConResults = 0; iConResults < iResults; iConResults++) {
			printf("[%s] ", ppcResults[iConResults]);
		}



    }
    
}
