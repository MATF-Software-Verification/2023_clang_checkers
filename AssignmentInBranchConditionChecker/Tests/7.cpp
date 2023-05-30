void test() {
	int a=0, b=1;

	while(a=b,b+=1,a==b){      // no warnings expected 
		int x=a+b;
	}
}