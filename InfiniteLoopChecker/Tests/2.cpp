void test() {
  int x = 1;


  while(x){

    if(0){
        break; // expected warning: unreachable break in loop
    }
  }

}