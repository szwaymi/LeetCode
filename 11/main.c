
#include <stdio.h>

int maxArea(int* height, int heightSize){
    unsigned int iConLeft;
    int iMax = 0;
    int iLastHeight = 0;
    int iLastRight = heightSize - 1;
    for(iConLeft = 0 ; iConLeft < heightSize ; iConLeft++){
        unsigned int iConRight;
        if(height[iConLeft] > iLastHeight){
            for(iConRight = iConLeft + 1 ; iConRight < heightSize ; iConRight++){
                unsigned int iTemp;
                unsigned int iHeight;
                if(height[iConLeft] > height[iConRight]){iHeight = height[iConRight];}
                else{iHeight = height[iConLeft];}
                iTemp = iHeight * (iConRight - iConLeft);
                if(iTemp >= iMax){
                    iMax = iTemp;
                    //iLastRight = iConRight;
                }
            }
            iLastHeight = height[iConLeft];
        }
    }
    return iMax;
}
int main(int argc, const char * argv[]) {
    //[Test Data]
    //  Input
    //      Structure
    struct sInput{
        int *piHeight;
        int iSize;
    };
    //      Macro
#define M_TEST_INPUT(N, ...) int iHeight_##N[] = __VA_ARGS__
    //      Data
    M_TEST_INPUT(1, {1, 8, 6, 2, 5, 4, 8, 3, 7});
    //  Test
    //      Structure
    struct sTest{
        unsigned int iNO;
        unsigned int iExp;
        struct sInput mInput;
    };
    //      Macro
#define M_TEST_COLLECTION(N, E) {N, E, {iHeight_##N, sizeof(iHeight_##N) / sizeof(int)}}
    //      Data
    struct sTest mTest[] = {
        M_TEST_COLLECTION(1, 49)
    };
    
    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iCon;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        printf("Test Case [%d], Expactation = %d, ", mTest[iCon].iNO, mTest[iCon].iExp);
        int iResult = maxArea(mTest[iCon].mInput.piHeight, mTest[iCon].mInput.iSize);
        printf(" Result = %d ", iResult);
        unsigned char iTest = iResult == mTest[iCon].iExp;
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
    if(iCon == iLength){
        printf("[PASS]");
    }else{
        printf("[FAIL]");
    }
    printf("\n");

    return 0;
}

