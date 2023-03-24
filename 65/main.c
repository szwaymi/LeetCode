
bool isNumber(char * pcNumber){
    unsigned char iState = 0;

    while(*pcNumber){
        switch(iState){
        case 0:
            if(*pcNumber == ' '){
                pcNumber++;
            }else if(*pcNumber == '+' || *pcNumber == '-'){
                pcNumber++;
                iState = 1;
            }else if(*pcNumber >= '0' && *pcNumber <= '9'){
                iState = 1;
            }else if(*pcNumber == '.'){
                pcNumber++;
                iState = 2;
            }else{
                return false;
            }
            break;
        case 1:
            if(*pcNumber >= '0' && *pcNumber <= '9'){
                pcNumber++;
            }else if(*pcNumber == '.'){
                pcNumber++;
                iState = 2;
            }else if(*pcNumber == 'e' || *pcNumber == 'E'){
                pcNumber++;
                iState = 5;
            }else{
                return false;
            }
            break;
        case 2:
        case 3:
            if(*pcNumber >= '0' && *pcNumber <= '9'){
                iState = 3;
                pcNumber++;
            }else if(*pcNumber == 'e' || *pcNumber == 'E'){
                pcNumber++;
                iState = 5;
            }else{
                return false;
            }
            break;
        case 5:
        case 6:
            if(*pcNumber >= '0' && *pcNumber <= '9'){
                pcNumber++;
                iState = 6;
            }else{
                return false;
            }
            break;
        }
    }
    switch(iState){
    case 2:return false;
    case 5:return false;
    }
    return true;
}
