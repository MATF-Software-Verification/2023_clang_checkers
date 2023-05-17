int test(){

    int x = 1;
    while(2){

    }

    while(1){    //expected warning: infinite loop without break or return
        x++;
    }

    return 1;
}
