
#include <stdio.h>

int** combinationSum(int* piCandidates, int iLength, int iTarget, int* piResults, int** ppiLength){
    
    unsigned int iNumber = (iTarget + piCandidates[0] - 1) / piCandidates[0];
    printf("%d", iNumber);
    
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
