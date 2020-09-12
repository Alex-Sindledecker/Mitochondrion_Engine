#pragma once

#define _CRTDBG_MAP_ALLOC

#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>

#define ENGINE_ASSERT(expression) assert(expression)

#ifdef _DEV
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#elif _DEBUG
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else

#endif