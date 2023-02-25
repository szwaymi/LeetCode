
#include "verify.h"

static char *gpcVRF_End;

static unsigned int rVRF_Search(char *pcString) {

    char *pcRight = gpcVRF_End;

    while (pcRight != pcString) {
        while (*pcRight != *pcString) {
            pcRight--;
        }
        if (pcRight == pcString) { return 0; }
        if (pcRight - pcString == 1) { return 1; }

        char *pcSR = pcRight - 1;
        char *pcSL = pcString + 1;
        while (pcSL < pcSR && *pcSL == *pcSR) {
            pcSL++;
            pcSR--;
        }
        if (*pcSL == *pcSR) {
            return (unsigned int)(pcRight - pcString);
        }
        pcRight--;
    }
    return 0;
}
char * rVRF_LongestPalindrome(char * pcString) {
    gpcVRF_End = pcString;
    while (*gpcVRF_End) {
        gpcVRF_End++;
    }
    gpcVRF_End--;

    unsigned int iMax = 0;
    char *pcMax = pcString;
    while (*pcString) {
        unsigned int iTemp;
        iTemp = rVRF_Search(pcString);
        if (iTemp > iMax) {
            iMax = iTemp;
            pcMax = pcString;
        }
        pcString++;
    }
    pcMax[iMax + 1] = 0;
    return pcMax;
}
