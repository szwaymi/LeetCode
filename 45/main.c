
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static struct{
    unsigned int iGoal;
    int *piSeries;
    int *piCaches;
}gmMeta;

int rSearch(unsigned int iLocation, unsigned int iStep){
    
    if(iLocation >= gmMeta.iGoal){
        if(iLocation == gmMeta.iGoal){
            return iStep;
        }
        return 0x10000000;
    }
    if(gmMeta.piCaches[iLocation] != -1){
        iStep += gmMeta.piCaches[iLocation];
        return iStep;
    }else{
        unsigned int iConSteps;
        int iMin = 0x10000000;
        for(iConSteps = gmMeta.piSeries[iLocation] ; iConSteps >= 1 ; iConSteps--){
            int iTemp = rSearch(iLocation + iConSteps, iStep + 1);
            if(iTemp < iMin){iMin = iTemp;}
        }
        gmMeta.piCaches[iLocation] = iMin - iStep;
        return iMin;
    }
}

int jump(int* piSeries, int iSize){
    int iResult;
    gmMeta.iGoal = iSize - 1;
    gmMeta.piSeries = piSeries;
    gmMeta.piCaches = (int *)malloc(sizeof(int) * iSize);
    for(unsigned int iCon = 0 ; iCon < iSize ; iCon++){
        gmMeta.piCaches[iCon] = -1;
    }
    iResult = rSearch(0, 0);
    free(gmMeta.piCaches);
    return iResult;
}
int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP
#define M_TEST_COLLECTION(N,S) {N, {sizeof(iSeries_##N) / sizeof(int), iSeries_##N}, {S}}
    //  Structure
    struct sInput{
        int iSize;
        int *piSeries;
    };
    struct sExp{
        int iSteps;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    //      [#1]
    M_TEST_INPUT(1, 2, 3, 1, 1, 4);
    //      [#2]
    M_TEST_INPUT(2, 2, 3, 0, 1, 4);
    //      [#69]
    M_TEST_INPUT(69, 5,9,3,2,1,0,2,3,3,1,0,0);
    //      [#74]
    M_TEST_INPUT(74, 5,6,4,4,6,9,4,4,7,4,4,8,2,6,8,1,5,9,6,5,2,7,9,7,9,6,9,4,1,6,8,8,4,4,2,0,3,8,5);
    //      [#83]
    M_TEST_INPUT(83, 8,2,4,4,4,9,5,2,5,8,8,0,8,6,9,1,1,6,3,5,1,2,6,6,0,4,8,6,0,3,2,8,7,6,5,1,7,0,3,4,8,3,5,9,0,4,0,1,0,5,9,2,0,7,0,2,1,0,8,2,5,1,2,3,9,7,4,7,0,0,1,8,5,6,7,5,1,9,9,3,5,0,7,5);
    //      [#105]
    M_TEST_INPUT(105, 9,8,2,2,0,2,2,0,4,1,5,7,9,6,6,0,6,5,0,5);
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, 2),
        M_TEST_COLLECTION(2, 2),
        M_TEST_COLLECTION(69, 3),
        M_TEST_COLLECTION(74, 5),
        M_TEST_COLLECTION(83, 13),
        M_TEST_COLLECTION(105, 3),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %d, ", mTest[iConTest].mExp.iSteps);
        //Result
        int iResult = jump(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iSize);
        printf("Result = %d, ", iResult);
        //Comparison
        int iTest = iResult == mTest[iConTest].mExp.iSteps;
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
