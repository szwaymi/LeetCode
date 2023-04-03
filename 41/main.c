
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int firstMissingPositive(int* piSeries, int iLength){

    int iCon;
    int iLenQualify;
    int iLenTemp;
    int iMax = 0;
    int iMin = 0x7FFFFFFF;
    unsigned long long iSum;
    
    //Remove Negative and Zero
    iLenTemp = 0;
    iSum = 0;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        if(piSeries[iCon] > 0){
            iLenTemp++;
            if(piSeries[iCon] > iMax){iMax = piSeries[iCon];}
            if(piSeries[iCon] < iMin){iMin = piSeries[iCon];}
            iSum += (unsigned long long)piSeries[iCon];
        }
    }
    iLenQualify = iLenTemp;
    
    int iHole;
    iHole = iMax - iLenQualify;
    while(iHole > 1){
        iLenTemp = 0;
        iMax = 0;
        for(iCon = 0 ; iCon < iLength ; iCon++){
            if(piSeries[iCon] > iLenQualify){
                iSum -= piSeries[iCon];
            }else{
                if(piSeries[iCon] > iMax){iMax = piSeries[iCon];}
                iLenTemp++;
            }
        }
        iHole = iMax - iLenTemp;
    }
    if(iHole){
        unsigned long long iTemp = (1 + iMax) * iMax / 2;
        return (int)(iTemp - iSum);
    }else{
        return iMax + 1;
    }
    
    return 0;
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
    struct sTest mTest[]={
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
