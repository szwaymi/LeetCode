
#include <stdio.h>

#define bool unsigned char
#define true 1
#define false 0

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {

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
		}
	};

	unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
	unsigned int iConTest;

	for (iConTest = 0; iConTest < iLengthTest; iConTest++) {
		
	}

}

