void test() {
	int x=2, y=3;

	while(x=y){   //expected warning
		x++;
	}
}