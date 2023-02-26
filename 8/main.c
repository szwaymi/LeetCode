
#include <stdio.h>
#include "verify.h"

#define M_TEST_EXAM rVRF_MyAtoi

int main(void){
    struct sTest{
        unsigned int iNO;
        int iExp;
        char *pcInput;
    };
    struct sTest mTest[]={
        {   1,           0, "words and 987"},
        {  34,           0, "+-12"},
        {  38, -2147483648, "-91283472332"},
        {  39,           3, "3.1415"},
        {  40,           3, "+3"},
        {  48, -2147483648, "-2147483648"},
        { 163,          42, "42"},
        { 760,         -42, "   -42"},
        {1027,  2147483647, "2147483648"},
        {1029,          -5, "-5-"},
        {1034,           0, "  +  413"},
    };
        
    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iCon;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        printf("Test Case [%d], Expactation = %d, ", mTest[iCon].iNO, mTest[iCon].iExp);
        int iResult;
        iResult = M_TEST_EXAM(mTest[iCon].pcInput);
        printf("Result = %d ", iResult);
        unsigned char iTest = iResult == mTest[iCon].iExp;
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
    if(iCon == iLength){
        printf("[PASS]");
    }else{
        printf("[FAIL]");
    }
    printf("\n");
}
