
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void sortColors(int* piSeries, int iLength) {
	int iLocR;
	int iLocL;
	int iLocM;
	int iLengthM = 0;
	iLocL = 0;
	iLocR = iLength;
	iLocM = -1;
	do {
		if (piSeries[iLocL] == 2) {
			do {
				iLocR--;
				if (piSeries[iLocR] == 0) {
					piSeries[iLocR] = 2;
					piSeries[iLocL] = 0;
					if (iLocM != -1) {
						piSeries[iLocM] = 0;
						piSeries[iLocL] = 1;
						iLocM++;
					}
					break;
				}
				else if (piSeries[iLocR] == 1) {
					if (iLocM == -1) {
						//iLocM = iLocR;
						piSeries[iLocL] = 1;
						piSeries[iLocR] = 2;
						iLocM = iLocL;
					}
					else {
						piSeries[iLocM + iLengthM] = 1;
						piSeries[iLocR] = 2;
					}
					iLengthM++;
					break;
				}
			} while (iLocR > iLocL);
		}
		else if (piSeries[iLocL] == 1) {
			if (iLocM == -1) {
				iLocM = iLocL;
			}
			iLengthM++;
		}
		else if (piSeries[iLocL] == 0) {
			if (iLocM != -1) {
				piSeries[iLocL] = 1;
				piSeries[iLocM] = 0;
				iLocM++;
			}
		}
		iLocL++;
	} while (iLocL < iLocR);
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int)}, {iExp_##N}}
    //  Structure
    struct sInput{
		int *piSeries;
		int iLength;
    };
    struct sExp{
		int *piSeries;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	//		#1
	M_TEST_INPUT(1, 2, 0, 2, 1, 1, 0);
	M_TEST_EXP(1, 0, 0, 1, 1, 2, 2);
	//		#2
	M_TEST_INPUT(2, 2, 0, 1);
	M_TEST_EXP(2, 0, 1, 2);
	//		#39
	M_TEST_INPUT(39, 1, 2, 0);
	M_TEST_EXP(39, 0, 1, 2);
	//		#42
	M_TEST_INPUT(42, 1, 0, 0);
	M_TEST_EXP(42, 0, 0, 1);
	//		#46
	M_TEST_INPUT(46, 1, 2, 1);
	M_TEST_EXP(46, 1, 1, 2);
	//		$54
	M_TEST_INPUT(54, 0, 1, 2, 0, 0, 2, 2, 1);
	M_TEST_EXP(54, 0, 0, 0, 1, 1, 2, 2, 2);
    struct sTest mTest[]={
		M_TEST_COLLECTION(54),
		M_TEST_COLLECTION(46),
		M_TEST_COLLECTION(42),
		M_TEST_COLLECTION(39),
		M_TEST_COLLECTION(2),
		M_TEST_COLLECTION(1),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
		for (unsigned int iCon = 0; iCon < mTest[iConTest].mInput.iLength; iCon++) {
			printf("%d ", mTest[iConTest].mExp.piSeries[iCon]);
		}
        //Result
        printf("Result = ");
		sortColors(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
		for (unsigned int iCon = 0; iCon < mTest[iConTest].mInput.iLength; iCon++) {
			printf("%d ", mTest[iConTest].mInput.piSeries[iCon]);
		}
        //Comparison
        int iTest = 1;
		for (unsigned int iCon = 0; iCon < mTest[iConTest].mInput.iLength; iCon++) {
			if (mTest[iConTest].mInput.piSeries[iCon] != mTest[iConTest].mExp.piSeries[iCon]) {
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
