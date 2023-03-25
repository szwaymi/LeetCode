
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

bool isNumber(char * pcNumber){
    unsigned int iState = 0;

    while(*pcNumber){
        switch(iState){
        case 0x0:	//Sign Mark
            if(*pcNumber == ' '){
                pcNumber++;
            }else if(*pcNumber == '+' || *pcNumber == '-'){
				iState = 0x100;
				pcNumber++;
            }else if(*pcNumber >= '0' && *pcNumber <= '9'){
                iState = 0x100;
            }else if(*pcNumber == '.'){
                pcNumber++;
                iState = 0x210;
            }else{
                return false;
            }
            break;
        case 0x100:	//Integer Part
		case 0x110:
            if(*pcNumber >= '0' && *pcNumber <= '9'){
				iState = 0x110;
                pcNumber++;
            }else if(*pcNumber == '.'){
                pcNumber++;
				if (iState == 0x110) {
					iState = 0x200;
				}
				else {
					iState = 0x210;
				}
            }else if(*pcNumber == 'e' || *pcNumber == 'E'){
				if (iState != 0x110) {
					return false;
				}
                pcNumber++;
                iState = 0x300;
            }else{
                return false;
            }
            break;
		//Decimal Part
        case 0x200:	//Complete
		case 0x210:	//Half
		case 0x220:
            if(*pcNumber >= '0' && *pcNumber <= '9'){
				iState = 0x220;
                pcNumber++;
            }else if(*pcNumber == 'e' || *pcNumber == 'E'){
				if (iState == 0x210  ) { return false; }
                pcNumber++;
                iState = 0x300;
            }else{
                return false;
            }
            break;
        case 0x300:	//Exponation Part
			if (*pcNumber == '+' || *pcNumber == '-') {
				iState = 0x400;
				pcNumber++;
			}else if(*pcNumber >= '0' && *pcNumber <= '9'){
				iState = 0x410;
            }else{
                return false;
            }
            break;
		case 0x400:
		case 0x410:
			if (*pcNumber >= '0' && *pcNumber <= '9') {
				iState = 0x410;
				pcNumber++;
			}
			else {
				return false;
			}
			break;
        }
    }
	switch (iState) {
	case 0x100:
	case 0x210:
	case 0x300:
	case 0x400:
		return false;
	}
    return true;
}

int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, S, R) {N, {S}, {R}}
    //  Structure
    struct sInput{
        char *pcNumber;
    };
    struct sExp{
        bool fResult;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    struct sTest mTest[]={
		M_TEST_COLLECTION(1490,"+", false),
		M_TEST_COLLECTION(1487,"4e+", false),
		M_TEST_COLLECTION(1472,"005047e+6", true),
		M_TEST_COLLECTION(1450, "46.e3", true),
		M_TEST_COLLECTION(1366, ".0e7", true),
		M_TEST_COLLECTION(1364, "+E3", false),
		M_TEST_COLLECTION(1362, "+.", false),
		M_TEST_COLLECTION(1463, ".e1", false),
		M_TEST_COLLECTION(1411, "0e", false),
		M_TEST_COLLECTION(1360, ".1", true),
		M_TEST_COLLECTION(3, ".", false),
		M_TEST_COLLECTION(2, "e", false),
        M_TEST_COLLECTION(1, "0", true),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = ");
        if(mTest[iConTest].mExp.fResult){printf("TRUE");}
        else{printf("FALSE");}
        printf(" ");
        //Result
        printf("Result = ");
        bool fResult =
        isNumber(mTest[iConTest].mInput.pcNumber);
        if(fResult){printf("TRUE");}
        else{printf("FALSE");}
        printf(" ");
        //Comparison
        int iTest = mTest[iConTest].mExp.fResult == fResult;
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

