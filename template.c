
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
