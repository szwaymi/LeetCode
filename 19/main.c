
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int main(void){
    
    unsigned int iValue[10] ={
        0, 1, 3, 4, 5, 6, 7, 8, 9,
    };
    
    struct ListNode *pmHead = NULL;
    unsigned int iCon;
    for(iCon = 0 ; iCon < sizeof(iValue) / sizeof(unsigned int) ; iCon++){
        
    }
    
    return 0;
}
