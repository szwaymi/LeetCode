
#include <stdio.h>

int** fourSum(int* piSeries, int iSize, int iTarget, int* piResults, int** ppiSizes) {

	return 0;
}

int main(void) {
	//Test Data
	//	Macros
#define M_TEST_DATA(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP(N, ...) int iExps_##N[][4] = { __VA_ARGS__ };	\
	int *piExps_##N[sizeof(iExps_##N) / sizeof(iExps_##N[0])];	\
	for(unsigned int iCon = 0 ; iCon < sizeof(iExps_##N) / sizeof(iExps_##N[0]) ; iCon++){	\
		piExps_##N[iCon] = iExps_##N[iCon];	\
	}
#define M_TEST_COLLECTION(N, T) {N, {piExps_##N, sizeof(iExps_##N) / sizeof(iExps_##N[0])}, {T, sizeof(iSeries_##N) / sizeof(int), iSeries_##N}}
	//	Structures
	struct sData {
		int iTarget;
		unsigned int iSize;
		int *piSeries;
	};
	struct sExp {
		int **ppiSeries;
		unsigned int iNumber;
	};
	struct sTest {
		unsigned int iNO;
		struct sExp mExp;
		struct sData mData;
	};
	//	Data
	M_TEST_DATA(0, 1, 0, -1, 0, -2, 2);
	M_TEST_EXP(0, { -2, -1, 1, 2 }, { -2, 0, 0, 2 }, { -1, 0, 0, 1 });
	struct sTest mTest[] = {
		M_TEST_COLLECTION(0, 0)
	};

	unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
	unsigned int iConTest;
	for (iConTest = 0; iConTest < iLength; iConTest++) {
		printf("Test Case [%d], Exp =", mTest[iConTest].iNO);
		unsigned int iConExp;
		for (iConExp = 0; iConExp < mTest[iConTest].mExp.iNumber; iConExp++) {
			printf("[");
			for (unsigned int iConLoc = 0; iConLoc < 4; iConLoc++) {
				printf("%d ", mTest[iConTest].mExp.ppiSeries[iConExp][iConLoc]);
			}
			printf("]");
		}

		fourSum(mTest[iConTest].mData.piSeries, mTest[iConTest].mData.iTarget, 
			int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
	}

	return 0;

}