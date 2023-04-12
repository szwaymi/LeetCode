
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0


bool isInterleave(char * pcSrcA, char * pcSrcB, char * pcDes){

    char *pcSrcC = "";
    struct sSegment{
        char *pcHead;
        char *pcTail;
    };
    struct sSegment mSegment[3] = {
        {pcSrcC, pcSrcC},
        {pcSrcB, pcSrcB},
        {pcSrcA, pcSrcA}
    };
    unsigned int iLast = 2;
    unsigned int iNow = 2;
    unsigned int iNext = 1;
    
    while(*pcDes){
        if(*pcDes != *mSegment[iNow].pcTail){
            while(*pcDes != *mSegment[iNext].pcTail && *mSegment[iNext].pcTail){
                mSegment[iNext].pcTail++;
            }
            if(*mSegment[iNext].pcTail == 0){
                iNext = (iNext + 1) % 2;
                while(*pcDes != *mSegment[iNext].pcTail && *mSegment[iNext].pcTail){
                    mSegment[iNext].pcTail++;
                }
                if(*mSegment[iNext].pcTail == 0){
                    return false;
                }
            }
            int iOffset = (int)(mSegment[iNext].pcTail - mSegment[iNext].pcHead);
            mSegment[iLast].pcTail -= iOffset;
            iNow = iNext;
            
            mSegment[iNow].pcTail -= iOffset;
            iLast = iNow;
            pcDes -= iOffset;
        }else{
            mSegment[iNow].pcTail++;
            if(*mSegment[iNow].pcTail == 0){
                iNow = (iNow + 1) % 2;
            }
            pcDes++;
        }
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
        M_TEST_COLLECTION(54, true, "aabd", "abdc", "aabdabcd"),
        //M_TEST_COLLECTION(49, false, "a", "b", "a"),
        //M_TEST_COLLECTION(2, false, "aabcc", "dbbca", "aadbbbaccc"),
        M_TEST_COLLECTION(1, true, "aabcc", "dbbca", "aadbbcbcac"),
		M_TEST_COLLECTION(2048, true, "abc", "xyz", "axbycz"),
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
