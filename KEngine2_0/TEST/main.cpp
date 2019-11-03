#include <iostream>
int main()
{
	short arr[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int * p = (int *)arr;
	p += 2;
	printf("%d\n", *(short*)p);
	return 0;
}
