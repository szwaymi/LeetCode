
#include <stdio.h>
#include "verify.h"

#define M_TEST_VERIFY	rVRF_NextPermutation
#define M_TEST_EXAM		rVRF_NextPermutation

int main(void) {
	//Test Data
	//	Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ };int iVerify_##N[] = { __VA_ARGS__ };
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ };
#define M_TEST_COLLECTION(N) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int)}, {iExp_##N}, {iVerify_##N}}
	//	Structures
	struct sInput {
		int *piSeries;
		int iLength;
	};
	struct sExp {
		int *piSeries;
	};
	struct sVerify {
		int *piSeries;
	};
	struct sTest {
		unsigned int iNO;
		struct sInput mInput;
		struct sExp mExp;
		struct sVerify mVerify;
	};
	//	Data
	//		#1
	M_TEST_INPUT(1, 1, 2, 3);
	M_TEST_EXP(1, 1, 3, 2);
	//		#2
	M_TEST_INPUT(2, 3, 2, 1);
	M_TEST_EXP(2, 1, 2, 3);
	//		#3
	M_TEST_INPUT(3, 1, 3, 2);
	M_TEST_EXP(3, 2, 1, 3);
	//		Collections
	struct sTest mTest[] = {
		M_TEST_COLLECTION(1),
		M_TEST_COLLECTION(2),
		M_TEST_COLLECTION(3),
	};

	unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
	unsigned int iConTest;
	for (iConTest = 0; iConTest < iLengthTest; iConTest++) {
		unsigned int iConSeries;
		printf("Test Case [%d], Expectation = [", mTest[iConTest].iNO);
		for (iConSeries = 0; iConSeries < mTest[iConTest].mInput.iLength; iConSeries++) {
			printf("%d ", mTest[iConTest].mExp.piSeries[iConSeries]);
		}
		printf("] Result = ");
		M_TEST_EXAM(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
		printf("[");
		for (iConSeries = 0; iConSeries < mTest[0].mInput.iLength; iConSeries++) {
			printf("%d ", mTest[0].mInput.piSeries[iConSeries]);
		}
		printf("]");
		for (iConSeries = 0; iConSeries < mTest[iConTest].mInput.iLength; iConSeries++) {
			if (mTest[iConTest].mExp.piSeries[iConSeries] != mTest[iConTest].mInput.piSeries[iConSeries]) {
				break;
			}
		}
		int iTest = iConSeries == mTest[iConTest].mInput.iLength;
		if (iTest) {
			printf("[PASS]");
		} else {
			printf("[FAIL]");
		}
		printf("\n");
		if (!iTest) {
			break;
		}
	}
	if (iConTest == iLengthTest) {
		printf("[PASS]\n");
	}
	else {
		printf("[FAIL]\n");
	}

}