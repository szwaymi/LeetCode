
#include <stdio.h>
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
int threeSumClosest(int* piSeries, int iSize, int iTarget){
    rSort(piSeries, iSize);
    unsigned int iConX;
    unsigned int iConY;
    unsigned int iConZ;
    unsigned int iDifference = 0xFFFFFFFF;
    int iSum;
    for(iConX = 0 ; iConX < iSize - 2 ; iConX++){
        for(iConY = iConX + 1 ; iConY < iSize - 1 ; iConY++){
            for(iConZ = iConY + 1 ; iConZ < iSize ; iConZ++){
                int iSumTemp = piSeries[iConX] + piSeries[iConY] + piSeries[iConZ];
                int iDiffTemp = iSumTemp - iTarget;
                if(iDiffTemp < 0){iDiffTemp *= -1;}
                if(iDiffTemp < iDifference){
                    iDifference = iDiffTemp;
                    iSum = iSumTemp;
                }
            }
        }
    }
    
    return iSum;
}

int main(void) {

    //Test Data
    //  Macros
#define M_TEST_DATA_IN(N, ...) int iSeries_##N[]={ __VA_ARGS__};
#define M_TEST_COLLECTION(N, E, T) {N, E, {T, iSeries_##N, sizeof(iSeries_##N) / sizeof(int)}}
    //  Structures
    struct sInput {
        int iTarget;
		int *piSeries;
		unsigned int iSize;
	};
	struct sTest {
		unsigned int iNO;
		int iOutput;
		struct sInput mInput;
	};
    //  Data
    M_TEST_DATA_IN(0, -1, 2, 1, -4);
    //  Collection
    struct sTest mTest[]={
        M_TEST_COLLECTION(0, 2, 1),
    };

    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLength ; iConTest++){
        printf("Test Case [%d], Exp = %d, ", mTest[iConTest].iNO, mTest[iConTest].iOutput);
        int iResult =
        threeSumClosest(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iSize, mTest[iConTest].mInput.iTarget);
        printf("Result = %d ", iResult);
        unsigned int iTest = iResult == mTest[iConTest].iOutput;
        if(iTest){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        printf("\n");
    }
    
}
