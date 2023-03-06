
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sCache {
	unsigned int iCombinations;
	char **ppcParentheses;
};

struct {
	struct sCache *pmCaches;
}gmMeta;

void rGenerate(unsigned int iNumber) {
	struct sResult {
		unsigned char iNumber;
		char **ppcParentheeses;
		struct sResult *pmNext;
	};
	struct sResult *pmResults = NULL;
	unsigned int iConNumber;
	for (iConNumber = iNumber; iConNumber > 0; iConNumber--) {
		unsigned char iLeft = iNumber - iConNumber;
		struct sChunk {
			unsigned char iLeft;
		};
		struct sChunk *pmChunks = (struct sChunk *)malloc(sizeof(struct sChunk) * iConNumber);
		unsigned int iConChunks;
		for (iConChunks = 1; iConChunks < iConNumber; iConChunks++) {
			pmChunks[iConChunks].iLeft = 0;
		}
		pmChunks[0].iLeft = iLeft - 1;
		do {
			unsigned int iSum = 0;
			pmChunks[0].iLeft++;
			for (iConChunks = 0; iConChunks < iConNumber - 1; iConChunks++) {
				if (pmChunks[iConChunks].iLeft > iLeft) {
					pmChunks[iConChunks].iLeft = 0;
					pmChunks[iConChunks + 1].iLeft++;
				}
				iSum += pmChunks[iConChunks].iLeft;
			}
			iSum += pmChunks[iConChunks].iLeft;
			if (iSum == iLeft) {
				unsigned int iCombinations = 1;
				for (iConChunks = 0; iConChunks < iConNumber; iConChunks++) {
					if (gmMeta.pmCaches[pmChunks[iConChunks].iLeft].iCombinations == 0xFFFFFFFF){
						rGenerate(pmChunks[iConChunks].iLeft);
					}
					iCombinations *= gmMeta.pmCaches[pmChunks[iConChunks].iLeft].iCombinations;
				}
				struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
				pmResult->pmNext = pmResults;
				pmResults = pmResult;
				pmResult->iNumber = iCombinations;
				pmResult->ppcParentheeses = (char **)malloc(sizeof(char *) * iCombinations);




			}
		} while (pmChunks[iConNumber - 1].iLeft != iLeft);
	}
}

char ** generateParenthesis(int iNumber, int* piResults){
	static char *pcTemp[] = { "" };
	unsigned int iCon;
	gmMeta.pmCaches = (struct sCache *)malloc(sizeof(struct sCache) * iNumber);
	gmMeta.pmCaches[0].iCombinations = 1;
	gmMeta.pmCaches[0].ppcParentheses = pcTemp;
	for (iCon = 1; iCon < iNumber; iCon++) {
		gmMeta.pmCaches[iCon].iCombinations = 0xFFFFFFFF;
	}
	rGenerate(1);
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
