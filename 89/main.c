
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void rProduce(int *piSeries, unsigned int iNumber){
    if(iNumber == 1){
        piSeries[0] = 0;
        piSeries[1] = 1;
        return;
    }
    unsigned int iHalf = iNumber / 2;
    rProduce(piSeries, iHalf);
    unsigned int iCon;
    for(iCon = 0 ; iCon < iHalf ; iCon++){
        
    }
    
}

int* grayCode(int iNumber, int* *piLength){
    unsigned int iLength = 1 << iNumber;
    int *piSeries = (int *)malloc(sizeof(int) * iLength);
    
    rProduce(piSeries, iNumber);
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP
#define M_TEST_COLLECTION
    //  Structure
    struct sInput{
    };
    struct sExp{
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    struct sTest mTest[]={
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
        printf("Result = ");
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
