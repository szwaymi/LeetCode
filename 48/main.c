
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void rotate(int** ppiMatrix, int iSize, int* piCols){
    int iLocX;
    int iLocY;
    unsigned int iConZ;
    for(iConZ = iSize ; iConZ > 1 ; iConZ-=2){
        unsigned int iConX;
        int iBoundary[2];
        iBoundary[0] = (iSize - iConZ) / 2;
        iBoundary[1] = iBoundary[0] + iConZ - 1;
        for(iConX = 0 ; iConX < iConZ - 1 ; iConX++){
            unsigned int iConY;
            unsigned int iLast;
            iLocY = (iSize - iConZ) / 2;
            iLocX = iLocY + iConX;
            //printf("[%d %d]\n", iLocX, iLocY);
            int iShift[4][2]={
                {1,0},{0,1},{-1,0},{0,-1}
            };
            iLast = ppiMatrix[iLocY][iLocX];
            for(iConY = 0 ; iConY <4 ; iConY++){
                int iStep = iConZ - 1;
                iLocX += iShift[iConY][0] * iStep;
                iLocY += iShift[iConY][1] * iStep;
                if(iLocX > iBoundary[1]){
                    iLocY += iLocX - iBoundary[1];
                    iLocX = iBoundary[1];
                }
                else if(iLocX < iBoundary[0]){
                    iLocY += iLocX - iBoundary[0];
                    iLocX = iBoundary[0];
                }
                if(iLocY > iBoundary[1]){
                    iLocX -= iLocY - iBoundary[1];
                    iLocY = iBoundary[1];
                }
                else if(iLocY < iBoundary[0]){
                    iLocX += iBoundary[0] - iLocY;
                    iLocY = iBoundary[0];
                }
                //Problem is here,
                //Location Overflow Rules is here:
                //+X>+Y, -X>-Y; +Y>-X,iY>+X
                int iTemp;
                iTemp = ppiMatrix[iLocY][iLocX];
                ppiMatrix[iLocY][iLocX] = iLast;
                iLast = iTemp;
                //printf("%d %d %d: %d %d\n",iConZ, iConX, iConY,iLocX,iLocY);
            }
        }
    }
}
void rShowMatrix(int **ppiMatrix, unsigned int iDimension, unsigned int iTab){
    unsigned int iConX;
    unsigned int iConY;
    unsigned int iConTab;
    for(iConY = 0 ; iConY < iDimension ; iConY++){
        for(iConTab = 0 ; iConTab < iTab ; iConTab++){printf(" ");}
        for(iConX = 0 ; iConX < iDimension ; iConX++){
            printf("%2d ", ppiMatrix[iConY][iConX]);
        }
        printf("\n");
    }
}
int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, D, ...) int iSeries_##N[][D] = { __VA_ARGS__ };int *piSeries_##N[D];int iCols_##N[D];for(unsigned int iCon = 0 ; iCon < D ; iCon++){piSeries_##N[iCon] = iSeries_##N[iCon];iCols_##N[iCon] = D;}
#define M_TEST_EXP(N, ...) int iExp_##N[][sizeof(iSeries_##N) / sizeof(iSeries_##N[0])] = { __VA_ARGS__ };int *piExp_##N[sizeof(iSeries_##N) / sizeof(iSeries_##N[0])];for(unsigned int iCon = 0 ; iCon < sizeof(iSeries_##N) / sizeof(iSeries_##N[0]) ; iCon++){piExp_##N[iCon] = iExp_##N[iCon];}
#define M_TEST_COLLECTION(N) {N, {piSeries_##N, sizeof(iSeries_##N) / sizeof(iSeries_##N[0]), iCols_##N},{piExp_##N}}
    //  Structure
    struct sInput{
        int **piMatrix;
        int iSize;
        int *piCols;
    };
    struct sExp{
        int **piMatrix;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    //      [#1]
    M_TEST_INPUT(1, 3, {1,2,3},{4,5,6},{7,8,9});
    M_TEST_EXP(1, {7,4,1},{8,5,2},{9,6,3});
    M_TEST_INPUT(2, 4, {5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16});
    M_TEST_EXP(2, {15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11});
    struct sTest mTest[]={
        M_TEST_COLLECTION(1),
        M_TEST_COLLECTION(2),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d]\n", mTest[iConTest].iNO);
        //Expectaion
        printf("  Expecation:\n");
        rShowMatrix(mTest[iConTest].mExp.piMatrix, mTest[iConTest].mInput.iSize, 4);
        //Result
        printf("  Result:\n");
        rotate(mTest[iConTest].mInput.piMatrix, mTest[iConTest].mInput.iSize, mTest[iConTest].mInput.piCols);
        rShowMatrix(mTest[iConTest].mInput.piMatrix, mTest[iConTest].mInput.iSize, 4);
        //Comparison
        int iTest = 1;
        {
            unsigned int iConY;
            for(iConY = 0 ; iConY < mTest[iConTest].mInput.iSize ; iConY++){
                unsigned int iConX;
                for(iConX = 0 ; iConX < mTest[iConTest].mInput.iSize ; iConX++){
                    if(mTest[iConTest].mInput.piMatrix[iConY][iConX] != mTest[iConTest].mExp.piMatrix[iConY][iConX]){
                        iTest = 0;
                        break;
                    }
                }
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
