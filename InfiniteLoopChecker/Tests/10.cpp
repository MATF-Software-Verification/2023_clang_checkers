void test() {
  int x = 1;

  while(x){

    if(x){
        break; 
    }else{
        while(1){ // expected warning: infinite loop

        }
    }
  }

}