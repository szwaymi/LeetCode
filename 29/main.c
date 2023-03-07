
#include <stdio.h>


int divide(int iDividend, int iDivisor){
    //Sign Process
    unsigned iValue[2];
    char iSign[2] = {1, 1};
    if(iDividend < 0){
        iSign[0] = -1;
        iValue[0] = 0 - (unsigned int)iDividend;
    }else{
        iValue[0] = iDividend;
    }
    if(iDivisor < 0){
        iSign[1] = -1;
        iValue[1] = 0 - (unsigned int)iDivisor;
    }else{
        iValue[1] = iDivisor;
    }
    
    unsigned int iFactor = iValue[1];
    unsigned int iMulti;
    unsigned int iQ = 0;
    while(iValue[0] > iFactor){
        iFactor = iValue[1];
        iMulti = 0;
        while(iValue[0] > iFactor){
            iFactor <<= 1;
            iMulti++;
        }
        if(iValue[0] < iFactor){
            iFactor >>= 1;
        }else{
            iMulti++;
        }
        iValue[0] -= iFactor;
        iQ += (unsigned int)1 << (iMulti - 1);
        iFactor = iValue[1];
    }
    if(iValue[0] == iFactor){
        iQ++;
    }
    
    if(iSign[0] + iSign[1] == 0){
        return (int)(0 - iQ);
    }else{
        if(iQ >= 0x80000000){
            iQ = 0x7FFFFFFF;
        }
        return (int)iQ;
    }

}
int main(void){
    struct sInput{
        int iDividend;
        int iDivisor;
    };
    struct sExp{
        int iValue;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    struct sTest mTest[]={
        //{10, {-2147483648, -1}, {333}},
        {979, {1, 1},{1}},
        //{1024, {200, 5}, {40}}
    };
    
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], Expectation = %d ", mTest[iConTest].iNO, mTest[iConTest].mExp.iValue);
        int iResult = divide(mTest[iConTest].mInput.iDividend, mTest[iConTest].mInput.iDivisor);
        printf("Result = %d \n", iResult);
    }
}
