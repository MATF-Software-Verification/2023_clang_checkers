
void test(){

    for(; 1;){
        int y = 1; //expected warning: infinte loop without break or return
    }
 
    return ; //expected warning: unreachable return statement preceded by infinite loop
}

