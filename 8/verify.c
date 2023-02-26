
#include "verify.h"

int rVRF_MyAtoi(char * pcString){
    
    int iSign = 1;
    unsigned int iValue = 0;
    unsigned int iPhase = 0;
    unsigned int iMax = ((unsigned int)1 << 31) - 1;

    enum{
        V_PHASE_BEGIN=0,
        V_PHASE_SIGN,
        V_PHASE_NUMBER,
        V_PHASE_END,
    };
    
    while(*pcString){
        if(*pcString >= '0' && *pcString <= '9'){
            //Phase Number
            if(iPhase <= V_PHASE_NUMBER){
                iPhase = V_PHASE_NUMBER;
                //10 Multiple
                if(iValue){
                    //  Product
                    if(iMax / iValue >= 10){
                        iValue *= 10;
                    }else{
                    //  Overflow
                        if(iSign == -1){
                            return 0x80000000;
                        }else{
                            return 0x7FFFFFFF;
                        }
                    }
                }
                //Digit Add
                //  Overflow
                if(iMax - iValue < *pcString - '0'){
                    if(iSign == -1){ return 0x80000000; }
                    else{ return 0x7FFFFFFF;}
                }
                //  Add
                iValue += *pcString - '0';
            }
        }else if(*pcString == '-' || *pcString == '+'){
            if(iPhase >= V_PHASE_SIGN){
                break;
            }
            iPhase = V_PHASE_SIGN;
            if(*pcString == '-'){
                iSign = -1;
            }
        }else if(*pcString == ' '){
            if(iPhase == V_PHASE_SIGN){
                return 0;
            }
            if(iPhase == V_PHASE_NUMBER){
                break;
            }
        }else if(*pcString == '.')
            break;
        else{
            if(iPhase == V_PHASE_BEGIN){
                return 0;
            }
            if(iPhase == V_PHASE_SIGN){
                return 0;
            }
            if(iPhase == V_PHASE_NUMBER){
                break;
            }
        }
        pcString++;
    }
    if(iSign == -1){
        return 0xFFFFFFFF - iValue + 1;
    }
    return iValue;
}
