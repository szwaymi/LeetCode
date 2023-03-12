
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char *** groupAnagrams(char ** ppcStrs, int iLength, int *piGroups, int** ppiGroupLength){
    struct sRating{
        unsigned int iScore;
        struct sRating *pmNext;
    };
    struct sEvaluation{
        unsigned int iID;
        unsigned char iRatings;
        struct sRating *pmRatings;
    };
    struct sEvaluation *pmEva = (struct sEvaluation *)malloc(sizeof(struct sEvaluation) * iLength);
    unsigned int iCon;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        char *pcCheck = ppcStrs[iCon];
        pmEva[iCon].iID = iCon;
        pmEva[iCon].iRatings = 0;
        pmEva[iCon].pmRatings = NULL;
        struct sRating *pmRating = (struct sRating *)malloc(sizeof(struct sRating));
        pmRating
        while(*pcCheck){
            
            pcCheck++;
        }
    }

    
}

int main(void){
    //Test Data
    //  Macro
    //"eat","tea","tan","ate","nat","bat"
#define M_TEST_INPUT(N, ...) char *pcStrs_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP
#define M_TEST_COLLECTION(N) {N, {pcStrs_##N},{}}
    //  Structure
    struct sInput{
        char **ppcStrs;
    };
    struct sExp{
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    M_TEST_INPUT(1, "eat","tea","tan","ate","nat","bat");
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
