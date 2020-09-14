#pragma once

#ifdef ENGINE_EXPORT
	#define ENGINE_API __declspec(dllexport)
#elif ENGINE_IMPORT
	#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine
{
	typedef unsigned long long u64;
	typedef unsigned int u32;
	typedef unsigned short u16;
	typedef unsigned char u8;
}