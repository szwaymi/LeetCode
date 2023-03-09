
#include <stdio.h>

struct{
    int iLocation[2];
    int *piSeries;
    int iTarget;
}gmMeta;

void rSearch(int iLeft, int iRight){

	//if (iLeft == iRight) { return; }
	printf("[%d %d]", iLeft, iRight);
    int iMiddle = (iLeft + iRight) / 2;

    if(gmMeta.piSeries[iLeft] <= gmMeta.iTarget && gmMeta.piSeries[iMiddle] >= gmMeta.iTarget){
		unsigned char iAcc = 0;
        if(gmMeta.piSeries[iMiddle] == gmMeta.iTarget && iMiddle > gmMeta.iLocation[1]){
            gmMeta.iLocation[1] = iMiddle;
			iAcc++;
        }
        if(gmMeta.piSeries[iLeft] == gmMeta.iTarget && iLeft < gmMeta.iLocation[0]){
            gmMeta.iLocation[0] = iLeft;
			iAcc++;
        }
		if (iAcc == 1) {
			rSearch(iLeft, iMiddle);
		}
    }
    if(gmMeta.piSeries[iMiddle+1] <= gmMeta.iTarget && gmMeta.piSeries[iRight] >= gmMeta.iTarget){
        if(gmMeta.piSeries[iRight] == gmMeta.iTarget && iRight > gmMeta.iLocation[1]){
            gmMeta.iLocation[1] = iRight;
        }
        if(gmMeta.piSeries[iMiddle + 1] == gmMeta.iTarget && iMiddle + 1 < gmMeta.iLocation[0]){
            gmMeta.iLocation[0] = iMiddle + 1;
        }
        if(iMiddle + 1 < iRight){
            rSearch(iMiddle + 1, iRight);
        }
    }
}
int* searchRange(int* piSeries, int iSize, int iTarget, int* piResults) {
	gmMeta.iLocation[0] = iSize;
	gmMeta.iLocation[1] = -1;
	if (iSize) {
		gmMeta.piSeries = piSeries;
		gmMeta.iTarget = iTarget;
		rSearch(0, iSize - 1);
	}
	*piResults = 2;
	int *piRange = (int *)malloc(sizeof(int) * 2);
	if (gmMeta.iLocation[0] == iSize) { piRange[0] = -1; }
	else { piRange[0] = gmMeta.iLocation[0]; }
	piRange[1] = gmMeta.iLocation[1];
	return piRange;
}
int main(void){
        
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP(N, ...) int iExp_##N[] = { __VA_ARGS__ }
#define M_TEST_COLLECTION(N, T) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int), T}, {sizeof(iExp_##N) / sizeof(int), iExp_##N}}
    struct sInput{
        int *piSeries;
        int iLength;
        int iTarget;
    };
    struct sExp{
        int iSize;
        int *piRange;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
	//#1
    M_TEST_INPUT(1, 5, 7, 7, 8, 8, 10);
    M_TEST_EXP(1, 3, 4);
	//#2
	M_TEST_INPUT(2, 5, 7, 7, 8, 8, 10);
	M_TEST_EXP(2, -1, -1);
	//#47
	M_TEST_INPUT(47, 1);
	M_TEST_EXP(47, 0, 0);
	//#
	M_TEST_INPUT(1024, 7, 7, 8);
	M_TEST_EXP(1024, 2, 2);
    struct sTest mTest[]={
        //M_TEST_COLLECTION(1, 8),
		//M_TEST_COLLECTION(2, 6),
        M_TEST_COLLECTION(47, 1),
        //M_TEST_COLLECTION(1024, 8),
    };
    
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        int iResultSize;
        int *piResult =
        searchRange(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength, mTest[iConTest].mInput.iTarget, &iResultSize);
		printf("[%d %d]\n", piResult[0], piResult[1]);
        //printf("[%d %d] [%d %d]\n", mTest[iConTest].mExp.piLocation[0], mTest[iConTest].mExp.piLocation[1], piResult[0], piResult[1]);
    }
    
    
}

