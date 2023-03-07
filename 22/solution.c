
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sCache {
	unsigned int iCombinations;
	char **ppcParentheses;
};

static struct {
	struct sCache *pmCaches;
}gmMeta;

static void rMSL_Generate(unsigned int iNumber) {
	unsigned int iResults = 0;
	unsigned int iDebug = 0;
	struct sResult {
		unsigned int iNumber;
		char **ppcParentheeses;
		struct sResult *pmNext;
	};
	struct sResult *pmResults = NULL;
	unsigned int iConNumber;
	for (iConNumber = iNumber; iConNumber > 0; iConNumber--) {
		unsigned char iLeft = iNumber - iConNumber;
		struct sChunk {
			unsigned int iLeft;
			unsigned int iAcc;
			unsigned int iComb;
		};
		struct sChunk *pmChunks = (struct sChunk *)malloc(sizeof(struct sChunk) * iConNumber);
		unsigned int iConChunks;
		for (iConChunks = 1; iConChunks < iConNumber; iConChunks++) {
			pmChunks[iConChunks].iLeft = 0;
		}
		pmChunks[0].iLeft = iLeft - 1;
		do {
			printf("%d,%d ", iNumber, iLeft);
			if (iNumber == 7 && iLeft == 6) {
				printf("Q");
			}
			unsigned int iSum = 0;
			pmChunks[0].iLeft++;
			for (iConChunks = 0; iConChunks < iConNumber - 1; iConChunks++) {
				if (pmChunks[iConChunks].iLeft > iLeft) {
					pmChunks[iConChunks].iLeft = 0;
					pmChunks[iConChunks + 1].iLeft++;
				}
				iSum += pmChunks[iConChunks].iLeft;
			}
			iSum += pmChunks[iConChunks].iLeft;
			if (iSum == iLeft) {
				unsigned int iCombinations = 1;
				for (iConChunks = 0; iConChunks < iConNumber; iConChunks++) {
					if (gmMeta.pmCaches[pmChunks[iConChunks].iLeft].iCombinations == 0xFFFFFFFF){
						rMSL_Generate(pmChunks[iConChunks].iLeft);
					}
					iCombinations *= gmMeta.pmCaches[pmChunks[iConChunks].iLeft].iCombinations;
					pmChunks[iConChunks].iAcc = 0;
					pmChunks[iConChunks].iComb = gmMeta.pmCaches[pmChunks[iConChunks].iLeft].iCombinations;
				}

				struct sResult *pmResult = (struct sResult *)malloc(sizeof(struct sResult));
				pmResult->pmNext = pmResults;
				pmResults = pmResult;
				pmResult->iNumber = iCombinations;
				pmResult->ppcParentheeses = (char **)malloc(sizeof(char *) * iCombinations);
				iDebug += iCombinations;
				unsigned int iConCombo;
				for (iConCombo = 0; iConCombo < iCombinations; iConCombo++) {
					char *pcParentheses;
					unsigned int iSize = iLeft * 2 + iConNumber * 2 + 1;
					pcParentheses = (char *)malloc(sizeof(char) * (iSize));
					pcParentheses[0] = 0;
					for (iConChunks = 0; iConChunks < iConNumber; iConChunks++) {
						strcat(pcParentheses, "(");
						strcat(pcParentheses, gmMeta.pmCaches[pmChunks[iConChunks].iLeft].ppcParentheses[pmChunks[iConChunks].iAcc]);
						strcat(pcParentheses, ")");
					}
					if (strcmp(pcParentheses, "(((((((())))))))") == 0) {
						printf("A");
					}
					pmResult->ppcParentheeses[iConCombo] = pcParentheses;
					pmChunks[0].iAcc++;
					for (iConChunks = 0; iConChunks < iConNumber - 1; iConChunks++) {
						if (pmChunks[iConChunks].iAcc >= pmChunks[iConChunks].iComb) {
							pmChunks[iConChunks].iAcc = 0;
							pmChunks[iConChunks + 1].iAcc++;
						}else{
							break;
						}
					}
					if (pmChunks[iConChunks].iAcc >= pmChunks[iConChunks].iComb) {
						pmChunks[iConChunks].iAcc = 0;
					}
					iResults++;
				}
			}
		} while (pmChunks[iConNumber - 1].iLeft != iLeft);
		free(pmChunks);
	}

	char **ppcResults = (char **)malloc(sizeof(char *) * iResults);
	unsigned int iTemp = 0;
	unsigned int iConResults = 0;
	while (pmResults) {
		struct sResult *pmResult = pmResults;
		pmResults = pmResults->pmNext;
		iTemp += pmResult->iNumber;
		unsigned int iConT;
		for (iConT = 0; iConT < pmResult->iNumber; iConT++) {
			ppcResults[iConResults] = pmResult->ppcParentheeses[iConT];
			iConResults++;
		}

		free(pmResult->ppcParentheeses);
		free(pmResult);
	}

	gmMeta.pmCaches[iNumber].iCombinations = iResults;
	gmMeta.pmCaches[iNumber].ppcParentheses = ppcResults;
}

char ** rMSL_GenerateParenthesis(int iNumber, int* piResults){
	static char *pcTemp[] = { "" };
	unsigned int iCon;
	gmMeta.pmCaches = (struct sCache *)malloc(sizeof(struct sCache) * (iNumber + 1));
	gmMeta.pmCaches[0].iCombinations = 1;
	gmMeta.pmCaches[0].ppcParentheses = pcTemp;
	for (iCon = 1; iCon < iNumber; iCon++) {
		gmMeta.pmCaches[iCon].iCombinations = 0xFFFFFFFF;
	}

	rMSL_Generate(iNumber);

	for (iCon = 1; iCon < iNumber - 1; iCon++) {
		unsigned int iConC;
		for (iConC = 0; iConC < gmMeta.pmCaches[iCon].iCombinations; iConC++) {
			free(gmMeta.pmCaches[iCon].ppcParentheses[iConC]);
		}
		free(gmMeta.pmCaches[iCon].ppcParentheses);
	}

	char **ppcResult = gmMeta.pmCaches[iNumber].ppcParentheses;
	*piResults = gmMeta.pmCaches[iNumber].iCombinations;

	free(gmMeta.pmCaches);

	return ppcResult;
}
