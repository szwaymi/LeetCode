
#include <stdio.h>
#include "verify.h"

#define M_TEST_EXAM rVRF_Reverse

int main(void){
    struct sTest{
        unsigned int iNO;
        int iExp;
        int iData;
    };
    struct sTest mTest[]={
        {1023, 0, 1534236469},
        {1024, 0, -2147483648},
    };

    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iCon;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        printf("Test Case [%d], Expactation = %d,", mTest[iCon].iNO, mTest[iCon].iExp);
        int iResult;
        iResult = M_TEST_EXAM(mTest[iCon].iData);
        printf(" Result = %d ", iResult);
        unsigned char iTest = iResult == mTest[iCon].iExp;
        if(iTest){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        printf("\n");
    }
    if(iCon == iLength){
        printf("[PASS]");
    }
    else{
        printf("[FAIL]");
    }
    printf("\n");
}
