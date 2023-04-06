
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct sCache {
	int iMethods;
	struct sCache *pmNext;
};

static struct
{
	struct sCache *pmLast;
	struct sCache *pmNow;
}gmCaches;

int rCheck(char *pcSource, char *pcProduction){
	if (*pcProduction == 0) {
		return 1;
	}
	gmCaches.pmNow = NULL;
	struct sCache **ppmCache = &gmCaches.pmNow;
	struct sCache *pmLast = NULL;
	int iMethods = 0;
	int iOffset = 0;
	while (*pcSource) {
		if (*pcSource == *pcProduction) {
			int iTemp;
			if (gmCaches.pmNow == NULL) {
				iTemp = rCheck(pcSource + 1, pcProduction + 1);
				pmLast = gmCaches.pmLast;
			}
			else {
				iTemp = gmCaches.pmNow->iMethods - iOffset;
			}
			struct sCache *pmCache = (struct sCache *)malloc(sizeof(struct sCache));
			pmCache->iMethods = iTemp;
			*ppmCache = pmCache;
			ppmCache = &pmCache->pmNext;
			iMethods += iTemp;
		}
		pcSource++;
		if (pmLast && *pcSource && *pcSource == *(pcProduction + 1)) {
			iOffset += pmLast->iMethods;
			pmLast = pmLast->pmNext;
		}
	}
	*ppmCache = NULL;
	while (gmCaches.pmLast) {
		pmLast = gmCaches.pmLast;
		gmCaches.pmLast = pmLast->pmNext;
		free(pmLast);
	}
	gmCaches.pmLast = gmCaches.pmNow;
    return iMethods;
}
int numDistinct(char * pcSource, char * pcProduction){
	gmCaches.pmLast = NULL;
	gmCaches.pmNow = NULL;
	int iMethods = rCheck(pcSource, pcProduction);
	struct sCache *pmLast;
	while (gmCaches.pmLast) {
		pmLast = gmCaches.pmLast;
		gmCaches.pmLast = pmLast->pmNext;
		free(pmLast);
	}
	return iMethods;
}
int main(void){
    //Test Data
    //  Macro
#define M_TEST_INPUT
#define M_TEST_EXP
#define M_TEST_COLLECTION(N, S, R, M) {N, {S, R}, {M}}
    //  Structure
    struct sInput{
        char *pcSource;
        char *pcResult;
    };
    struct sExp{
        int iMethods;
    };
    struct sTest{
        unsigned int iNO;
        struct sInput mInput;
        struct sExp mExp;
    };
    //  Data
    struct sTest mTest[]={
        M_TEST_COLLECTION(61, "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo", "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys", 543744000),
        M_TEST_COLLECTION(54, "adbdadeecadeadeccaeaabdabdbcdabddddabcaaadbabaaedeeddeaeebcdeabcaaaeeaeeabcddcebddebeebedaecccbdcbcedbdaeaedcdebeecdaaedaacadbdccabddaddacdddc", "bcddceeeebecbc", 700531452),
        M_TEST_COLLECTION(2, "babgbag", "bag", 5),
        M_TEST_COLLECTION(1, "rabbbit", "rabbit", 3),
    };
    unsigned int iLengthTest = sizeof(mTest) / sizeof(struct sTest);
    unsigned int iConTest;
    for(iConTest = 0 ; iConTest < iLengthTest ; iConTest++){
        printf("Test Case [%d], ", mTest[iConTest].iNO);
        //Expectaion
        printf("Expecation = %d, ", mTest[iConTest].mExp.iMethods);
        //Result
        printf("Result = ");
        int iResult =
        numDistinct(mTest[iConTest].mInput.pcSource, mTest[iConTest].mInput.pcResult);
        printf("%d ", iResult);
        //Comparison
        int iTest = iResult == mTest[iConTest].mExp.iMethods;
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
