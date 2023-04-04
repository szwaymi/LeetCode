
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0


int rCheck(char * pcSrcA, char * pcSrcB, char * pcDes){
    
    if(*pcDes == 0){
        if(*pcSrcA == 0 && *pcSrcB == 0){
            return true;
        }else{
            return false;
        }
    }
    
    if(*pcDes != *pcSrcA && *pcDes != *pcSrcB){
        return false;
    }
    
    int iResult = 0;
    if(*pcDes == *pcSrcA){
        iResult += rCheck(pcSrcA + 1, pcSrcB, pcDes + 1);
    }
    if(*pcDes == *pcSrcB){
        iResult += rCheck(pcSrcA, pcSrcB + 1, pcDes + 1);
    }
    
    if(iResult){
        return true;
    }
    return false;
}

bool isInterleave(char * pcSrcA, char * pcSrcB, char * pcDes){

    return rCheck(pcSrcA, pcSrcB, pcDes);
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, T, SA, SB, D) {N, {SA, SB, D}, {T}}
    //  Structure
    struct sInput{
        char *pcSrcA;
        char *pcSrcB;
        char *pcDes;
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
        M_TEST_COLLECTION(105, true, "aacaac", "aacaaeaac", "aacaacaaeaacaac"),
        M_TEST_COLLECTION(100, false, "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa", "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab", "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab"),
        M_TEST_COLLECTION(87, true, "aa", "ab", "aaba"),
        M_TEST_COLLECTION(2, false, "aabcc", "dbbca", "aadbbbaccc"),
        M_TEST_COLLECTION(1, true, "aabcc", "dbbca", "aadbbcbcac"),
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
        isInterleave(mTest[iConTest].mInput.pcSrcA, mTest[iConTest].mInput.pcSrcB, mTest[iConTest].mInput.pcDes);
        if(fResult){printf("TRUE");}
        else{printf("FALSE");}
        //Comparison
        int iTest = fResult == mTest[iConTest].mExp.fResult;
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
