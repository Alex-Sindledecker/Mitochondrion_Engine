#pragma once

#ifdef MITO_EXPORT
#define MITO_API __declspec(dllexport)
#else
#define MITO_API __declspec(dllimport)
#endif

#ifdef NDEBUG
#define MITO_ASSERT 
#else
#include <assert.h>
#define MITO_ASSERT(expr) assert(expr)
#endif