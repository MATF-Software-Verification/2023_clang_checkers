void test() {
	int n=10;
	int x=0;

	for(int i=0; i<n, n+=i ; ++i){      //expected warning: right operand of comma operator is assignment that is used as branch condition 
		x++;
	}
}