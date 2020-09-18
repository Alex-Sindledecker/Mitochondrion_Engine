#pragma once

#define _CRTDBG_MAP_ALLOC

#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>

#define ENGINE_ASSERT(expression) assert(expression)

#ifdef ENGINE_DEV
	//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#elif ENGINE_DEBUG
	//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else

#endif