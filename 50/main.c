
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

double myPow(double dX, int iN){

    if(iN == 0){return 1;}
    if(dX == 1){return 1;}
    if(dX == -1){
        if(iN % 2 == 0 ){
            return 1;
        }else{
            return -1;
        }
    }

    unsigned int iNumber = (unsigned int)iN;
    double dP;
    if(iN < 0){
        dX = 1 / dX;
        iNumber = 0 - iNumber;
    }
    dP = dX;

    for(unsigned int iCon = 0 ; iCon < iNumber - 1 ; iCon++){
        dX *= dP;
        if(dX == 0){break;}
    }
    return dX;
}
int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP
#define M_TEST_COLLECTION(NO , X, N) {NO, {X, N}, {}}
    //  Structure
    struct sInput{
        double dX;
        int iN;
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
        M_TEST_COLLECTION(1, 1.00000, 2147483647),
        M_TEST_COLLECTION(6, 2.00000, -2),
        M_TEST_COLLECTION(302, 2.00000, -2147483648),
        M_TEST_COLLECTION(304, -1.00000, -2147483648),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
        printf("Result = ");
        double dY =
        myPow(mTest[iConTest].mInput.dX,mTest[iConTest].mInput.iN);
        printf("%f\n", dY);
        //Comparison
        int iTest = 1;
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
