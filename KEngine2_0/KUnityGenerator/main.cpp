#include "KUnityParse.h"


int main()
{
	KUnityParse::instance()->init();

	KUnityParse::instance()->release();
	return 0;
}