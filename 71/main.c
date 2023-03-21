
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * simplifyPath(char * pcIn){
    
    char *pcResult = (char *)malloc(sizeof(char) * (strlen(pcIn) + 1));
    char *pcOut = pcResult;
    while(*pcIn){
        if(*pcIn == '.'){
            pcIn++;
            if(*pcIn == '.'){
                if(pcOut > pcResult + 1){
                    pcOut -= 2;
                    while(*pcOut != '/'){
                        pcOut--;
                    }
                    pcOut++;
                }
            }
            pcIn+=2;
        }else{
            *pcOut = *pcIn;
            pcOut++;
            pcIn++;
        }
    }
    *pcOut = 0;
    
    return pcResult;
}
int main(void){
    
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, S, E) {N, {S}, {E}}
    //  Structure
    struct sInput{
        char *pcPath;
    };
    struct sExp{
        char *pcPath;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    struct sTest mTest[]={
        M_TEST_COLLECTION(1, "/home/", "/home"),
        M_TEST_COLLECTION(2, "/../", "/"),
        M_TEST_COLLECTION(3, "/home//foo/", "/home/foo/"),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %s, ",mTest[iConTest].mExp.pcPath);
        //Result
        char *pcResult =
            simplifyPath(mTest[iConTest].mInput.pcPath);
        printf("Result = %s ", pcResult);
        //Comparison
        int iTest = strcmp(pcResult, mTest[iConTest].mExp.pcPath);
        if(iTest == 0){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        printf("\n");
        if(iTest){
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
