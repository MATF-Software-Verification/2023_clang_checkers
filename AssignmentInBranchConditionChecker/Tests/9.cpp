void test(){
	int x = 1;
	int y=0;

	int a = (x==5,y+=x,y>5) ? 0:1;  //expected warning

	return;
}
