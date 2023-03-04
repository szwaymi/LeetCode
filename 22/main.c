
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sParenthese{
    unsigned int iNumber;
    struct sParenthese *pmChildren;
};
struct sResult{
    struct sResult *pmNext;
    char *pcParentheses;
};

struct{
    unsigned int iResults;
    unsigned int iNumber;
    struct sParenthese mParentheses;
    struct sResult *pmResults;
    char *pcParenceses;
}gmMeta;

void rTrace(struct sParenthese *pmParent){
    unsigned int iCon;
    for(iCon = 0 ; iCon < pmParent->iNumber ; iCon++){
        *gmMeta.pcParenceses = '(';
        gmMeta.pcParenceses++;
        rTrace(&pmParent->pmChildren[iCon]);
        *gmMeta.pcParenceses = ')';
        gmMeta.pcParenceses++;
    }
}
void rGenerate(unsigned int iAvailable, unsigned int iLeft, struct sParenthese *pmParent){
    pmParent->iNumber = 0;
    unsigned char *piChunks = (unsigned char *)malloc(sizeof(unsigned char) * iAvailable);
    unsigned int iConN;
    for(iConN = iAvailable ; iConN > 0 ; iConN--){
        unsigned int iConChunk;
        pmParent->iNumber = iConN;
        pmParent->pmChildren = (struct sParenthese *)malloc(sizeof(struct sParenthese) * iConN);
        if(iConN < iLeft){
            unsigned int iNext = iAvailable - iConN;
            for(iConChunk = 1 ; iConChunk < iConN ; iConChunk++){
                piChunks[iConChunk] = 0;
            }
            piChunks[0] = iNext - 1;
            do{
                unsigned int iSum = 0 ;
                piChunks[0]++;
                for(iConChunk = 0 ; iConChunk < iConN - 1 ; iConChunk++){
                    if(piChunks[iConChunk] > iNext){
                        piChunks[iConChunk] = 0 ;
                        piChunks[iConChunk + 1]++;
                    }
                    iSum += piChunks[iConChunk];
                }
                iSum += piChunks[iConChunk];
                if(iSum == iNext){
                    for(iConChunk = 0 ; iConChunk < iConN ; iConChunk++){
                        rGenerate(piChunks[iConChunk], iLeft - iConN, &pmParent->pmChildren[iConChunk]);
                    }
                }
            }while(piChunks[iConN - 1] != iNext);
        }else{
            struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
            pmResult->pmNext = gmMeta.pmResults;
            gmMeta.pmResults = pmResult;
            pmResult->pcParentheses = (char *)malloc(sizeof(char) * (gmMeta.iNumber * 2 +1));
            gmMeta.pcParenceses = pmResult->pcParentheses;
            gmMeta.iResults++;
            rTrace(&gmMeta.mParentheses);
            *gmMeta.pcParenceses = 0;
        }
        free(pmParent->pmChildren);
    }
}

char ** generateParenthesis(int iNumber, int* piResults){
    gmMeta.iResults = 0;
    gmMeta.iNumber = iNumber;
    gmMeta.pmResults = NULL;
    rGenerate(3,3, &gmMeta.mParentheses);
    char **ppcResults = (char **)malloc(sizeof(char *) * gmMeta.iResults);
    unsigned iCon;
    for(iCon = 0 ; iCon < gmMeta.iResults ; iCon++){
        struct sResult *pmResult = gmMeta.pmResults;
        ppcResults[iCon] = pmResult->pcParentheses;
        gmMeta.pmResults = pmResult->pmNext;
        free(pmResult);
    }
    *piResults = gmMeta.iResults;
    return ppcResults;
}

int main(void){
    //Test Data
    //  Macros
#define M_TEST_EXP(N, ...) char *pcExp_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N, P) {N, {P}, {sizeof(pcExp_##N) / sizeof(char *), pcExp_##N}}
    //  Structures
    struct sInput{
        unsigned int iNumber;
    };
    struct sExp{
        unsigned int iNumber;
        char **ppcParentheses;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    //      Exp
    M_TEST_EXP(0, "((()))","(()())","(())()","()(())","()()()");
    //      Test
    struct sTest mTest[]={
        M_TEST_COLLECTION(0, 3),
    };
    
    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLength ; iConTest++){
        printf("Test Case [%d], Expactation = ", iConTest);
        unsigned int iConExp;
        for(iConExp = 0 ; iConExp < mTest[iConTest].mExp.iNumber ; iConExp++){
            printf("%s ", mTest[iConTest].mExp.ppcParentheses[iConExp]);
        }
        int iResults;
        char **ppcResults;
        ppcResults = generateParenthesis(mTest[iConTest].mInput.iNumber, &iResults);
        int iTest = 1;
        for(iConExp = 0 ; iConExp < mTest[iConTest].mExp.iNumber ; iConExp++){
            unsigned int iConResults;
            for(iConResults = 0 ; iConResults < iResults ; iConResults++){
                if(strcmp(ppcResults[iConResults],mTest[iConTest].mExp.ppcParentheses[iConExp]) == 0){
                    break;
                }
            }
            if(iConResults == iResults){
                iTest = 0;
                break;
            }
        }
        if(iTest){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        printf("\n");
    }
    
}
