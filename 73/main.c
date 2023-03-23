
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void setZeroes(int** ppiMatrix, int iSize, int* piCols){
    
    unsigned int iConY;
    unsigned int iConX;
    
    //Column Checking
    //  Find Mark Row
    for(iConY = 0 ; iConY < iSize ; iConY++){
        for(iConX = 0 ; iConX < piCols[iConY] ; iConX++){
            if(ppiMatrix[iConY][iConX] == 0){
                break;
            }
        }
        if(iConX != piCols[iConY]){
            break;
        }
    }
    if(iConY == iSize){
        return;
    }
    unsigned int iLocY = iConY;
    //  Check each Column
    for(iConX = 0 ; iConX < piCols[0] ; iConX++){
        for(iConY = iLocY ; iConY < iSize ; iConY++){
            if(ppiMatrix[iConY][iConX] == 0){
                ppiMatrix[iLocY][iConX] = 0;
                break;
            }
        }
    }
    
    //Row Checking
    //  Find Mark Column
    for(iConX = 0 ; iConX < piCols[0] ; iConX++){
        if(ppiMatrix[iLocY][iConX] == 0){
            break;
        }
    }
    unsigned int iLocX = iConX;
    for(iConY = iLocY + 1 ; iConY < iSize ; iConY++){
        for(iConX = 0 ; iConX < piCols[0] ; iConX++){
            if(ppiMatrix[iConY][iConX] == 0){
                ppiMatrix[iConY][iLocX] = 0;
                break;
            }
        }
    }
    
    //Clearn
    //
    for(iConX = 0 ; iConX < piCols[0] ; iConX++){
        if(ppiMatrix[iLocY][iConX] == 0 && iConX != iLocX){
            for(iConY = 0 ; iConY < iSize ; iConY++){
                ppiMatrix[iConY][iConX] = 0;
            }
        }
    }
    //
    for(iConY = iLocY ; iConY < iSize ; iConY++){
        if(ppiMatrix[iConY][iLocX] == 0){
            for(iConX = 0 ; iConX < piCols[0] ; iConX++){
                ppiMatrix[iConY][iConX] = 0;
            }
        }
    }
    if(ppiMatrix[iLocY][iLocX] == 0){
        for(iConY = 0 ; iConY < iSize ; iConY++){
            ppiMatrix[iConY][iLocX] = 0;
        }
    }
    return;
}

int main(void){
    //Test Data
    //  Macro
    //
#define M_TEST_INPUT(N, C, ...) int iMatrix_##N[][C] = { __VA_ARGS__ };int *piMatrix_##N[sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0])];int iCols_##N[sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0]) ; iCon++){iCols_##N[iCon] = C;piMatrix_##N[iCon] = iMatrix_##N[iCon];}
#define M_TEST_EXP(N, ...) int iExp_##N[][sizeof(iMatrix_##N[0]) / sizeof(int)] = { __VA_ARGS__ };int *piExp_##N[sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0]) ; iCon++){piExp_##N[iCon] = iExp_##N[iCon];}
#define M_TEST_COLLECTION(N) {N, {piMatrix_##N, sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0]), iCols_##N}, {piExp_##N}}
    //  Structure
    struct sInput{
        int **ppiMatrix;
        int iSize;
        int *piCols;
    };
    struct sExp{
        int **ppiMatrix;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    //      #1
    M_TEST_INPUT(1, 3, {1, 1, 1}, {1, 0,1 }, {1, 1, 1});
    M_TEST_EXP(1, {1, 0, 1}, {0, 0, 0}, {1, 0, 1});
    //      #2
    M_TEST_INPUT(2, 4, {0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5});
    M_TEST_EXP(2, {0, 0, 0, 0}, {0, 4, 5, 0},{0, 3, 1, 0});
    //      #69
    M_TEST_INPUT(69, 4, {1,2,3,4},{5,0,7,8},{0,10,11,12},{13,14,15,0});
    M_TEST_EXP(69, {0,0,3,0},{0,0,0,0},{0,0,0,0},{0,0,0,0});
    struct sTest mTest[]={
        M_TEST_COLLECTION(1),
        M_TEST_COLLECTION(2),
        M_TEST_COLLECTION(69),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        unsigned int iConX;
        unsigned int iConY;
        printf("Test Case [%d]\n", mTest[iConTest].iNO);
        //Expectaion
        printf(" Expecation:\n");
        for(iConY = 0 ; iConY < mTest[iConTest].mInput.iSize ; iConY++){
            printf("  ");
            for(iConX = 0 ; iConX < mTest[iConTest].mInput.piCols[iConY] ; iConX++){
                printf("%d ", mTest[iConTest].mExp.ppiMatrix[iConY][iConX]);
            }
            printf("\n");
        }
        //Result
        printf(" Result:\n");
        setZeroes(mTest[iConTest].mInput.ppiMatrix, mTest[iConTest].mInput.iSize, mTest[iConTest].mInput.piCols);
        for(iConY = 0 ; iConY < mTest[iConTest].mInput.iSize ; iConY++){
            printf("  ");
            for(iConX = 0 ; iConX < mTest[iConTest].mInput.piCols[iConY] ; iConX++){
                printf("%d ", mTest[iConTest].mInput.ppiMatrix[iConY][iConX]);
            }
            printf("\n");
        }
        //Comparison
        int iTest = 1;
        for(iConY = 0 ; iConY < mTest[iConTest].mInput.iSize ; iConY++){
            for(iConX = 0 ; iConX < mTest[iConTest].mInput.piCols[iConY] ; iConX++){
                if(mTest[iConTest].mInput.ppiMatrix[iConY][iConX] != mTest[iConTest].mExp.ppiMatrix[iConY][iConX]){
                    iTest = 0;
                    break;
                }
            }
            if(iTest == 0){break;}
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
