
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int* spiralOrder(int** ppiMatrix, int iRows, int* piCols, int* piSize){
    
    unsigned int iLength = iRows * piCols[0];
    *piSize = iLength;
    
    int *piArray = (int *)malloc(sizeof(int) * iLength);
    
    int iLocX = 0;
    int iLocY = 0;
    
    int iShift[4][2] ={
        {1,0},{0,1},{-1,0},{0,-1}
    };
    int iBoundary[2][2];
    iBoundary[0][0] = 0;
    iBoundary[0][1] = piCols[0] - 1;
    iBoundary[1][0] = 0;
    iBoundary[1][1] = iRows - 1;
    unsigned char iDir = 0;
    unsigned int iCon;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        piArray[iCon] = ppiMatrix[iLocY][iLocX];
        iLocX += iShift[iDir][0];
        iLocY += iShift[iDir][1];
        if(iLocX < iBoundary[0][0]){
            iBoundary[1][1]--;
            iLocX++;
            iLocY--;
            iDir++;
        }
        if(iLocX > iBoundary[0][1]){
            iBoundary[1][0]++;
            iLocX--;
            iLocY++;
            iDir++;
        }
        if(iLocY < iBoundary[1][0]){
            iBoundary[0][0]++;
            iLocY++;
            iLocX++;
            iDir++;
        }
        if(iLocY > iBoundary[1][1]){
            iBoundary[0][1]--;
            iLocY--;
            iLocX--;
            iDir++;
        }
        iDir %= 4;
    }
    return piArray;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, R, C, ...) int iSeries_##N[R][C] = { __VA_ARGS__ };   \
    int *piSeries_##N[R];   \
    int iCols_##N[R];     \
    for(unsigned int iCon = 0 ; iCon < R ; iCon++){ \
        piSeries_##N[iCon] = iSeries_##N[iCon]; \
        iCols_##N[iCon] = C;   \
    }
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N) {N, {piSeries_##N, sizeof(piSeries_##N) / sizeof(int *), iCols_##N},{ iExp_##N, sizeof(iExp_##N) / sizeof(int)}}
    //  Structure
    struct sInput{
        int **ppiSeries;
        int iRows;
        int *piCols;
    };
    struct sExp{
        int *piSeries;
        int iLength;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    //      #1
    M_TEST_INPUT(1, 3, 3, {1,2,3}, {4,5,6}, {7,8,9});
    M_TEST_EXP(1, 1, 2, 3, 6, 9, 8, 7, 4, 5);
    //      #2
    M_TEST_INPUT(2, 3, 4, {1,2,3,4},{5,6,7,8},{9,10,11,12});
    M_TEST_EXP(2, 1,2,3,4,8,12,11,10,9,5,6,7);
    struct sTest mTest[]={
        //M_TEST_COLLECTION(1),
        M_TEST_COLLECTION(2),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        unsigned int iConExp;
        for(iConExp = 0 ; iConExp < mTest[iConTest].mExp.iLength ; iConExp++){
            printf("%d ", mTest[iConTest].mExp.piSeries[iConExp]);
        }
        printf(", ");
        //Result
        printf("Result = ");
        int iLength;
        int *piArray =
        spiralOrder(mTest[iConTest].mInput.ppiSeries, mTest[iConTest].mInput.iRows, mTest[iConTest].mInput.piCols, &iLength);
        unsigned int iConResult;
        for(iConResult = 0 ; iConResult < iLength ; iConResult++){
            printf("%d ", piArray[iConResult]);
        }
        //Comparison
        int iTest = 1;
        if(iLength == mTest[iConTest].mExp.iLength){
            for(iConResult = 0 ; iConResult < iLength ; iConResult++){
                if(mTest[iConTest].mExp.piSeries[iConResult] != piArray[iConResult]){
                    iTest = 0;
                    break;
                }
            }
        }else{
            iTest = 0;
        }
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
