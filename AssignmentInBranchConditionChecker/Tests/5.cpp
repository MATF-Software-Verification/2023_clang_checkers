void test() {
	int x=2, y=3;

	while(x==y,y<5){      //expected warning: left operand of comma operator produces no effect 
		x++;
	}
}