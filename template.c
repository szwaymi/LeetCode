
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * rProduce(int iNumber){
    char *pcResult;
    if(iNumber == 1){
        pcResult = (char *)malloc(sizeof(char) * 2);
        pcResult[0] = '1';
        pcResult[1] = 0;
    }else{
        char *pcSentence = rProduce(iNumber - 1);
        pcResult = (char *)malloc(sizeof(char) * (strlen(pcSentence) * 2 + 1));
        char *pcDes = pcResult;
        char *pcSrc = pcSentence;
        unsigned char iNumber = 0;
        char cV = 0;
        while(*pcSrc){
            if(cV != *pcSrc){
                if(iNumber){
                    *pcDes = iNumber + '0';
                    pcDes++;
                    *pcDes = cV;
                    pcDes++;
                    *pcDes = 0;
                    iNumber = 0;
                }
                cV = *pcSrc;
            }
            iNumber++;
            pcSrc++;
        }
        *pcDes = iNumber + '0';
        pcDes++;
        *pcDes = cV;
        pcDes++;
        *pcDes = 0;
        free(pcSentence);
    }
    return pcResult;
}

char * countAndSay(int iNumber){
    return rProduce(iNumber);
}

int main(void){
    struct sInput{
        int iNumber;
    };
    struct sExp{
        char *pcSentence;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    struct sTest mTest[]={
        //{1, {1}, {"1"}},
        {2, {4}, {"1211"}},
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        char *pcResult =
        countAndSay(mTest[iConTest].mInput.iNumber);
        printf("%s\n", pcResult);
    }
}
