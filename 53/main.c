
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*
int maxSubArray(int* piSeries, int iLength) {
    printf("\n");
    printf("%d\n", iLength);
    int *piLeft = (int *)malloc(sizeof(int) * iLength);
    int *piRight = (int *)malloc(sizeof(int) * iLength);
    int iSum;
    int iTotal;
    unsigned int iCon;
    unsigned int iLoc;
    int iLast;
    int iMin = 0x80000000;
    
    iLast = -1;
    iLoc = 0;
    iSum = 0;
    piLeft[0] = 0;
    iLoc++;
    for(iCon = 0 ; iCon < iLength - 1 ; iCon++){
        if(iLast < 0 && piSeries[iCon] < 0){
            if(piSeries[iCon] > iMin){
                iMin = piSeries[iCon];
            }
            continue;
        }
        iSum += piSeries[iCon];
        piLeft[iLoc] = iSum;
        iLoc++;
        iLast = 1;
    }
    if(iLoc == 1){
        if(piSeries[iCon] > iMin){return piSeries[iCon];}
        return iMin;
    }
    iTotal = iSum + piSeries[iCon];
    if(iCon >= iLoc){
        piSeries = &piSeries[iCon - iLoc + 1];
        iLength = iLoc;
    }
    printf("%d %d\n", iCon, iLoc);
    
    iSum = 0;
    piRight[0] = 0;
    for(iCon = 0 ; iCon < iLength - 1 ; iCon++){
        iSum += piSeries[iLength - 1 - iCon];
        piRight[iCon + 1] = iSum;
    }
    
    iLast = 1;
    iMin = 0x7FFFFFFF;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        unsigned int iConT;
        if(piRight[iCon] >= iLast){
            continue;;
        }
        for(iConT = 0 ; iConT < iLength - iCon ; iConT++){
            int iTemp = piRight[iCon] + piLeft[iConT];
            if(iTemp < iMin){
                iMin = iTemp;
            }
        }
        iLast = piRight[iCon];
    }
    return iTotal - iMin;
}
*/
int maxSubArray(int* nums, int size) {
//int maxSubArray(vector<int>& nums) {
        int sum=0;
        int temp=0x80000000;
        for(int i=0;i<size;i++){
            sum=sum+nums[i];
            if(temp<sum){
                temp=sum;
            }
           if(sum<0){
                sum=0;
            }
           
        }
        return temp;
    }

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) int iSeries_##N[] = { __VA_ARGS__ }
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, S) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(int)} , {S}}
    //  Structure
    struct sInput{
		int *piSeries;
		int iLength;
    };
    struct sExp{
		int iSum;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	M_TEST_INPUT(1, -2, 1, -3, 4, -1, 2, 1, -5, 4);
	M_TEST_INPUT(2, 1);
	M_TEST_INPUT(3, 5, 4, -1, 7, 8);
	M_TEST_INPUT(11, 1, -1, 1);
	M_TEST_INPUT(13, -1, 0, -2);
	M_TEST_INPUT(129, -2, 1);
	M_TEST_INPUT(134, -1, -2);
	M_TEST_INPUT(140, -1);
    M_TEST_INPUT(146, -2, 1, -3, 4, -1, 2, 1, -5, 4);
	M_TEST_INPUT(154, -2, -1);
	M_TEST_INPUT(171, -1, 0, -2, 2);
	M_TEST_INPUT(178, 0, -3, 1, 1);
	M_TEST_INPUT(184, 1, 2, -1, -2, 2, 1, -2, 1);
	M_TEST_INPUT(1024, -10, -1, -1, 1, 2, 3);
	M_TEST_INPUT(1025, -100, -2, 1, 1, 1, 1,-300);
    M_TEST_INPUT(1026, -1, -1, -1, -1, -1, -1, -1);
	struct sTest mTest[] = {
        M_TEST_COLLECTION(1026, -1),
		M_TEST_COLLECTION(1, 6),
		M_TEST_COLLECTION(2, 1),
		M_TEST_COLLECTION(3, 23),
		M_TEST_COLLECTION(11, 1),
		M_TEST_COLLECTION(13, 0),
		M_TEST_COLLECTION(129, 1),
		M_TEST_COLLECTION(134, -1),
		M_TEST_COLLECTION(140, -1),
        M_TEST_COLLECTION(146, 6),
		M_TEST_COLLECTION(154, -1),
		M_TEST_COLLECTION(171, 2),
		M_TEST_COLLECTION(178, 2),
		M_TEST_COLLECTION(184, 3),
		M_TEST_COLLECTION(1024, 6),
		M_TEST_COLLECTION(1025, 4),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %d, ", mTest[iConTest].mExp.iSum);
        //Result
        printf("Result = ");
		int iResult = maxSubArray(mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
		printf("%d ", iResult);
        //Comparison
        int iTest = iResult == mTest[iConTest].mExp.iSum;
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
