
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0


bool isInterleave(char * pcSrcA, char * pcSrcB, char * pcDes){

    char *pcSearch = pcSrcB;
    char *pcCheck = pcSrcA;
    char *pcTail = NULL;
    
    while(*pcDes){
        if(*pcDes != *pcCheck){
            char *pcHead = pcSearch;
            while(*pcDes != *pcSearch && *pcSearch != 0){
                pcSearch++;
            }
            if(*pcSearch == 0){
                return false;
            }
            if(pcTail == NULL){
                int iOffset = (int)(pcSearch - pcHead);
                pcDes -= (iOffset + 1);
                pcSearch = pcCheck - iOffset;
                pcCheck = pcHead - 1;
                
                /*
                
                char *pcTemp = pcCheck;
                pcCheck = pcSearch;
                pcSearch = pcTemp;
                */
                
            }else{
                int iOffset = (int)(pcSearch - pcHead);
                pcCheck = pcSearch;
                pcSearch = pcTail - iOffset;
                pcTail = NULL;
            }
        }
        pcCheck++;
        if(*pcCheck == 0){
            pcTail = pcCheck;
            pcCheck = pcSearch;
        }
        pcDes++;
    }
	return true;
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
        //M_TEST_COLLECTION(1024, true, "abc", "abcxyz", "abcxyzabc"),
        //M_TEST_COLLECTION(106, false, "abababababababababababababababababababababababababababababababababababababababababababababababababbb", "babababababababababababababababababababababababababababababababababababababababababababababababaaaba", "abababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababbb"),
        //M_TEST_COLLECTION(105, true, "aacaac", "aacaaeaac", "aacaacaaeaacaac"),
        //M_TEST_COLLECTION(104, true, "abababababababababababababababababababababababababababababababababababababababababababababababababbb", "abababababababababababababababababababababababababababababababababababababababababababababababababab", "abababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababbb"),
        //M_TEST_COLLECTION(100, false, "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa", "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab", "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab"),
        //M_TEST_COLLECTION(87, true, "aa", "ab", "aaba"),
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
