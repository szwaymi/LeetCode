
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int* findSubstring(char * pcSentence, char ** ppcKeys, int iLength, int* piResults) {
	
	unsigned int iCon;
	unsigned char *piMark = (unsigned char *)malloc(sizeof(unsigned char) * iLength);

	for (iCon = 0; iCon < iLength; iCon++) {
		piMark[iCon] = 0;
	}

	unsigned int iLoc;
	while (*pcSentence) {
		for (iCon = 0; iCon < iLength; iCon++) {
			if (piMark[iCon] == 0) {
				char *pcSrc = pcSentence;
				char *pcDes = ppcKeys[iCon];
				while(*pcDes){
					if (*pcSrc != *pcDes) {
						break;
					}
					pcSrc++;
					pcDes++;
				}
				if (*pcDes == NULL) {
					piMark[iCon]++;
				}
			}
		}

	}

}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) char *pcKeys_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ };
#define M_TEST_COLLECTION(N, S) {N, {S,pcKeys_##N, sizeof(pcKeys_##N) / sizeof(char *)}, {iExp_##N, sizoef(iExp_##N) / sizeof(int)}}
    //  Structure
    struct sInput{
		char *pcSentence;
		char **ppcKeys;
		int iLength;
    };
    struct sExp{
		int *piSeries;
		int iLength;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	//		#1
	M_TEST_INPUT(1, "foo", "bar");
	M_TEST_EXP(1, 0, 9);
    struct sTest mTest[]={
		M_TEST_COLLECTION(1, "barfoothefoobarman"),
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
