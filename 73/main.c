
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void setZeroes(int** ppiMatrix, int iSize, int* piCols){

 
}

int main(void){
    //Test Data
    //  Macro
    //
#define M_TEST_INPUT(N, C, ...) int iMatrix_##N[][C] = { __VA_ARGS__ };int *piMatrix_##N[sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0])];int iCols_##N[sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0]) ; iCon++){iCols_##N[iCon] = C;piMatrix_##N[iCon] = iMatrix_##N[iCon];}
//#define M_TEST_EXP(N, ...) int iExp_##N[][sizeof(iMatrix_##N[0]) / sizeof(int)] = { __VA_ARGS__ };
#define M_TEST_COLLECTION(N) {N, {piMatrix_##N, sizeof(iMatrix_##N) / sizeof(iMatrix_##N[0]), iCols_##N}, {}}
    //  Structure
    struct sInput{
        int **ppiMatrix;
        int iSize;
        int *piCols;
    };
    struct sExp{
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    M_TEST_INPUT(1, 3, {1, 1, 1},{1, 0,1 },{1, 1, 1});
    struct sTest mTest[]={
        M_TEST_COLLECTION(1),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
        printf("Result = ");
        setZeroes(mTest[iConTest].mInput.ppiMatrix, mTest[iConTest].mInput.iSize, mTest[iConTest].mInput.piCols);
        //Comparison
        int iTest;
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
