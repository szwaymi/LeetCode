
#include "verify.h"

int rVRF_Reverse(int iData){
    int iSign;
    unsigned iValue = (unsigned int)iData;
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
