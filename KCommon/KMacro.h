#pragma once
#include <assert.h>



#define RELEASE_PTR(PTR) \
{\
	if (nullptr != PTR)\
	{\
		delete PTR;\
		PTR = nullptr;\
	}\
}

// 무조건 터진다.
#define KASSERT assert(false)
#define KNAMING 32
#define KHASH 64
#define KBUFSIZE 1024
#define KHALFBUFSIZE ( KBUFSIZE / 2 )
#define KPATHBUFSIZE 128
#define WM_SOCKET (WM_USER+1)