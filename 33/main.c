
#include <stdio.h>

int search(int* piSeries, int iSize, int iTarget){
    struct sSet{
        unsigned int iLoc;
        unsigned int iValue;
    };
    struct sGroup{
        unsigned int iLo;
        unsigned int iHi;
    };
    struct sGroup mLeft;
    struct sGroup mRight;
    
    
    unsigned int iLeft = 0;
    unsigned int iRight = iSize - 1;
    unsigned int iMiddle;
    
    unsigned int iConDebug;
    do{
        printf("[%d %d]\n", iLeft, iRight);
        iMiddle = (iLeft + iRight) / 2;
        mLeft.iLo = piSeries[iLeft];
        mLeft.iHi = piSeries[iMiddle];
        if(mLeft.iHi >= mLeft.iLo){
            if(iTarget <= mLeft.iHi && iTarget >= mLeft.iLo){
                iRight = iMiddle;
            }
        }else{
            if(!(iTarget > mLeft.iHi && iTarget < mLeft.iLo)){
                iRight = iMiddle;
            }
        }
        if(iRight != iMiddle){
            mRight.iLo = piSeries[iMiddle + 1];
            mRight.iHi = piSeries[iRight];
            if(mRight.iHi >= mRight.iLo){
                if(iTarget <= mRight.iHi && iTarget >= mRight.iLo){
                    iLeft = iMiddle + 1;
                }
            }else{
                if(!(iTarget >= mRight.iHi && iTarget <= mRight.iLo)){
                    iLeft = iMiddle + 1;
                }
            }
        }
    }while((iLeft + iRight) / 2 != iMiddle);
    
    if(iLeft == iRight & iTarget == piSeries[iLeft]){return iLeft;}
    else{
        return -1;
    }
}

int main(void){
        
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N, T, E) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int), T}, {E}}
    struct sInput{
        int *piSeries;
        int iLength;
        int iTarget;
    };
    struct sExp{
        int iLocation;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    
    M_TEST_INPUT(1, 4, 5, 6, 7, 0, 1, 2);
    M_TEST_INPUT(2, 4, 5, 6, 7, 0, 1, 2);
    M_TEST_INPUT(3, 5, 1, 3);
    struct sTest mTest[]={
        //M_TEST_COLLECTION(1, 0, 4),
        //M_TEST_COLLECTION(2, 3, -1),
        M_TEST_COLLECTION(3, 1, 1),
    };
    
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        int iResult =
        search(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength, mTest[iConTest].mInput.iTarget);
        printf("%d %d\n", mTest[iConTest].mExp.iLocation, iResult);
        //search(iSeries, iSize, iTarget);
    }
    
    
}
