
#include <stdlib.h>
#include <stdio.h>

int** combinationSum(int* piCandidates, int iLength, int iTarget, int* piResults, int** ppiLength){
    
    unsigned int iNumber = iTarget / piCandidates[0];
    unsigned char *piAccs = (unsigned char *)malloc(sizeof(unsigned char) * (iNumber + 1));
    {
        unsigned int iCon;
        for(iCon = 0 ; iCon < iNumber + 1 ; iCon++){
            piAccs[iCon] = 0;
        }
    }
    unsigned int iConNumber;
    for(iConNumber = 0 ; iConNumber < iNumber ; iConNumber++){
        do{
            unsigned int iConCombine;
            int iSum = 0;
            for(iConCombine = 0 ; iConCombine < iConNumber ; iConCombine++){
                iSum += piCandidates[piAccs[iConNumber]];
                if(iSum > iTarget){
                    break;
                }
            }
            if(iSum == iTarget && iConCombine == iConNumber){
                unsigned int iConDbg;
                for(iConDbg = 0 ; iConDbg <= iConNumber ; iConDbg++){
                    printf("%d ", piCandidates[piAccs[iConDbg]]);
                }
                printf("\n");
                for(iConDbg = 0 ; iConDbg <= iNumber ; iConDbg++){
                    printf("%d ", piAccs[iConDbg]);
                }
                printf("\n");
            }
            piAccs[0]++;
            for(iConCombine = 0 ; iConCombine < iConNumber ; iConCombine++){
                if(piAccs[iConCombine] >= iLength){
                    piAccs[iConCombine] = 0;
                    piAccs[iConCombine + 1]++;
                }else{
                    unsigned int iConBit;
                    for(iConBit = 0 ; iConBit < iConCombine ; iConBit++){
                        piAccs[iConNumber - 2 -iConBit] = piAccs[iConCombine];
                    }
                    break;
                }
            }
        }while(piAccs[iConNumber] == 0);
    }
    
    
    return NULL;
}

int main(void){
#define M_TEST_INPUT(N, ...) int iCandiates_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N, T) {N, {T, iCandiates_##N, sizeof(iCandiates_##N) / sizeof(int)}}
    struct sInput{
        int iTarget;
        int *piCandiates;
        unsigned int iLength;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
    };
    M_TEST_INPUT(1, 2, 3, 6, 7);
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, 7),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        int iResults;
        int *piLengthes;
        int **ppiResults;
        ppiResults = combinationSum(mTest[iConTest].mInput.piCandiates, mTest[iConTest].mInput.iLength, mTest[iConTest].mInput.iTarget, &iResults, &piLengthes);
        
        printf("\n");
    }
    
}
