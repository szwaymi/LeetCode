
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "verify.h"

#define M_TEST_RUN rVRF_Convert

int main(int argc, const char * argv[]) {

    struct sData{
        char *pcString;
        unsigned int iRows;
    };
    struct sTest{
        unsigned int iNO;
        char *pcExp;
        struct sData mData;
    };
    struct sTest mTest[]={
        {1, "PAHNAPLSIIGYIR", {"PAYPALISHIRING", 3}},
        {2, "PINALSIGYAHRPI", {"PAYPALISHIRING", 4}},
        {3, "A", {"A", 1}},
        {4, "A", {"A", 2}},
    };
 
    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iCon;
    for(iCon= 0 ; iCon < iLength ; iCon++){
        printf("Test Case [%d], Expactation = %s, ", iCon, mTest[iCon].pcExp);
        char *pcResult;
        printf("Result = ");
        pcResult = M_TEST_RUN(mTest[iCon].mData.pcString, mTest[iCon].mData.iRows);
        printf("%s ", pcResult);
        int iTest = strcmp(pcResult, mTest[iCon].pcExp);
        free(pcResult);
        if(iTest == 0){
            printf("[PASS]");
        }else{
            printf("[FAIL];");
        }
        printf("\n");
        if(iTest != 0){
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

