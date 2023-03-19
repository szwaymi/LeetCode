
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int** insert(int** ppIntervals, int iLength, int* piCols, int* piNew, int iLenNew, int *piLength, int** ppiCols){

    struct sResult{
        int *piInterval;
        struct sResult *pmNext;
    };
    struct sResult *pmResults;
    struct sResult **ppmResult;
    struct sResult *pmResult = NULL;
    ppmResult = &pmResults;
    
    int iResults = 0;
    
    unsigned int iCon = 0;
    while(iCon < iLength){
        pmResult = (struct sResult *)malloc(sizeof(struct sResult));
        *ppmResult = pmResult;
        ppmResult = &pmResult->pmNext;
        pmResult->piInterval = ppIntervals[iCon];
        iResults++;
        if(piNew[0] <= pmResult->piInterval[1] && piNew[0] >= pmResult->piInterval[0]){
            if(pmResult->piInterval[1] < piNew[1]){
                pmResult->piInterval[1] = piNew[1];
            }
            if(iCon + 1 < iLength){
                if(ppIntervals[iCon+1][0] < pmResult->piInterval[1]){
                    pmResult->piInterval[1] = ppIntervals[iCon+1][1];
                    iCon++;
                }
            }
        }
        iCon++;
    }
    if(pmResult){
        pmResult->pmNext = NULL;
    }
    
    int **ppiResults = (int **)malloc(sizeof(int *) * iResults);
    piCols = (int *)malloc(sizeof(int) * iResults);
    for(iCon = 0 ; iCon < iResults ; iCon++){
        piCols[iCon] = 2;
        pmResult = pmResults;
        ppiResults[iCon] = (int *)malloc(sizeof(int) * 2);
        ppiResults[iCon][0] = pmResult->piInterval[0];
        ppiResults[iCon][1] = pmResult->piInterval[1];
        pmResults = pmResults->pmNext;
        free(pmResult);
    }
    
    *piLength = iResults;
    *ppiCols = piCols;
    
    return ppiResults;
}


int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, S, E, ...) int iNew_##N[2]={S,E};int iSeries_##N[][2] = { __VA_ARGS__ };int *piSeries_##N[sizeof(iSeries_##N) / sizeof(iSeries_##N[0])];int iCols_##N[sizeof(iSeries_##N) / sizeof(iSeries_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iSeries_##N) / sizeof(iSeries_##N[0]) ; iCon++){piSeries_##N[iCon]=iSeries_##N[iCon];iCols_##N[iCon]=2;}
#define M_TEST_EXP(N, ...) int iExp_##N[][2] = { __VA_ARGS__ };int iExpCols_##N[sizeof(iExp_##N)/sizeof(iExp_##N[0])];int *piExp_##N[sizeof(iExp_##N)/sizeof(iExp_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iExp_##N)/sizeof(iExp_##N[0]) ; iCon++){piExp_##N[iCon]=iExp_##N[iCon];iExpCols_##N[iCon]=2;}
#define M_TEST_COLLECTION(N) {N, {piSeries_##N, sizeof(iSeries_##N) / sizeof(iSeries_##N[0]), iCols_##N,  iNew_##N}, {piExp_##N, sizeof(iExp_##N) / sizeof(iExp_##N[0]), iExpCols_##N}}
    //  Structure
    struct sInput{
        int **piIntervals;
        int iLength;
        int *piCols;
        int *piNew;
    };
    struct sExp{
        int **piIntervals;
        int iLength;
        int *piCols;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    //      #1
    M_TEST_INPUT(1, 2, 5, {1, 3},{6, 9});
    M_TEST_EXP(1, {1, 5}, {6, 9});
    //      #2
    M_TEST_INPUT(2, 4, 8, {1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16});
    M_TEST_EXP(2, {1, 2}, {3, 10}, {12, 16});
    struct sTest mTest[]={
        M_TEST_COLLECTION(1),
        M_TEST_COLLECTION(2),
        //M_TEST_COLLECTION(18),
        //M_TEST_COLLECTION(53),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        unsigned int iCon;
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        for(iCon = 0 ; iCon < mTest[iConTest].mExp.iLength ; iCon++){
            unsigned int iConSeries;
            printf("[");
            for(iConSeries = 0 ; iConSeries < mTest[iConTest].mExp.piCols[iCon] ; iConSeries++){
                printf("%d ", mTest[iConTest].mExp.piIntervals[iCon][iConSeries]);
            }
            printf("]");
        }
        printf(",");
        //Result
        printf("Result = ");
        int **ppiIntervals;
        int iLength;
        int *piCols;
        ppiIntervals =
        insert(mTest[iConTest].mInput.piIntervals, mTest[iConTest].mInput.iLength, mTest[iConTest].mInput.piCols, mTest[iConTest].mInput.piNew, 2, &iLength, &piCols);
        for(iCon = 0 ; iCon < iLength ; iCon++){
            unsigned int iConSeries;
            printf("[");
            for(iConSeries = 0 ; iConSeries < piCols[iCon] ; iConSeries++){
                printf("%d ", ppiIntervals[iCon][iConSeries]);
            }
            printf("]");
        }
        //Comparison
        int iTest = 1;
        if(mTest[iConTest].mExp.iLength != iLength){
            iTest = 0;
        }else{
            for(iCon = 0 ; iCon < mTest[iConTest].mExp.iLength ; iCon++){
                if(mTest[iConTest].mExp.piCols[iCon]!=piCols[iCon]){
                    break;
                }
                if(mTest[iConTest].mExp.piIntervals[iCon][0] != ppiIntervals[iCon][0]){
                    break;
                }
                if(mTest[iConTest].mExp.piIntervals[iCon][1] != ppiIntervals[iCon][1]){
                    break;
                }
            }
            if(iCon != mTest[iConTest].mExp.iLength){
                iTest = 0;
            }
        }
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
