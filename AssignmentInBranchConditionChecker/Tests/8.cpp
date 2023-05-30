void test() {
	int a=0, b=1;

	while(a=b,b+=1,a=7){      //expected warning: right operand of comma operator is assignment that is used as branch condition
		int x=a+b;
	}
}