
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

static int giTarget;

//L = 3, H = 1
//0 1 2
//S[2]
bool rSearch(int *piSeries, int iSize){
    if(iSize == 1){
        return *piSeries == giTarget;
    }
    if(iSize == 2){
        if(*piSeries == giTarget){return true;}
        if(piSeries[1] == giTarget){return true;}
        return false;
    }
    int iHalf = iSize / 2;
    int iValue = piSeries[iHalf];
    if(iValue == giTarget){
        return true;
    }else if(iValue < giTarget){
        return rSearch(&piSeries[iHalf + 1], iSize - iHalf - 1);
    }else{
        return rSearch(piSeries, iHalf);
    }
}
bool searchMatrix(int** ppiMatrix, int iRows, int* piCols, int iTarget){
    
    unsigned int iConY;
    for(iConY = 0 ; iConY < iRows ; iConY++){
        if(ppiMatrix[iConY][piCols[0] - 1] >= iTarget){
            break;
        }
    }
    if(iConY == iRows){
        return false;
    }
    
    giTarget = iTarget;
    return rSearch(ppiMatrix[iConY], piCols[0]);
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, C, ...) int iMatrix_##N[][C] = { __VA_ARGS__ };int *piMatrix_##N[sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0])];int iCols_##N[sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0]) ; iCon++){iCols_##N[iCon] = C;piMatrix_##N[iCon] = iMatrix_##N[iCon];}
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, T, E) {N, {piMatrix_##N, sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0]), iCols_##N, T}, E}
    //  Structure
    struct sInput{
        int **ppiMatrix;
        int iRows;
        int *piCols;
        int iTarget;
    };
    struct sExp{
        bool fExist;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    //      #1
    M_TEST_INPUT(1, 4, {1,3,5,7},{10,11,16,20},{23,30,34,60});
    //      #2
    M_TEST_INPUT(2, 4, {1,3,5,7},{10,11,16,20},{23,30,34,60});
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, 3, true),
        M_TEST_COLLECTION(2, 13, false),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        if(mTest[iConTest].mExp.fExist){
            printf("true");
        }else{
            printf("false");
        }
        printf(" ");
        //Result
        printf("Result = ");
        bool iResult =
        searchMatrix(mTest[iConTest].mInput.ppiMatrix, mTest[iConTest].mInput.iRows, mTest[iConTest].mInput.piCols, mTest[iConTest].mInput.iTarget);
        if(iResult){
            printf("true");
        }else{
            printf("false");
        }
        printf(" ");
        //Comparison
        int iTest = iResult == mTest[iConTest].mExp.fExist;
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
