
#include <stdio.h>

#define M_TEST_EXAM threeSumClosest
#define M_TEST_VERIFY rVRF_threeSumCloset

int rVRF_threeSumClosest(int* piSeries, int iSize, int iTarget){
    int iSum;
    unsigned int iConX;
    unsigned int iConY;
    unsigned int iConZ;
    unsigned int iDifference = 0xFFFFFFFF;
    for(iConX = 0 ; iConX < iSize - 2 ; iConX++){
        for(iConY = iConX + 1 ; iConY < iSize - 1 ; iConY++){
            for(iConZ = iConY + 1 ; iConZ < iSize ; iConZ++){
                int iSumTemp = piSeries[iConX] + piSeries[iConY] + piSeries[iConZ];
                int iDiffTemp = iTarget - iSumTemp;
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
    unsigned int iDifference = 0xFFFFFFFF;
    int iSum = 0;
    for(iConX = 0 ; iConX < iSize - 2 ; iConX++){
        if(iConX && piSeries[iConX] == piSeries[iConX - 1]){
            continue;
        }
        for(iConY = iConX + 1 ; iConY < iSize - 1 ; iConY++){
            if(iConY >= iConX + 2 && piSeries[iConY] == piSeries[iConY - 1]){
                continue;
            }
            if(piSeries[iConX] == -1 && piSeries[iConY] == 1){
                printf("FF");
            }
            int iSumTemp = piSeries[iConX] + piSeries[iConY];
            int iRequire = iTarget - iSumTemp;
            unsigned int iLeft = iConY + 1;
            unsigned int iRight = iSize - 1;
            int iMiddle = -1;
            while (iRight >= iLeft) {
                iMiddle = (iRight + iLeft) / 2;
                if (piSeries[iMiddle] == iRequire) {
                    break;
                }
                else if (piSeries[iMiddle] < iRequire) {
                    iLeft = iMiddle + 1;
                }
                else {
                    iRight = iMiddle - 1;
                }
            }
            if(iMiddle != -1){
                int iDiffTemp[2];
                iDiffTemp[0] = iRequire - piSeries[iMiddle];
                if(iMiddle + 1 < iSize && piSeries[iMiddle] < iRequire){
                    iDiffTemp[1] = iRequire - piSeries[iMiddle + 1];
                    if(iDiffTemp[1] * iDiffTemp[1] < iDiffTemp[0] * iDiffTemp[0]){
                        iDiffTemp[0] = iDiffTemp[1];
                        iMiddle++;
                    }
                    
                }else if(iMiddle - 1 >= iConY + 1 && piSeries[iMiddle] > iRequire){
                    iDiffTemp[1] = iRequire - piSeries[iMiddle - 1];
                    if(iDiffTemp[1] * iDiffTemp[1] < iDiffTemp[0] * iDiffTemp[0]){
                        iDiffTemp[0] = iDiffTemp[1];
                        iMiddle--;
                    }
                }
                if(iDiffTemp[0] < 0){iDiffTemp[0] *= -1;}
                if((unsigned int)iDiffTemp[0] < iDifference){
                    iDifference = iDiffTemp[0];
                    iSum = iSumTemp + piSeries[iMiddle];
                }
            }
        }
    }
    
    return iSum;
}

int main(void) {

    //Test Data
    //  Macros
#define M_TEST_DATA_IN(N, ...) int iSeries_##N[]={ __VA_ARGS__}
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
    M_TEST_DATA_IN(1, 1, 1, 1, 1);
    M_TEST_DATA_IN(2, 1, 1, 1, 0);
    M_TEST_DATA_IN(3, 88,609,-765,-709,191,-963,412,-231,652,-236,-692,-874,322,-993,-202,-89,-133,764,-241,-224,-906,-775,-667,433,726,4,-208,-595,814,-561,103,-827,-948,-476,0,-14,974,-475,488,397,-456,87,225,6,-804,242,503,55,90,487,-630,335,403,-499,396,229,-160,858,-702,-226,-615,3,882,518,28,-676,990,-252,-142,-382,-663,-47,-71,-567,-728,761,59,-945,653,572,353,-200,172,595,-325,-987,-858,114,-506,190,-107,-388,698,-219,12,-510,-374,-181,-161,-35,-890,-330,193,-110,-817,495,-803,-323,-935,-136,730,-860,-767,416,-256,798,179,682,-196,10,-515,76,909,-301,-530,945,248,-570,597,-869,-85,-665,-884,-887,900,45,-659,-138,519,565,-623,-60,995,-194,157,958,173,536,-91,380,306,690,-534,77,571,902,-316,40,-617,-899,-29,-318,-267,-539,443,375,-843,249,563,-757,473,117,331,342,979,-129,-503,-326,694,975,732,98,-59,-115,-212,-286,-223,-33,-652,-405,169,957,-375,-238,745,-816,901,-926,559,719,-1,-419,511,-684,-524,369,-17,377,96,914,819,665,392,465,-750,676,152,298,-265,851,596,219,785,-622,-794,-225,-559,-468,-610,637,-439,-516,-189,505,-335,543,769,-989,700,-641,387,406,-6,-602,922,710,-351,-90,394,-75,754,444,-309,-124,-755,697,-491,336,319,-769,-533,-313,9,196,606,72,-607,-84,362,-337,-766,-637,643,772,-54,746,560,66,-140,-722,-790,-172,-940,-729,-449,-36,231,549,793,735,490,-986,702,339,-44,-780,314,101,348,982,577,238,285,567,-41,268,540,37,269,413,-511,-520);
    M_TEST_DATA_IN(4,  -1, 2, 1, -4);
    //  Collection
    struct sTest mTest[]={
        M_TEST_COLLECTION(0,    2,    1),
        M_TEST_COLLECTION(1,    3,    0),
        M_TEST_COLLECTION(2,    3,  100),
        M_TEST_COLLECTION(3, 1096, 1096),
        M_TEST_COLLECTION(4,    2,    1),
    };

    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLength ; iConTest++){
        printf("Test Case [%d], Exp = %d, ", mTest[iConTest].iNO, mTest[iConTest].iOutput);
        int iResult =
        M_TEST_EXAM(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iSize, mTest[iConTest].mInput.iTarget);
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
