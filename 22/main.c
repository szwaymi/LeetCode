
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "verify.h"
#include "solution.h"


#define M_TEST_EXAM rMSL_GenerateParenthesis
#define M_TEST_VERIFY rVRF_GenerateParenthesis

int main(void){
	
    //Test Data
    //  Macros
#define M_TEST_EXP(N, ...) char *pcExp_##N[] = { __VA_ARGS__ };	\
	struct sExp mExp_##N = {	\
		sizeof(pcExp_##N) / sizeof(char *), pcExp_##N	\
	};
#define M_TEST_COLLECTION(N, P) {N, {P}, &mExp_##N}
#define M_TEST_COLLECTION_VERIFY(N, P) {N, {P} , NULL}
    //  Structures
    struct sInput{
        unsigned int iNumber;
    };
    struct sExp{
		int iNumber;
        char **ppcParentheses;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp *pmExp;
    };
    //  Data
    //      Exp
	M_TEST_EXP(0, "()");
	M_TEST_EXP(1, "()()", "(())");
    M_TEST_EXP(2, "((()))","(()())","(())()","()(())","()()()");
	M_TEST_EXP(3, "(((())))", "((()()))", "(()(()))", "((())())", "(()()())", "()((()))", "()(()())", "(())(())", "((()))()", "(()())()", "()()(())", "()(())()", "(())()()", "()()()()");
    //      Test
    struct sTest mTest[]={
		//M_TEST_COLLECTION(0, 1),
		//M_TEST_COLLECTION(1, 2),
        //M_TEST_COLLECTION(2, 3),
		//M_TEST_COLLECTION(3, 4),
		//M_TEST_COLLECTION_VERIFY(4, 5),
		//M_TEST_COLLECTION_VERIFY(5, 6),
		//M_TEST_COLLECTION_VERIFY(6, 7),
		M_TEST_COLLECTION_VERIFY(7, 8),
    };

    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
	struct sExp mExp;
    for(iConTest = 0 ; iConTest < iLength ; iConTest++){
        printf("Test Case [%d], Expactation = ", mTest[iConTest].iNO);
		
		mExp.iNumber = 0;
		if (mTest[iConTest].pmExp == NULL) {
			mTest[iConTest].pmExp = &mExp;
			mExp.ppcParentheses = M_TEST_VERIFY(mTest[iConTest].mInput.iNumber, &mExp.iNumber);
		}

		unsigned int iConExp;
        for(iConExp = 0 ; iConExp < mTest[iConTest].pmExp->iNumber ; iConExp++){
            printf("%s ", mTest[iConTest].pmExp->ppcParentheses[iConExp]);
        }
        int iResults;
        char **ppcResults;
        ppcResults = M_TEST_EXAM(mTest[iConTest].mInput.iNumber, &iResults);
		printf("Result = ");
		unsigned int iConResults;
		for (iConResults = 0; iConResults < iResults; iConResults++) {
			printf("%s ", ppcResults[iConResults]);
		}
        int iTest = 0;
		if (iResults == mTest[iConTest].pmExp->iNumber) {
			iTest = 1;
			for (iConExp = 0; iConExp < mTest[iConTest].pmExp->iNumber; iConExp++) {
				for (iConResults = 0; iConResults < iResults; iConResults++) {
					if (strcmp(ppcResults[iConResults], mTest[iConTest].pmExp->ppcParentheses[iConExp]) == 0) {
						break;
					}
				}
				if (iConResults == iResults) {
					iTest = 0;
					break;
				}
			}
		}
		for (iConResults = 0; iConResults < iResults; iConResults++) {
			free(ppcResults[iConResults]);
		}
		free(ppcResults);
		if (mExp.iNumber) {
			for (iConExp = 0; iConExp < mExp.iNumber; iConExp++) {
				free(mExp.ppcParentheses[iConExp]);
			}
			free(mExp.ppcParentheses);
		}
        if(iTest){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        printf("\n");
		if (!iTest) { break; }
    }
	if (iConTest == iLength) {
		printf("[PASS]\n");
	}
	else {
		printf("[FAIL]\n");
	}
    
}
