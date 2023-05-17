void test() {
	int x=2, y=3;

	while(x=y,y<5){      //no warnings expected
		x++;
	}
}