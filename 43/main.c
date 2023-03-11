
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * multiply(char * pcA, char * pcB){
    unsigned int iLengthA = (unsigned int)strlen(pcA);
    unsigned int iLengthB = (unsigned int)strlen(pcB);
    unsigned int iLengthR = iLengthA + iLengthB;
    
    {
        if(iLengthA > iLengthB){
            unsigned int iTemp;
            char *pcTemp;
            pcTemp = pcA;
            pcA = pcB;
            pcB = pcTemp;
            iTemp = iLengthA;
            iLengthA = iLengthB;
            iLengthB = iTemp;
        }
    }
    
    
    unsigned int *piResults = (unsigned int *)malloc(sizeof(unsigned int) * (iLengthR));
    unsigned int iConDigit;
    unsigned int iCarry = 0 ;
    for(iConDigit = 0 ; iConDigit < iLengthR ; iConDigit++){
        unsigned int iConUnit;
        unsigned int iSum = 0;
        for(iConUnit = 0 ; iConUnit <= iConDigit ; iConUnit++){
            unsigned int iTemp;
            unsigned int iLoc;
            iLoc = iLengthA - 1;
            if(iLoc >= iConUnit){
                iTemp = pcA[iLoc - iConUnit] - '0';
            }else{
                iTemp = 0;
            }
            iLoc = iConDigit - iConUnit;
            if(iLengthB - 1 >= iLoc){
                iTemp *= (pcB[iLengthB - 1 - iLoc] - '0');
            }else{
                iTemp = 0;
            }
            iSum += (iTemp);
        }
        iSum += iCarry;
        piResults[iLengthR - iConDigit - 1] = iSum % 10;
        iCarry = iSum / 10;
    }
    
    char *pcResult = (char *)malloc(sizeof(char) * (iLengthR + 1));
    char *pcPut = pcResult;
    unsigned int iConHead;
    for(iConHead = 0 ; iConHead < iLengthR ; iConHead++){
        if(piResults[iConHead]){
            break;
        }
    }
    if(iConHead == iLengthR){
        *pcPut = '0' ;
        pcPut++;
    }else{
        for(iConDigit = iConHead ; iConDigit < iLengthR ; iConDigit++){
            *pcPut = piResults[iConDigit] + '0';
            pcPut++;
        }
    }
    *pcPut = 0;
    free(piResults);
    return pcResult;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_COLLECTION(N,A,B,R) {N, {A, B}, {R}}
    //  Structure
    struct sInput{
        char *pcA;
        char *pcB;
    };
    struct sExp{
        char *pcResult;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, "2", "3", "6"),
        M_TEST_COLLECTION(2, "123", "456", "56088"),
        M_TEST_COLLECTION(299, "0", "0", "0"),
        M_TEST_COLLECTION(1024, "396", "487", "192852"),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %s, ", mTest[iConTest].mExp.pcResult);
        //Result
        char *pcResult = multiply(mTest[iConTest].mInput.pcA, mTest[iConTest].mInput.pcB);
        printf("Result = %s,", pcResult);
        //Comparison
        int iTest = strcmp(mTest[iConTest].mExp.pcResult, pcResult);
        if(iTest == 0){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        free(pcResult);
        printf("\n");
        if(iTest){
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
