

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sResult {
	char *pcParentheses;
	struct sResult *pmNext;
};

static struct {
	unsigned int iResults;
	unsigned int iNumber;
	struct sResult *pmResults;
}gmMeta;

static void rVRF_Generate(unsigned char iLeft, unsigned char iRight, char *pcParent) {

	if (gmMeta.iNumber == iLeft && iLeft == iRight) {
		struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
		pmResult->pmNext = gmMeta.pmResults;
		gmMeta.pmResults = pmResult;

		pmResult->pcParentheses = (char *)malloc(sizeof(char) * (gmMeta.iNumber * 2 + 1));
		strcpy(pmResult->pcParentheses, pcParent);

		gmMeta.iResults++;
		return;
	}
	char *pcParentheses = (char *)malloc(sizeof(char) * (iRight + iLeft + 2));
	if (iLeft < gmMeta.iNumber) {
		strcpy(pcParentheses, pcParent);
		strcat(pcParentheses, "(");
		rVRF_Generate(iLeft + 1, iRight, pcParentheses);
	}
	if (iLeft > iRight) {
		strcpy(pcParentheses, pcParent);
		strcat(pcParentheses, ")");
		rVRF_Generate(iLeft, iRight + 1, pcParentheses);
	}
	free(pcParentheses);
}
char ** rVRF_GenerateParenthesis(int iNumber, int* piResults) {
	char *pcTemp = { "" };
	gmMeta.iNumber = iNumber;
	gmMeta.pmResults = NULL;
	gmMeta.iResults = 0;
	rVRF_Generate(0, 0, pcTemp);
	*piResults = gmMeta.iResults;
	char **ppcResults = (char **)malloc(sizeof(char *) * gmMeta.iResults);
	struct sResult *pmResult;
	unsigned int iConResult = 0;
	while (gmMeta.pmResults) {
		pmResult = gmMeta.pmResults;
		gmMeta.pmResults = pmResult->pmNext;
		ppcResults[iConResult] = pmResult->pcParentheses;
		free(pmResult);
		iConResult++;
	}
	return ppcResults;
}