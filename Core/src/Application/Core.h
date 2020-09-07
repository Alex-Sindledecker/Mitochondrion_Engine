#pragma once

#ifdef ENGINE_EXPORT

#define ENGINE_API __declspec(dllexport)

#elif ENGINE_IMPORT

#define ENGINE_API __declspec(dllimport)

#endif