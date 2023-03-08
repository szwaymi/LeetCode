
#include <stdio.h>

void rQuickSort(int *piValues, unsigned int iSize) {
	unsigned int iLeft;
	unsigned int iRight;
	iLeft = 0;
	iRight = iSize;

	do {
		do {
			iRight--;
		} while (piValues[0] <= piValues[iRight] && iLeft < iRight);
		do {
			iLeft++;
		} while (piValues[0] > piValues[iLeft] && iLeft < iRight);
		if (iLeft < iRight) {
			unsigned int iTemp;
			iTemp = piValues[iLeft];
			piValues[iLeft] = piValues[iRight];
			piValues[iRight] = iTemp;
		}
	} while (iLeft < iRight);

	unsigned int iTemp;
	iTemp = piValues[0];
	piValues[0] = piValues[iRight];
	piValues[iRight] = iTemp;

	if (iRight > 1) {
		rQuickSort(&piValues[0], iRight);
	}
	if (iSize - iRight - 1 > 1) {
		rQuickSort(&piValues[iRight + 1], iSize - iRight - 1);
	}
	return;
}

void nextPermutation(int* piSeries, int iLength) {

	unsigned int iConTarget;
	unsigned int iConSearch;
	unsigned int iLocMin = 0xFFFFFFFF;
	unsigned int iLocTarget;
	for (iConTarget = 1; iConTarget < iLength; iConTarget++) {
		iLocTarget = iLength - 1 - iConTarget;
		int iMin = 0x7FFFFFFF;
		for (iConSearch = iLocTarget + 1; iConSearch < iLength; iConSearch++) {
			if (piSeries[iLocTarget] < piSeries[iConSearch]) {
				if (piSeries[iConSearch] < iMin) {
					iLocMin = iConSearch;
				}
			}
		}
		if (iLocMin != 0xFFFFFFFF) {
			break;
		}
	}
	if (iLocMin == 0xFFFFFFFF) {
		for (iConSearch = 0; iConSearch < iLength / 2; iConSearch++) {
			unsigned int iTemp;
			iTemp = piSeries[iConSearch];
			piSeries[iConSearch] = piSeries[iLength - iConSearch - 1];
			piSeries[iLength - iConSearch - 1] = iTemp;

		}
	}
	else {
		int iTemp;
		iTemp = piSeries[iLocTarget];
		piSeries[iLocTarget] = piSeries[iLocMin];
		piSeries[iLocMin] = iTemp;
		unsigned int iSizeSort = iLength - iLocTarget - 1;
		if (iSizeSort > 1) {
			rQuickSort(&piSeries[iLocTarget + 1], iLength - iLocTarget - 1);
		}
	}
}

int main(void) {
	
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ };
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ };
#define M_TEST_COLLECTION(N) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int)}, {iExp_##N}}
	struct sInput {
		int *piSeries;
		int iLength;
	};
	struct sExp {
		int *piSeries;
	};
	struct sTest {
		unsigned int iNO;
		struct sInput mInput;
		struct sExp mExp;
	};
	M_TEST_INPUT(1, 1, 2, 3);
	M_TEST_EXP(1, 1, 3, 2);
	M_TEST_INPUT(2, 3, 2, 1);
	M_TEST_EXP(2, 1, 2, 3);
	M_TEST_INPUT(3, 1, 3, 2);
	M_TEST_EXP(3, 2, 1, 3);
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
		nextPermutation(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
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