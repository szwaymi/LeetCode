
#include <stdio.h>

int main(void) {

#define M_TEST_DATA_IN(N, ...) int iSeries_##N[]={ __VA_ARGS__};
	struct sInput {
		int *piSeries;
		unsigned int iSize;
	};
	struct sTest {
		unsigned int iNO;
		int iOutput;
		struct sInput mInput;
	};
	M_TEST_DATA_IN(0, -1, 2, 1, -4);


}