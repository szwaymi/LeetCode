
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

bool isNumber(char * pcNumber){
    unsigned char iState = 0;

    while(*pcNumber){
        switch(iState){
        case 0:
            if(*pcNumber == ' '){
                pcNumber++;
            }else if(*pcNumber == '+' || *pcNumber == '-'){
                pcNumber++;
                iState = 1;
            }else if(*pcNumber >= '0' && *pcNumber <= '9'){
                iState = 1;
            }else if(*pcNumber == '.'){
                pcNumber++;
                iState = 2;
            }else{
                return false;
            }
            break;
        case 1:
            if(*pcNumber >= '0' && *pcNumber <= '9'){
                pcNumber++;
            }else if(*pcNumber == '.'){
                pcNumber++;
                iState = 2;
            }else if(*pcNumber == 'e' || *pcNumber == 'E'){
                pcNumber++;
                iState = 5;
            }else{
                return false;
            }
            break;
        case 2:
        case 3:
            if(*pcNumber >= '0' && *pcNumber <= '9'){
                iState = 3;
                pcNumber++;
            }else if(*pcNumber == 'e' || *pcNumber == 'E'){
                pcNumber++;
                iState = 5;
            }else{
                return false;
            }
            break;
        case 5:
        case 6:
            if(*pcNumber >= '0' && *pcNumber <= '9'){
                pcNumber++;
                iState = 6;
            }else{
                return false;
            }
            break;
        }
    }
    switch(iState){
    case 2:return false;
    case 5:return false;
    }
    return true;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, S, R) {N, {S}, {R}}
    //  Structure
    struct sInput{
        char *pcNumber;
    };
    struct sExp{
        bool fResult;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, "0", true),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        if(mTest[iConTest].mExp.fResult){printf("TRUE");}
        else{printf("FALSE");}
        printf(" ");
        //Result
        printf("Result = ");
        bool fResult =
        isNumber(mTest[iConTest].mInput.pcNumber);
        if(fResult){printf("TRUE");}
        else{printf("FALSE");}
        printf(" ");
        //Comparison
        int iTest = mTest[iConTest].mExp.fResult == fResult;
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

