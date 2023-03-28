
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define null 0x8000000000000000
typedef long long T_INT;

struct TreeNode {
	T_INT val;
	struct TreeNode *left;
	struct TreeNode *right;
};

void rTreeBuild(struct TreeNode **ppmNode, unsigned int iLoc, T_INT *piSeries, unsigned int iLength) {
	if (iLoc == iLength) { return; }
	struct TreeNode *pmNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	pmNode->val = piSeries[iLoc];
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

int rTreeCheck(struct TreeNode *pmNode, unsigned int iLoc, T_INT *piSeries, unsigned int iLength) {
	if (iLoc == iLength) { return 0; }
	if (pmNode->val != piSeries[iLoc]) {
		return 0;
	}
	unsigned int iLocTemp;
	iLocTemp = iLoc * 2 + 1;
	if (iLocTemp < iLength && piSeries[iLocTemp] != null) {
		int iResult =
		rTreeCheck(pmNode->left, iLocTemp, piSeries, iLength);
		if (iResult == 0) { return 0; }
	}
	iLocTemp = iLoc * 2 + 2;
	if (iLocTemp < iLength && piSeries[iLocTemp] != null) {
		int iResult =
		rTreeCheck(&pmNode->right, iLocTemp, piSeries, iLength);
		if (iResult == 0) { return 0; }
	}

	return 1;
}
typedef int T_INT;

int rCheck(struct TreeNode *pmNode) {
	struct TreeNode *pmNodeA;
	struct TreeNode *pmNodeB = NULL;
	pmNodeA = pmNode;
	if (pmNode->left) {
		if (pmNodeA->val < pmNode->left->val) {
			pmNodeB = pmNode->left;
		}
		else {
			if (pmNode->left->left) {
				T_INT iTemp;
				iTemp = pmNode->left->left->val;
				if (pmNodeA->val < iTemp) {
					pmNodeB = pmNode->left->left;
				}
				else if (pmNode->left->val < iTemp) {
					pmNodeA = pmNode->left;
					pmNodeB = pmNode->left->left;
				}
			}
			if (pmNodeB == NULL && pmNode->left->right) {
				T_INT iTemp;
				iTemp = pmNode->left->right->val;
				if (pmNodeA->val < iTemp) {
					pmNodeB = pmNode->left->right;
				}
				else if (pmNode->left->val < iTemp) {
					pmNodeA = pmNode->left;
					pmNodeB = pmNode->left->right;
				}
			}
		}
	}
	if (pmNodeB) {
		T_INT iTemp = pmNodeA->val;
		pmNode->val = pmNodeB->val;
		pmNodeB->val = iTemp;
		return 1;
	}

	if (pmNode->right) {
		if (pmNodeA->val > pmNode->right->val) {
			pmNodeB = pmNode->right;
		}
		else {
			if (pmNode->right->left) {
				int iTemp;
				iTemp = pmNode->right->left->val;
				if (pmNodeA->val > iTemp) {
					pmNodeB = pmNode->right->left;
				}
				else if (pmNode->right->val < iTemp) {
					pmNodeA = pmNode->right;
					pmNodeB = pmNode->right->left;
				}
			}
			if (pmNodeB == NULL && pmNode->right->right) {
				int iTemp;
				iTemp = pmNode->right->right->val;
				if (pmNodeA->val > iTemp) {
					pmNodeB = pmNode->right->right;
				}
				else if (pmNode->right->val > iTemp) {
					pmNodeA = pmNode->right;
					pmNodeB = pmNode->right->right;
				}
			}
		}
	}
	if (pmNodeB) {
		int iTemp = pmNodeA->val;
		pmNode->val = pmNodeB->val;
		pmNodeB->val = iTemp;
		return 1;
	}


	return 0;
}
void rTraverse(struct TreeNode *pmNode) {
	if (rCheck(pmNode)) {
		return;
	}
	if (pmNode->left) {
		rTraverse(pmNode->left);
	}
	if (pmNode->right) {
		rTraverse(pmNode->right);
	}
}
void recoverTree(struct TreeNode* pmRoot) {
	rTraverse(pmRoot);
}
int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT(N, ...) T_INT iSeries_##N[] = {__VA_ARGS__};
#define M_TEST_EXP(N, ...) T_INT iExp_##N[] = {__VA_ARGS__};
#define M_TEST_COLLECTION(N) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(T_INT)},{iExp_##N}}
    //  Structure
    struct sInput{
		T_INT *piSeries;
		unsigned int iLength;
    };
    struct sExp{
		T_INT *piSeries;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
	//		#1
	M_TEST_INPUT(1, 1, 3, null, null, 2);
	M_TEST_EXP(1, 3, 1, null, null, 2);
	//		#2
	M_TEST_INPUT(2, 3, 1, 4, null, null, 2);
	M_TEST_EXP(2, 2, 1, 4, null, null, 3);
	//		#458
	M_TEST_INPUT(458, 2, 3, 1);
	M_TEST_EXP(458, 2, 1, 3);
    struct sTest mTest[]={
		M_TEST_COLLECTION(2),
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
		recoverTree(pmRoot);
        printf("Result = ");
        //Comparison
        int iTest = rTreeCheck(pmRoot, 0, mTest[iConTest].mExp.piSeries, mTest[iConTest].mInput.iLength);
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
