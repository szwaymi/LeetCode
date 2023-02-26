
#include <string.h>
#include <stdio.h>

char gcResult[17];

char * intToRoman(int iValue){

    char cRomand[4][2]={
        {'M', ' '},
        {'C', 'D'},
        {'X', 'L'},
        {'I', 'V'},
    };
    char *pcPut = gcResult;
    unsigned int iDivider = 1000;
    unsigned char iLoc = 0;
    while(iDivider){
        unsigned char iDigit;
        iDigit = (iValue / iDivider);
        if(iDigit > 0 && iDigit < 4){
            for(unsigned char iCon = 0 ; iCon < iDigit ; iCon++){
                *pcPut = cRomand[iLoc][0];
                pcPut++;
            }
        }else if(iDigit == 4){
            *pcPut = cRomand[iLoc][0];
            pcPut++;
            *pcPut = cRomand[iLoc][1];
            pcPut++;
        }else if(iDigit > 4 && iDigit < 9){
            *pcPut = cRomand[iLoc][1];
            pcPut++;
            for(unsigned char iCon = 0 ; iCon < iDigit - 5 ; iCon++){
                *pcPut = cRomand[iLoc][0];
                pcPut++;
            }
        }else if(iDigit == 9){
            *pcPut = cRomand[iLoc][0];
            pcPut++;
            *pcPut = cRomand[iLoc - 1][0];
            pcPut++;
        }
        iValue %= iDivider;
        iDivider /= 10;
        iLoc++;
    }
    *pcPut = 0;
    return gcResult;
}
int main(void){
    struct sTest{
        unsigned int iNO;
        char *pcExp;
        int iInput;
    };
    struct sTest mTest[]={
        {   1, "III",               3},
        {   2, "LVIII",            58},
        {   4, "MCMXCIV",        1994},
        {1889, "MDCCCLXXXVIII",  1888},
    };
    
    unsigned int iLength = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iCon;
    for(iCon = 0 ; iCon < iLength ; iCon++){
        printf("Test Case [%d], Expactation = %s, ", mTest[iCon].iNO, mTest[iCon].pcExp);
        char *pcResult;
        pcResult = intToRoman(mTest[iCon].iInput);
        printf(" Result = %s ", pcResult);
        int iTest = strcmp(mTest[iCon].pcExp, pcResult);
        if(iTest == 0){
            printf("[PASS]");
        }else{
            printf("[FAIL];");
        }
        printf("\n");
    }
}
