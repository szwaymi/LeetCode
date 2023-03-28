
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
			rTreeCheck(pmNode->right, iLocTemp, piSeries, iLength);
		if (iResult == 0) { return 0; }
	}

	return 1;
}
int rCheck(struct TreeNode *pmNode) {
#define M_SWAP(A, B) pmNodeA=A;pmNodeB=B;goto A_CHANGE
	struct TreeNode *pmTop = pmNode;
	struct TreeNode *pmLeft = pmNode->left;
	struct TreeNode *pmRight = pmNode->right;
	struct TreeNode *pmNodeA;
	struct TreeNode *pmNodeB;
	if ((pmLeft && pmRight) && pmTop->val < pmLeft->val && pmTop->val > pmRight->val) {
		M_SWAP(pmLeft, pmRight);
	}
	if (pmLeft) {
		if (pmLeft->left && pmLeft->left->val > pmLeft->val) {
			if (pmLeft->val > pmTop->val) {
				M_SWAP(pmLeft->left, pmTop);
			}
			else {
				M_SWAP(pmLeft->left, pmLeft);
			}
		}
		else if (pmLeft->right) {
			if (pmLeft->val > pmLeft->right->val)
			{
				if (pmTop->val < pmLeft->val) {
					M_SWAP(pmLeft, pmTop);
				}
				else {
					M_SWAP(pmLeft->right, pmLeft);
				}
			}
			else if (pmTop->val < pmLeft->right->val) {
				M_SWAP(pmLeft->right, pmTop);
			}
		}
		else if (pmLeft->val > pmTop->val)
		{
			M_SWAP(pmLeft, pmTop);
		}
	}
	if (pmRight) {
		if (pmRight->right && pmRight->val > pmRight->right->val) {
			if (pmTop->val > pmRight->val) {
				M_SWAP(pmRight->right, pmTop);
			}
			else {
				M_SWAP(pmRight->right, pmRight);
			}
		}
		else if (pmRight->left)
		{
			if (pmRight->val < pmRight->left->val) {
				if (pmTop->val > pmRight->val) {
					M_SWAP(pmRight, pmTop);
				}
				else {
					M_SWAP(pmRight, pmRight->left);
				}
			}
			else if (pmTop->val > pmRight->left->val) {
				M_SWAP(pmRight->left, pmTop);
			}
		}
		else if (pmTop->val > pmRight->val) {
			M_SWAP(pmRight, pmTop);
		}
	}
	return 0;

A_CHANGE:
	{
		T_INT iTemp = pmNodeA->val;
		pmNodeA->val = pmNodeB->val;
		pmNodeB->val = iTemp;
	}
	return 1;
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
int main(void) {
	//Test Data
	//  Macro
#define M_TEST_INPUT(N, ...) T_INT iSeries_##N[] = {__VA_ARGS__};
#define M_TEST_EXP(N, ...) T_INT iExp_##N[] = {__VA_ARGS__};
#define M_TEST_COLLECTION(N) {N, {iSeries_##N, sizeof(iSeries_##N) / sizeof(T_INT)},{iExp_##N}}
	//  Structure
	struct sInput {
		T_INT *piSeries;
		unsigned int iLength;
	};
	struct sExp {
		T_INT *piSeries;
	};
	struct sTest {
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
	//		#1070
	M_TEST_INPUT(1070, 146, 71, -13, 55, null, 231, 399, 321, null, null, null, null, null, -33);
	M_TEST_EXP(1070, 146, 71, 321, 55, null, 231, 399, -13, null, null, null, null, null, -33);
	struct sTest mTest[] = {
		M_TEST_COLLECTION(1070),
		M_TEST_COLLECTION(458),
		M_TEST_COLLECTION(2),
		M_TEST_COLLECTION(1),
	};
	unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
	unsigned int iConTest;
	for (iConTest = 0; iConTest < iLengthTest; iConTest++) {
		printf("Test Case [%d], ", mTest[iConTest].iNO);
		//Expectaion
		printf("Expecation = ");
		//Result
		struct TreeNode *pmRoot;
		rTreeBuild(&pmRoot, 0, mTest[iConTest].mInput.piSeries, mTest[iConTest].mInput.iLength);
		rTreeShow(pmRoot);
		recoverTree(pmRoot);
		rTreeShow(pmRoot);
		printf("Result = ");
		//Comparison
		int iTest = rTreeCheck(pmRoot, 0, mTest[iConTest].mExp.piSeries, mTest[iConTest].mInput.iLength);
		if (iTest) {
			printf("[PASS]");
		}
		else {
			printf("[FAIL]");
		}
		printf("\n");
		if (!iTest) {
			break;
		}
	}
	printf("All Test Case : ");
	if (iConTest < iLengthTest) {
		printf("[FAIL]");
	}
	else {
		printf("[PASS]");
	}
	printf("\n");
}
