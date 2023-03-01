
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char gpmDigits;

void rCombination(char *pcResult, unsigned int iDigits){
    
}

char ** letterCombinations(char * pcDigits, int* piResults){
    char *pcAlphabet[] = {
      "abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"
    };
    
    char *pcV;
    int iResults = 1;
    unsigned int iLength = (unsigned int)strlen(pcDigits);
    
    pcV = pcDigits;
    while(*pcV){
        iResults *= strlen(pcAlphabet[*pcV - '2']);
        pcV++;
    }
    
    gpmDigits = pcDigits;
    
    char **ppcResults = (char **)malloc(sizeof(char *) * iResults);
    unsigned int iCon;
    for(iCon = 0 ; iCon < iResults ; iCon++){
        ppcResults[iCon] = (char *)malloc(sizeof(char) * (iLength + 1));
        rCombination(ppcResults[iCon], iLength);
    }
    *piResults = iResults;
    return 0;
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
    struct sTest mTest[] = {
        M_TEST_COLLECTION(1, "23"),
    };
    
    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    
    for(iConTest = 0 ; iConTest < iLength ; iConTest++){
        printf("Test Case [%d], Expactation = ", mTest[iConTest].iNO);
        for(unsigned int iConExp = 0 ; iConExp < mTest[iConTest].mOutput.iNumber ; iConExp++){
            printf("[%s] ", mTest[iConTest].mOutput.ppcOut[iConExp]);
        }
    }
    
}
