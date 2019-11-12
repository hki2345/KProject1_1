#include <iostream>


class A
{
public:
	A();
	~A();

private:
	int a;

public:
	int b;
};

class B : public A
{
private:
	int c;

public:
	B();
	~B();
};


int main()
{
	sizeof(A);
	sizeof(B);


	short arr[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int * p = (int *)arr;
	p += 2;
	printf("%d\n", *(short*)p);
	return 0;
}
