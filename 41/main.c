
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int firstMissingPositive(int* piSeries, int iLength){

    unsigned int iCon;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        
        int iLast = 0;
        int *piValue = &piSeries[iCon];
        int iLoc = iCon;
        
        while(1){
            if(*piValue <= 0 || *piValue > iLength){
                *piValue = iLast;
                break;
            }else if(*piValue != iLoc + 1){
                iLoc = *piValue - 1;
                *piValue = iLast;
                piValue = &piSeries[iLoc];
                iLast = iLoc + 1;
            }else{
                break;
            }
        }
    }
    
    for(iCon = 0 ; iCon < iLength ; iCon++){
        if(piSeries[iCon] == 0){
            return iCon + 1;
        }
    }
    return iCon + 1;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = {__VA_ARGS__}
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, E) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int)}, {E}}
    //  Structure
    struct sInput{
        int *piSeries;
        int iLength;
    };
    struct sExp{
        int iValue;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    //      #1
    M_TEST_INPUT(1, 1, 2, 0);
    //      #2
    M_TEST_INPUT(2, 3, 4, -1, 1);
    //      #3
    M_TEST_INPUT(3, 7, 8, 9, 11, 12);
    //      #31
    M_TEST_INPUT(31, 1, 1);
    //      #165
    M_TEST_INPUT(165, 1);
    struct sTest mTest[]={
        M_TEST_COLLECTION(165, 2),
        M_TEST_COLLECTION(31, 2),
        M_TEST_COLLECTION(3, 1),
        M_TEST_COLLECTION(2, 2),
        M_TEST_COLLECTION(1, 3),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %d, ", mTest[iConTest].mExp.iValue);
        //Result
        printf("Result = ");
        int iResult =
            firstMissingPositive(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
        printf("%d ", iResult);
        //Comparison
        int iTest = iResult == mTest[iConTest].mExp.iValue;
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
