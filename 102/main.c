
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define null 0x8000000000000000
typedef unsigned long long T_INT;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
int rTreeShowLevel(unsigned char iTarget, unsigned char iLevel, struct TreeNode *pmNode) {
	if (iLevel == iTarget) {
		if (pmNode) {
			printf("[%d] ", pmNode->val);
			return 1;
		}
		else {
			printf("[ ] ");
			return 0;
		}
	}
	int iResult = 0;
	if (pmNode) {
		iResult += rTreeShowLevel(iTarget, iLevel + 1, pmNode->left);
		iResult += rTreeShowLevel(iTarget, iLevel + 1, pmNode->right);
	}
	return iResult;
}
void rTreeShow(struct TreeNode *pmNode) {
	printf("\n");
	unsigned int iLevel = 0;
	while (rTreeShowLevel(iLevel, 0, pmNode)) {
		iLevel++;
		printf("\n");
	}
	printf("\n");
}
void rTreeBuild(struct TreeNode **ppmNode, unsigned int iLoc, T_INT *piSeries, unsigned int iLength) {
	if (iLoc == iLength) { return; }
	struct TreeNode *pmNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	pmNode->val = (int)piSeries[iLoc];
	pmNode->left = NULL;
	pmNode->right = NULL;
	unsigned int iLocTemp;
	iLocTemp = iLoc * 2 + 1;
	if (iLocTemp >= iLength || piSeries[iLocTemp] == null) {
		pmNode->left = NULL;
	}
	else {
		rTreeBuild(&pmNode->left, iLocTemp, piSeries, iLength);
	}
	iLocTemp = iLoc * 2 + 2;
	if (iLocTemp >= iLength || piSeries[iLocTemp] == null) {
		pmNode->right = NULL;
	}
	else {
		rTreeBuild(&pmNode->right, iLocTemp, piSeries, iLength);
	}
	*ppmNode = pmNode;
	return;
}

int** levelOrder(struct TreeNode* pmRoot, int* piResults, int** ppiCols) {
	//[Structures]
	struct sLink {
		struct TreeNode *pmNode;
		struct sLink *pmNext;
	};
	struct sCollection {
		struct sCollection *pmNext;
		struct sLink *pmLinks;
		int iLinks;
	};

	//Handle the Root
	struct sCollection *pmCollections = (struct sCollection *)malloc(sizeof(struct sCollection));
	pmCollections->pmLinks = (struct sLink *)malloc(sizeof(struct sLink));
	pmCollections->pmLinks->pmNext = NULL;
	pmCollections->pmLinks->pmNode = pmRoot;
	pmCollections->iLinks = 1;

	//Loop each level
	struct sCollection **ppmCollection = &pmCollections->pmNext;
	struct sCollection *pmCollection = pmCollections;
	int iLinks;
	int iResults = 1;
	do
	{
		struct sLink *pmLinks;
		struct sLink **ppmLink = &pmLinks;
		struct sLink *pmLink = pmCollection->pmLinks;
		iLinks = 0;
		while (pmLink) {
			if (pmLink->pmNode->left) {
				struct sLink *pmLinkNew = (struct sLink *)malloc(sizeof(struct sLink));
				pmLinkNew->pmNext = NULL;
				pmLinkNew->pmNode = pmLink->pmNode->left;
				*ppmLink = pmLinkNew;
				ppmLink = &pmLinkNew->pmNext;
				iLinks++;
			}
			if (pmLink->pmNode->right) {
				struct sLink *pmLinkNew = (struct sLink *)malloc(sizeof(struct sLink));
				pmLinkNew->pmNext = NULL;
				pmLinkNew->pmNode = pmLink->pmNode->right;
				*ppmLink = pmLinkNew;
				ppmLink = &pmLinkNew->pmNext;
				iLinks++;
			}
			pmLink = pmLink->pmNext;
		}
		if (iLinks) {
			struct sCollection *pmCollectionNew = (struct sCollection *)malloc(sizeof(struct sCollection));
			pmCollectionNew->pmLinks = pmLinks;
			pmCollectionNew->iLinks = iLinks;
			*ppmCollection = pmCollectionNew;
			ppmCollection = &pmCollectionNew->pmNext;
			pmCollection = pmCollectionNew;
			iResults++;
		}
	} while (iLinks);
	*ppmCollection = NULL;

	//Retrieve Data
	struct sCollection *pmCollectionTemp;
	unsigned int iCon = 0;
	int *piCols = (int *)malloc(sizeof(int) * iResults);
	int **ppiSeries = (int **)malloc(sizeof(int *) * iResults);
	pmCollection = pmCollections;
	while (pmCollection) {
		piCols[iCon] = pmCollection->iLinks;
		ppiSeries[iCon] = (int *)malloc(sizeof(int) * pmCollection->iLinks);
		unsigned int iConLink = 0;
		struct sLink *pmLink = pmCollection->pmLinks;
		while(pmLink) {
			struct sLink *pmLinkTemp;
			ppiSeries[iCon][iConLink] = pmLink->pmNode->val;
			pmLinkTemp = pmLink;
			pmLink = pmLink->pmNext;
			free(pmLinkTemp);
			iConLink++;
		}
		pmCollectionTemp = pmCollection;
		pmCollection = pmCollection->pmNext;
		free(pmCollectionTemp);
		iCon++;
	}

	*piResults = iResults;
	*ppiCols = piCols;
	return ppiSeries;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) T_INT iSeries_##N[] = {__VA_ARGS__}
#define M_TEST_EXP
#define M_TEST_COLLECTION(N) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(T_INT)},{NULL,NULL,0}}
    //  Structure
    struct sInput{
		T_INT *piSeries;
		int iLength;
    };
    struct sExp{
		int **ppiSeries;
		int *piCols;
		int iResults;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	//		#1
	M_TEST_INPUT(1, 3, 9, 20, null, null, 15, 7);
    struct sTest mTest[]={
		M_TEST_COLLECTION(1),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        //Result
		struct TreeNode *pmRoot;
		rTreeBuild(&pmRoot, 0, mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
		rTreeShow(pmRoot);
		int iResults;
		int *piCols;
		levelOrder(pmRoot, &iResults, &piCols);
        printf("Result = ");
        //Comparison
        int iTest = 1;
        if(iTest){
            printf("[PASS]");
        }else{
            printf("[FAIL]");
        }
        printf("\n");
        if(!iTest){
            break;
        }
    }
    printf("All Test Case : ");
    if(iConTest < iLengthTest){
        printf("[FAIL]");
    }else{
        printf("[PASS]");
    }
    printf("\n");
}
