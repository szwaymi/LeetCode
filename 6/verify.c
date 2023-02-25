
#include <stdlib.h>
#include <string.h>
#include "verify.h"

char * rVRF_Convert(char * pcSource, int iRows){
    char *pcDes;
    unsigned int iSize = (unsigned int)strlen(pcSource);
    unsigned int iGroupSize;
    if(iRows < 3){
        iGroupSize = iRows;
    }else{
        iGroupSize = iRows * 2 - 2;
    }
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
