

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
	char *pcParentheses;
}gmMeta;

static void rVRF_Generate(unsigned char iLeft, unsigned char iRight, char *pcParentheses) {

	if (gmMeta.iNumber == iLeft && iLeft == iRight) {
		*pcParentheses = 0;
		struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
		pmResult->pmNext = gmMeta.pmResults;
		gmMeta.pmResults = pmResult;

		pmResult->pcParentheses = (char *)malloc(sizeof(char) * (gmMeta.iNumber * 2 + 1));
		strcpy(pmResult->pcParentheses, gmMeta.pcParentheses);

		gmMeta.iResults++;
		return;
	}
	char *pcTemp;
	pcTemp = pcParentheses;
	if (iLeft < gmMeta.iNumber) {
		*pcTemp = '(';
		pcTemp++;
		rVRF_Generate(iLeft + 1, iRight, pcTemp);
	}
	pcTemp = pcParentheses;
	if (iLeft > iRight) {
		*pcTemp = ')';
		pcTemp++;
		rVRF_Generate(iLeft, iRight + 1, pcTemp);
	}
}
char ** rVRF_GenerateParenthesis(int iNumber, int* piResults) {
	gmMeta.pcParentheses = (char *)malloc(sizeof(char) * (iNumber * 2 + 1));;
	gmMeta.pcParentheses[0] = 0;
	gmMeta.iNumber = iNumber;
	gmMeta.pmResults = NULL;
	gmMeta.iResults = 0;
	rVRF_Generate(0, 0, gmMeta.pcParentheses);
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