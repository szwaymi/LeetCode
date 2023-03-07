
#include <stdio.h>

int strStr(char * pcSearch, char * pcTarget){

    char *pcPointer;
    char *pcSrc;
    char *pcDes;
    pcPointer = pcSearch;
    do{
        pcSrc = pcPointer;
        pcDes = pcTarget;
        while(*pcDes && *pcSrc == *pcDes){
            pcDes++;
            pcSrc++;
        }
        if(*pcDes == 0){
            break;
        }
        pcPointer++;
    }while(*pcPointer);

    if(*pcPointer == 0){
        return -1;
    }
    printf("%d", pcSrc - pcSearch - (pcDes - pcTarget));

    return (int)(pcSrc - (pcDes - pcTarget));
}

int main(void){
    char *pcSearch = "sadbutsad";
    char *pcTarget = "sad";
    
    int iResult;
    iResult = strStr(pcSearch, pcTarget);

}
