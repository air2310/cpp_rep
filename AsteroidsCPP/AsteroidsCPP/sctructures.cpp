
//typedef struct
//{
//	int H;
//	int D;
//} Pointstruct;

struct MyStruct
{
	int H;
	int D;
} ms;

MyStruct structures() {
	int a, b;
	
	a = 10;
	b = 20;
	ms.H = a;
	ms.D = b;

	return(ms);
}