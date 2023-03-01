
#include <stdlib.h>
#include <stdio.h>

void rPrintS(int *piSeries, unsigned int iSize){
    unsigned int iCon;
    for(iCon = 0 ; iCon < iSize ; iCon++){
        printf("%d ", piSeries[iCon]);
    }
    printf("\n");
}
void rPrint(int *piSeries, unsigned int iSize) {
	unsigned int iCon;
	for (iCon = 0; iCon < iSize; iCon++) {
		printf("%d ", piSeries[iCon]);
	}
	printf("\n");
}

void rSort(int *piSeries, unsigned int iSize){
    
    int *piL = piSeries;
    int *piR = piSeries + iSize;
    
	do {
        do{
            piR--;
		} while (*piSeries <= *piR  && piR > piL);

        do{
            piL++;
		} while (*piSeries > *piL && piL < piR);
        if(piL < piR){
            int iTemp = *piR;
            *piR = *piL;
            *piL = iTemp;
        }
	}while (piL < piR);
	
	int iTemp = *piSeries;
	*piSeries = *piR;
	*piR = iTemp;

	unsigned int iSizeTemp;
	iSizeTemp = (unsigned int)(piR - piSeries);
	if (iSizeTemp > 1) {
		rSort(piSeries, iSizeTemp);
	}
	iSizeTemp = iSize -  (unsigned int)(piR - piSeries) - 1;
	if (iSizeTemp > 1) {
		rSort(piR + 1, iSizeTemp);
	}
}
int** threeSum(int* piSeries, int iSize, int* piResultRows, int** ppiResultColumns){
    rSort(piSeries, iSize);
    rPrint(piSeries, iSize);
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
    int iRequire;
    struct sResult *pmResults = NULL;
    for(iConX = 0 ; iConX < iSize - 2 ; iConX++){
        if(iConX > 0 && piSeries[iConX - 1] == piSeries[iConX]){
            continue;
        }
        for(iConY = iConX + 1 ; iConY < iSize - 1 ; iConY++){
            if(iConY > iConX + 1 && piSeries[iConY - 1] == piSeries[iConY]){
                continue;
            }
            iRequire = 0 - piSeries[iConX] - piSeries[iConY];
            unsigned int iLeft = iConY + 1;
            unsigned int iRight = iSize - 1;
            int iMiddle;
            while(iRight >= iLeft){
                iMiddle = (iRight + iLeft) / 2;
                if(piSeries[iMiddle] == iRequire){
                    break;
                }else if(piSeries[iMiddle] < iRequire){
                    iLeft = iMiddle + 1;
                }else{
                    iRight = iMiddle - 1;
                }
                iMiddle = -1;
            }
            if(iMiddle != -1){
                struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
                pmResult->piSeries = (int *)malloc(sizeof(int) * 3);
                pmResult->piSeries[0] = piSeries[iConX];
                pmResult->piSeries[1] = piSeries[iConY];
                pmResult->piSeries[2] = piSeries[iMiddle];
                pmResult->pmNext = pmResults;
                pmResults = pmResult;
                iResults++;
            }
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
    M_TEST_INPUT(137, {-1,0,1,2,-1,-4,-2,-3,3,0,4});
    M_TEST_EXP(137, {-4,0,4},{-4,1,3},{-3,-1,4},{-3,0,3},{-3,1,2},{-2,-1,3},{-2,0,2},{-1,-1,2},{-1,0,1});
    //  Constructure
    struct sTest{
        unsigned int iNO;
        struct sExp mExp;
        struct sInput mInput;
    };
    struct sTest mTest[]={
        //M_TEST_COLLECTION(1),
        //M_TEST_COLLECTION(68)
        //M_TEST_COLLECTION(107)
        //M_TEST_COLLECTION((137),
        M_TEST_COLLECTION(137)
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
