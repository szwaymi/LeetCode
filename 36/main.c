
#include <stdlib.h>
#include <stdio.h>

#define bool unsigned char
#define true 1
#define false 0

bool isValidSudoku(char** pcBoard, int iRows, int* piCols){
    unsigned int iConX;
    unsigned int iConY;
    unsigned short iTotal;
    for(iConY = 0 ; iConY < 9 ; iConY++){
        iTotal = 0;
        for(iConX = 0 ; iConX < 9 ; iConX++){
            char cV = pcBoard[iConY][iConX];
            if(cV != '.'){
                unsigned char iShift = cV - '1';
                unsigned short iMask = 1 << iShift;
                if(((iTotal & iMask) ^ iMask) == 0){
                    return false;
                }
                iTotal |= iMask;
            }
        }
    }
    for(iConX = 0 ; iConX < 9 ; iConX++){
        iTotal = 0;
        for(iConY = 0 ; iConY < 9 ; iConY++){
            char cV = pcBoard[iConY][iConX];
            if(cV != '.'){
                unsigned char iShift = cV - '1';
                unsigned short iMask = 1 << iShift;
                if(((iTotal & iMask) ^ iMask) == 0){
                    return false;
                }
                iTotal |= iMask;
            }
        }
    }
    
    unsigned int iConZ;
    for(iConZ = 0 ; iConZ < 9 ; iConZ++){
        unsigned int iX = (iConZ % 3) * 3;
        unsigned int iY = (iConZ / 3) * 3;
        iTotal = 0;
        for(iConY = 0 ; iConY < 3 ; iConY++){
            for(iConX = 0 ; iConX < 3 ; iConX++){
                char cV = pcBoard[iConY + iY][iConX + iX];
                if(cV != '.'){
                    unsigned char iShift = cV - '1';
                    unsigned short iMask = 1 << iShift;
                    if(((iTotal & iMask) ^ iMask) == 0){
                        return false;
                    }
                    iTotal |= iMask;
                }
            }
        }
    }
    
    return true;
}

int main(void) {
	struct sInput {
		char cBoard[9][9];
	};
	struct sExp {
		bool bCheck;
	};
	struct sTest {
		unsigned int iNO;
		struct sInput mInput;
		struct sExp mExp;
	};
	struct sTest mTest[]=
	{
		{ 1, 
			{
				{
					{ '5','3','.','.','7','.','.','.','.' },
					{ '6','.','.','1','9','5','.','.','.' },
					{ '.','9','8','.','.','.','.','6','.' },
					{ '8','.','.','.','6','.','.','.','3' },
					{ '4','.','.','8','.','3','.','.','1' },
					{ '7','.','.','.','2','.','.','.','6' },
					{ '.','6','.','.','.','.','2','8','.' },
					{ '.','.','.','4','1','9','.','.','5' },
					{ '.','.','.','.','8','.','.','7','9' },
			    }
			}, true 
		},
		{ 2,
			{
				{
					{ '8','3','.','.','7','.','.','.','.' },
					{ '6','.','.','1','9','5','.','.','.' },
					{ '.','9','8','.','.','.','.','6','.' },
					{ '8','.','.','.','6','.','.','.','3' },
					{ '4','.','.','8','.','3','.','.','1' },
					{ '7','.','.','.','2','.','.','.','6' },
					{ '.','6','.','.','.','.','2','8','.' },
					{ '.','.','.','4','1','9','.','.','5' },
					{ '.','.','.','.','8','.','.','7','9' },
				}
			}, false
		},
        { 490,
            {
                {
                    {'.','.','.','9','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'.','.','3','.','.','.','.','.','1'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'1','.','.','.','.','.','3','.','.'},
                    {'.','.','.','.','2','.','6','.','.'},
                    {'.','9','.','.','.','.','.','7','.'},
                    {'.','.','.','.','.','.','.','.','.'},
                    {'8','.','.','8','.','.','.','.','.'}
                }
            }, false
        }
	};

	unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
	unsigned int iConTest;

	for (iConTest = 0; iConTest < iLengthTest; iConTest++) {
            printf("Test Case [%d]: ", mTest[iConTest].iNO);
            char **ppcBoard = (char **)malloc(sizeof(char *) * 9);
            int *piCols = (int *)malloc(sizeof(int) * 9);
            for(unsigned int iConRow = 0 ; iConRow < 9 ; iConRow++){
                ppcBoard[iConRow] = mTest[iConTest].mInput.cBoard[iConRow];
                piCols[iConRow] = 9;
            }
            bool bResult =
            isValidSudoku(ppcBoard, 9, piCols);
            printf("%d\n", bResult);
            free(piCols);
            free(ppcBoard);
	}
    return 0;

}

