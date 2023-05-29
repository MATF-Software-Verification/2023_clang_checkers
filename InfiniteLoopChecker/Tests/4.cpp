void test(){
    int x=5;
    for(; x > 2;){

        if(0){
            return;  //expected warning: unreachable return in loop
        }
    }

    return ;
}