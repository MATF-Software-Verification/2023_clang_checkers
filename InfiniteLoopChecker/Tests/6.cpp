int test(){

    int x = 1;
    while(2){     //expected warning: infinite loop without break or return

    }

    while(1){
        x++;
        if(x>5){
            break;
        }
    }

    return 1;
}
