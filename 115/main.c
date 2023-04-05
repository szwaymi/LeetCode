
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static struct{
    int iResult;
    int iSource;
}gmLength;

int rCheck(char *pcSource, char *pcResult, int iLoc, int iLeft){
    if(gmLength.iSource - iLoc < iLeft){
        return 0;
    }
    if(*pcResult == 0){
        return 1;
    }
    int iMethod = 0;
    char iRepeat = 0;
    int iLast;
    while(*pcSource && (gmLength.iSource - iLoc) >= iLeft){
        if(*pcSource == *pcResult){
            if(iRepeat == 0){
                iLast = rCheck(pcSource + 1, pcResult + 1, iLoc, iLeft);
                iMethod += iLast;
            }else{
                iMethod += iLast;
            }
            iRepeat = 1;
        }
        pcSource++;
        iLoc++;
        if(*pcSource == *(pcResult + 1)){
            iRepeat = 0;
        }
    }
    return iMethod;
}
int numDistinct(char * pcSource, char * pcResult){
    gmLength.iResult = (int)strlen(pcResult);
    gmLength.iSource = (int)strlen(pcSource);
    return rCheck(pcSource, pcResult, 0, gmLength.iResult);
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
        M_TEST_COLLECTION(61, "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo", "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys", 1024),
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
