
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * convert(char * pcSource, int iRows){
    char *pcDes;
    unsigned int iSize = (unsigned int)strlen(pcSource);
    unsigned int iGroupSize;
    if(iRows < 3){
        iGroupSize = iRows;
    }else{
        iGroupSize = iRows * 2 - 2;
    }
    printf("Group Size = %d\n", iGroupSize);
    pcDes = (char *)malloc(iSize + 1);
    char *pcPut = pcDes;
    
    unsigned int iConRow;
    for(iConRow = 0 ; iConRow < iRows ; iConRow++){
        char *pcGet = pcSource + iConRow;
        if(iConRow == 0 || iConRow == iRows - 1){
            while(pcGet < pcSource + iSize){
                *pcPut = *pcGet;
                pcGet += iGroupSize;
                pcPut++;
            }
        }else{
            while(pcGet < pcSource + iSize){
                *pcPut = *pcGet;
                pcPut++;
                char *pcGet2 = pcGet + iGroupSize - iConRow * 2;
                if(pcGet2 < pcSource + iSize){
                    *pcPut = *(pcGet + iGroupSize - iConRow * 2);
                    pcPut++;
                }
                pcGet += iGroupSize;
            }
        }
    }
    *pcPut = 0;
    return pcDes;
}

int main(int argc, const char * argv[]) {

    struct sData{
        char *pcString;
        unsigned int iRows;
    };
    struct sTest{
        unsigned int iNO;
        char *pcExp;
        struct sData mData;
    };
    struct sTest mTest[]={
        {1, "PAHNAPLSIIGYIR", {"PAYPALISHIRING", 3}},
        {2, "PINALSIGYAHRPI", {"PAYPALISHIRING", 4}},
        {3, "A", {"A", 1}},
        {4, "A", {"A", 2}},
    };
 
    unsigned int iCon;
    for(iCon= 0 ; iCon < sizeof(mTest) / sizeof(struct sTest) ; iCon++){
        char *pcResult;
        pcResult = convert(mTest[iCon].mData.pcString, mTest[iCon].mData.iRows);
        printf("(%s),%d\n", pcResult, strcmp(pcResult, mTest[iCon].pcExp));
        free(pcResult);
    }
    
    return 0;
}

