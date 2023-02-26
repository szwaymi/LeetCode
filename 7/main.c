
#include <stdio.h>

int reverse(int iData){
    int iSign;
    unsigned iValue = (unsigned int)iData;
    unsigned int iSource;
    unsigned int iMax = ((unsigned int)1 << 31);
    if(iData < 0){
        iSign = -1;
        iValue = (0xFFFFFFFF - iValue) + 1;
    }else{
        iSign = 1;
        iMax--;
    }

    unsigned int iResult = 0;
    while(iValue){
        if(iResult){
            if(iMax / iResult < 10){return 0;}
        }
        iResult *= 10;
        if(iResult >= iMax){
            return 0;
        }
        if(iMax - iResult < iValue % 10){return 0;}
        iResult += (iValue % 10);
        iValue /= 10;
    }

    return iResult * iSign;
}

int main(void){
    struct sTest{
        unsigned int iNO;
        int iExp;
        int iData;
    };
    struct sTest mTest[]={
        {1023, 0, 1534236469},
        {1024, 0, -2147483648},
    };

    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iCon;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        printf("Test Case [%d], Expactation = %d,", mTest[iCon].iNO, mTest[iCon].iExp);
        int iResult;
        iResult = reverse(mTest[iCon].iData);
        printf(" Result = %d\n", iResult);
    }
    
}
