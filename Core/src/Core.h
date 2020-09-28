#pragma once

#ifdef ENGINE_EXPORT
	#define ENGINE_API __declspec(dllexport)
#elif ENGINE_IMPORT
	#define ENGINE_API __declspec(dllimport)
#endif

namespace Engine
{
	using u64 = unsigned long long;
	using u32 = unsigned int;
	using u16 = unsigned short;
	using u8 = unsigned char;
}