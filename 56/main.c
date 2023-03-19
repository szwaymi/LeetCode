
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void rTST_QuickSort(int **ppiIntervals, unsigned int iSize) {
    
    if(iSize == 1){return;}
    
    unsigned int iLeft;
    unsigned int iRight;
    iLeft = 0;
    iRight = iSize;

    do {
        do {
            iRight--;
        } while (ppiIntervals[0][0] <= ppiIntervals[iRight][0] && iLeft < iRight);
        do {
            iLeft++;
        } while (ppiIntervals[0][0] > ppiIntervals[iLeft][0] && iLeft < iRight);
        if (iLeft < iRight) {
            unsigned int iTemp;
            iTemp = ppiIntervals[iLeft][0];
            ppiIntervals[iLeft][0] = ppiIntervals[iRight][0];
            ppiIntervals[iRight][0] = iTemp;
            iTemp = ppiIntervals[iLeft][1];
            ppiIntervals[iLeft][1] = ppiIntervals[iRight][1];
            ppiIntervals[iRight][1] = iTemp;
        }
    } while (iLeft < iRight);

    unsigned int iTemp;
    iTemp = ppiIntervals[0][0];
    ppiIntervals[0][0] = ppiIntervals[iRight][0];
    ppiIntervals[iRight][0] = iTemp;
    iTemp = ppiIntervals[0][1];
    ppiIntervals[0][1] = ppiIntervals[iRight][1];
    ppiIntervals[iRight][1] = iTemp;

    if (iRight > 1) {
        rTST_QuickSort(&ppiIntervals[0], iRight);
    }
    if (iSize - iRight - 1 > 1) {
        rTST_QuickSort(&ppiIntervals[iRight + 1], iSize - iRight - 1);
    }
    return;
}

int** merge(int** ppiIntervals, int iLength, int* piCols, int* piLength, int** ppiCols){
    
    struct sResult{
        int iInterval[2];
        struct sResult *pmNext;
    };
    
    unsigned int iCon;
    struct sResult *pmResults = NULL;
    struct sResult **ppmResult = &pmResults;
    int iResults = 0;
    struct sResult *pmResult;
    
    rTST_QuickSort(ppiIntervals, iLength);
    
    iCon = 0;
    do{
        iResults++;
        pmResult = (struct sResult *)malloc(sizeof(struct sResult));
        *ppmResult = pmResult;
        ppmResult = &pmResult->pmNext;
        pmResult->iInterval[0] = ppiIntervals[iCon][0];
        pmResult->iInterval[1] = ppiIntervals[iCon][1];
        iCon++;
        while(iCon < iLength)
        {
            if(ppiIntervals[iCon][0] <= pmResult->iInterval[1] && ppiIntervals[iCon][0] >= pmResults->iInterval[0]){
                if(ppiIntervals[iCon][1] > pmResult->iInterval[1]){
                    pmResult->iInterval[1] = ppiIntervals[iCon][1];
                }
                if(ppiIntervals[iCon][0] < pmResult->iInterval[0]){
                    pmResult->iInterval[0] = ppiIntervals[iCon][0];
                }
                
                iCon++;
            }else{
                //printf("%d]", iInterval[1]);
                //pmResult->iInterval[0] = iInterval[0];
                //pmResult->iInterval[1] = iInterval[1];
                break;
            }
        }
    }while(iCon < iLength);
    if(ppiIntervals[iCon - 1][1] > pmResult->iInterval[1]){
        pmResult->iInterval[1] = ppiIntervals[iCon - 1][1];
    }
    pmResult->pmNext = NULL;
    
    int **ppiResults = (int **)malloc(sizeof(int *) * iResults);
    piCols = (int *)malloc(sizeof(int) * iResults);
    for(iCon = 0 ; iCon < iResults ; iCon++){
        piCols[iCon] = 2;
        ppiResults[iCon] = (int *)malloc(sizeof(int) * 2);
        pmResult = pmResults;
        ppiResults[iCon][0] = pmResult->iInterval[0];
        ppiResults[iCon][1] = pmResult->iInterval[1];
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
#define M_TEST_INPUT(N, ...) int iSeries_##N[][2] = { __VA_ARGS__ };int *piSeries_##N[sizeof(iSeries_##N) / sizeof(iSeries_##N[0])];int iCols_##N[sizeof(iSeries_##N) / sizeof(iSeries_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iSeries_##N) / sizeof(iSeries_##N[0]) ; iCon++){piSeries_##N[iCon]=iSeries_##N[iCon];iCols_##N[iCon]=2;}
#define M_TEST_EXP(N, ...) int iExp_##N[][2] = { __VA_ARGS__ };int iExpCols_##N[sizeof(iExp_##N)/sizeof(iExp_##N[0])];int *piExp_##N[sizeof(iExp_##N)/sizeof(iExp_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iExp_##N)/sizeof(iExp_##N[0]) ; iCon++){piExp_##N[iCon]=iExp_##N[iCon];iExpCols_##N[iCon]=2;}
#define M_TEST_COLLECTION(N) {N, {piSeries_##N, sizeof(iSeries_##N) / sizeof(iSeries_##N[0]), iCols_##N}, {piExp_##N, sizeof(iExp_##N) / sizeof(iExp_##N[0]), iExpCols_##N}}
    //  Structure
    struct sInput{
        int **piIntervals;
        int iLength;
        int *piCols;
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
    M_TEST_INPUT(1, {1,3},{2,6},{8,10},{15,18});
    M_TEST_EXP(1, {1,6},{8,10},{15,18});
    //      #11
    M_TEST_INPUT(11, {1,4},{0,4});
    M_TEST_EXP(11, {0,4});
    //      #18
    M_TEST_INPUT(18, {1,4},{0,1});
    M_TEST_EXP(18, {0,4});
    //      #53
    M_TEST_INPUT(53, {1,4},{0,0});
    M_TEST_EXP(53, {0,0},{1,4})
    struct sTest mTest[]={
        //M_TEST_COLLECTION(1),
        //M_TEST_COLLECTION(11),
        //M_TEST_COLLECTION(18),
        M_TEST_COLLECTION(53),
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
        merge(mTest[iConTest].mInput.piIntervals, mTest[iConTest].mInput.iLength, mTest[iConTest].mInput.piCols, &iLength, &piCols);
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
