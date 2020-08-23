#pragma once

#include <vector>
#include <string>
#include <functional>

#ifdef WIN32
#	ifdef API_DEV_MOD
#		define	ARCHMQ2_API __declspec(dllexport)
#	else
#		define	ARCHMQ2_API	__declspec(dllimport)
#	endif
#else
#	define ARCHMQ2_API
#endif

