
#include <stdlib.h>
#include <stdio.h>

int** threeSum(int* piSeries, int iSize, int* piResultRows, int** ppiResultColumns){
    printf("\n");
    struct sResult{
        int *piSeries;
        struct sResult *pmNext;
    };
    int iResultTemp[3];
    unsigned int iConX;
    unsigned int iConY;
    unsigned int iConZ;
    unsigned int iResults = 0;
    int iSum = 0;
    struct sResult *pmResults = NULL;
    for(iConX = 0 ; iConX < iSize - 2 ; iConX++){
        iSum = piSeries[iConX];
        for(iConY = iConX +1 ; iConY < iSize - 1 ; iConY++){
            iSum += piSeries[iConY];
            for(iConZ = iConY + 1 ; iConZ < iSize ; iConZ++){
                if(iSum + piSeries[iConZ] == 0){
                    
                    iResultTemp[0] = piSeries[iConX];
                    if(piSeries[iConY] < iResultTemp[0]){
                        iResultTemp[1] = iResultTemp[0];
                        iResultTemp[0] = piSeries[iConY];
                    }else{
                        iResultTemp[1] = piSeries[iConY];
                    }
                    if(piSeries[iConZ] < iResultTemp[0]){
                        iResultTemp[2] = iResultTemp[1];
                        iResultTemp[1] = iResultTemp[0];
                        iResultTemp[0] = piSeries[iConZ];
                    }else if(piSeries[iConZ] < iResultTemp[1]){
                        iResultTemp[2] = iResultTemp[1];
                        iResultTemp[1] = piSeries[iConZ];
                    }else{
                        iResultTemp[2] = piSeries[iConZ];
                    }
                    
                    struct sResult **ppmResult = &pmResults;
                    struct sResult *pmResult = NULL;
                    unsigned char iCached = 0;
                    while(*ppmResult){
                        pmResult = *ppmResult;
                        if(pmResult->piSeries[0] == iResultTemp[0]){
                            if(pmResult->piSeries[1] == iResultTemp[1]){
                                if(pmResult->piSeries[2] == iResultTemp[2]){
                                    iCached = 1;
                                    break;
                                }else if(iResultTemp[2] < pmResult->piSeries[2]){
                                    break;
                                }
                            }else if(iResultTemp[1] < pmResult->piSeries[1]){
                                break;
                            }
                        }else if(iResultTemp[0] < pmResult->piSeries[0]){
                            break;
                        }
                        ppmResult = &(*ppmResult)->pmNext;
                    }
                    if(iCached){
                        continue;
                    }else{
                        pmResult = (struct sResult *)malloc(sizeof(struct sResult));
                    }
                    pmResult->piSeries = (int *)malloc(sizeof(int) * 3);
                    pmResult->piSeries[0] = iResultTemp[0];
                    pmResult->piSeries[1] = iResultTemp[1];
                    pmResult->piSeries[2] = iResultTemp[2];
                    pmResult->pmNext = *ppmResult;
                    *ppmResult = pmResult;
                    iResults++;
                }
            }
            iSum -= piSeries[iConY];
        }
    }
    
    struct sResult *pmResult = pmResults;
    int **ppiResults = (int **)malloc(sizeof(int *) * iResults);
    int *piColumns = (int *)malloc(sizeof(int) * iResults);
    for(unsigned int iCon = 0 ; iCon < iResults ; iCon++){
        piColumns[iCon] = 3;
        ppiResults[iCon] = pmResult->piSeries;
        struct sResult *pmTemp = pmResult;
        pmResult = pmResult->pmNext;
        free(pmTemp);
    }
    *piResultRows = iResults;
    *ppiResultColumns = piColumns;
    return ppiResults;
}
int main(void){
    
    //[Test Data]
    //  Structures
    struct sInput{
        int *piInput;
        int iSize;
    };
    struct sExp{
        int **ppiExp;
        unsigned int iSize;
    };
    //  Macros
#define M_TEST_EXP(N, ...) int iExp_##N[][3] ={__VA_ARGS__};    \
    int *piExp_##N[sizeof(iExp_##N) / sizeof(iExp_##N[0])]; \
    for(unsigned char iCon = 0 ; iCon < sizeof(iExp_##N) / sizeof(iExp_##N[0]) ; iCon++){    \
    piExp_##N[iCon] = iExp_##N[iCon];   \
    }
#define M_TEST_INPUT(N,...) int iInput_##N[] = __VA_ARGS__
#define M_TEST_COLLECTION(N) {N, {piExp_##N, sizeof(piExp_##N) / sizeof(int *)}, {iInput_##N, sizeof(iInput_##N) / sizeof(int)}}
    //  Data
    M_TEST_INPUT(1, {-1, 0, 1, 2, -1, -4});
    M_TEST_EXP(1, {-1, -1, 2}, {-1, 0, 1});
    M_TEST_INPUT(68, {-2,0,1,1,2});
    M_TEST_EXP(68, {-2, 0, 2},{-2, 1, 1});
    M_TEST_INPUT(107, {3,0,-2,-1,1,2});
    M_TEST_EXP(107, {-2,-1,3},{-2,0,2},{-1,0,1});
    //  Constructure
    struct sTest{
        unsigned int iNO;
        struct sExp mExp;
        struct sInput mInput;
    };
    struct sTest mTest[]={
        //M_TEST_COLLECTION(1),
        //M_TEST_COLLECTION(68)
        M_TEST_COLLECTION(107)
    };
    
    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iCon;
    
    for(iCon = 0 ; iCon < iLength ; iCon++){
        printf("Test Case [%d], Expactation = ", iCon);
        unsigned int iConExp;
        for(iConExp = 0 ; iConExp < mTest[iCon].mExp.iSize ; iConExp++){
            printf("[%d, %d, %d] ", mTest[iCon].mExp.ppiExp[iConExp][0], mTest[iCon].mExp.ppiExp[iConExp][1], mTest[iCon].mExp.ppiExp[iConExp][2]);
        }
        
        int **ppiResults;
        int iResultSize;
        int *piResultColumns;
        ppiResults = threeSum(mTest[iCon].mInput.piInput, mTest[iCon].mInput.iSize, &iResultSize, &piResultColumns);

        unsigned int iConResult;
        unsigned int iTest = 1;
        printf("Result = ");
        for(iConResult = 0 ; iConResult < iResultSize ; iConResult++){
            printf("[");
            for(unsigned int iConLoc = 0 ; iConLoc < piResultColumns[iConResult] ; iConLoc++){
                printf("%d ", ppiResults[iConResult][iConLoc]);
            }
            printf("] ");
            if(piResultColumns[iConResult] != 3){
                iTest = 0;
            }
        }
        if(iTest){
            if(mTest[iCon].mExp.iSize !=  iResultSize){
                iTest = 0;
            }
        }
        if(iTest){
            for(iConExp = 0 ; iConExp < mTest[iCon].mExp.iSize ; iConExp++){
                for(iConResult = 0 ; iConResult < iResultSize ; iConResult++){
                    unsigned int iConLoc;
                    for(iConLoc = 0 ; iConLoc < 3 ; iConLoc++){
                        if(mTest[iCon].mExp.ppiExp[iConExp][iConLoc] != ppiResults[iConResult][iConLoc]){
                            break;
                        }
                    }
                    if(iConLoc == 3){
                        break;
                    }
                }
                if(iConResult == iResultSize){
                    iTest = 0;
                    break;
                }
            }
        }
        if(iTest){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        printf("\n");
    }
    
}
