
#include <stdio.h>

struct{
    int iLocation[2];
    int *piSeries;
    int iTarget;
}gmMeta;

void rSearch(unsigned int iLeft, unsigned int iRight){
    int iMiddle = (iLeft + iRight) / 2;
    
}

int* searchRange(int* piSeries, int iSize, int iTarget, int* piResults){
    gmMeta.iLocation[0] = 0;
    gmMeta.iLocation[1] = iSize - 1;
    gmMeta.piSeries = piSeries;
    gmMeta.iTarget = iTarget;
    rSearch(0, iSize - 1);
    return gmMeta.iLocation;
}
int main(void){
        
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N, T) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int), T}, {sizeof(iExp_##N) / sizeof(int), iExp_##N}}
    struct sInput{
        int *piSeries;
        int iLength;
        int iTarget;
    };
    struct sExp{
        int iSize;
        int *piLocation;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    M_TEST_INPUT(1, 5, 7, 7, 8, 8, 10);
    M_TEST_EXP(1, 3, 4);
    //M_TEST_INPUT(2, 4, 5, 6, 7, 0, 1, 2);
    //M_TEST_INPUT(3, 5, 1, 3);
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, 8),
        //M_TEST_COLLECTION(2, 3, -1),
        //M_TEST_COLLECTION(3, 1, 1),
    };
    
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        int iResultSize;
        int *piResult =
        searchRange(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength, mTest[iConTest].mInput.iTarget, &iResultSize);
        printf("[%d %d] [%d %d]\n", mTest[iConTest].mExp.piLocation[0], mTest[iConTest].mExp.piLocation[1], piResult[0], piResult[1]);
    }
    
    
}

