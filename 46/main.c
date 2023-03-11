
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct sResult{
    int *piSeries;
    struct sResult *pmNext;
};

static struct{
    int iResults;
    int *piSeries;
    int iSize;
    unsigned char *piPer;
    unsigned int iMask;
    struct sResult *pmResults;
}gmMeta;

void rProduce(unsigned int iLevel)
{
    if(iLevel == gmMeta.iSize){
        struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
        pmResult->pmNext = gmMeta.pmResults;
        gmMeta.pmResults = pmResult;
        pmResult->piSeries = (int *)malloc(sizeof(int) * gmMeta.iSize);
        unsigned int iConPer;
        for(iConPer = 0 ; iConPer < gmMeta.iSize ; iConPer++){
            pmResult->piSeries[iConPer] = gmMeta.piSeries[gmMeta.piPer[iConPer]];
        }
        gmMeta.iResults++;
        return;
    }
    unsigned int iConUnit = iLevel;
    unsigned int iCon;
    for(iCon = 0 ; iCon < gmMeta.iSize - iLevel ; iCon++){
        unsigned int iMask = 1 << iConUnit;
        while(((gmMeta.iMask & iMask) ^ iMask) == 0){
            iConUnit++;
            iConUnit %= gmMeta.iSize;
            iMask = 1<< iConUnit;
        }
        gmMeta.iMask |= iMask;
        gmMeta.piPer[iLevel] = iConUnit;
        rProduce(iLevel + 1);
        gmMeta.iMask &= (~iMask);
        iConUnit++;
        iConUnit %= gmMeta.iSize;
    }
}

int** permute(int* piSeries, int iSize, int* piResults, int** ppiCols){
    gmMeta.piSeries = piSeries;
    gmMeta.iSize = iSize;
    gmMeta.piPer = (unsigned char *)malloc(sizeof(unsigned char) * iSize);
    gmMeta.iMask = 0;
    gmMeta.iResults = 0;
    gmMeta.pmResults = NULL;
    rProduce(0);
    
    int **ppiResults = (int **)malloc(sizeof(int *) * gmMeta.iResults);
    int *piCols = (int *)malloc(sizeof(int) * gmMeta.iResults);
    
    unsigned int iConPer;
    for(iConPer = 0 ; iConPer < gmMeta.iResults ; iConPer++){
        struct sResult *pmResult = gmMeta.pmResults;
        ppiResults[iConPer] = pmResult->piSeries;
        piCols[iConPer] = iSize;
        gmMeta.pmResults = pmResult->pmNext;
        free(pmResult);
    }
    
    *piResults = gmMeta.iResults;
    *ppiCols = piCols;
    return ppiResults;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP(N, ...) int iExp_##N[][sizeof(iSeries_##N) / sizeof(int)] = { __VA_ARGS__ };int *piExp_##N[sizeof(iExp_##N)/sizeof(iExp_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iExp_##N) / sizeof(iExp_##N[0]) ; iCon++){piExp_##N[iCon] = iExp_##N[iCon];}
#define M_TEST_COLLECTION(N) {N, {sizeof(iSeries_##N) / sizeof(int), iSeries_##N}, {sizeof(iExp_##N)/sizeof(iExp_##N[0]), piExp_##N}}
    //  Structure
    struct sInput{
        unsigned int iSize;
        int *piSeries;
    };
    struct sExp{
        unsigned int iNumber;
        int **ppiResults;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    M_TEST_INPUT(1, 1, 2, 3);
    M_TEST_EXP(1, {1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1});
    M_TEST_INPUT(1024, 1, 2, 3, 4, 5, 6);
    M_TEST_EXP(1024, {1, 2, 3, 4, 5, 6});
    struct sTest mTest[]={
        M_TEST_COLLECTION(1)
        //M_TEST_COLLECTION(1024),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        unsigned int iConExp;
        for(iConExp = 0 ; iConExp < mTest[iConTest].mExp.iNumber ; iConExp++){
            printf("[");
            unsigned int iConSeries;
            for(iConSeries = 0 ; iConSeries < mTest[iConTest].mInput.iSize ; iConSeries++){
                printf("%d ", mTest[iConTest].mExp.ppiResults[iConExp][iConSeries]);
            }
            printf("]");
        }
        //Result
        printf("Result = ");
        int *piCols;
        int iResults;
        int **ppiResults =
        permute(mTest[iConTest].mInput.piSeries,mTest[iConTest].mInput.iSize, &iResults,&piCols);
        unsigned int iConResults;
        for(iConResults = 0 ; iConResults < iResults ; iConResults++){
            printf("[");
            unsigned int iConSeries;
            for(iConSeries = 0 ; iConSeries < piCols[iConResults] ; iConSeries++){
                printf("%d ", ppiResults[iConResults][iConSeries]);
            }
            printf("]");
        }
        
        //Comparison
        int iTest;
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
