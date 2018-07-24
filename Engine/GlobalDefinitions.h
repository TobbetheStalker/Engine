#ifndef _GLOBAL_DEFINITIONS_H_
#define _GLOBAL_DEFINITIONS_H_

#include <windows.h>
#include <string>

/* Global variables and functions should be declared and defined in this file	*/
namespace globals
{
	//WINDOW
	static const LPCWSTR	APPLICATION_NAME	= L"Engine";
	
	static const int		WINDOWED_WIDTH		= 800;
	static const int		WINDOWED_HEIGHT		= 600;

	static bool				SHOW_CURSOR			= false;
	static bool				FULL_SCREEN			= false;
	static bool				VSYNC_ENABLED		= true;

	//VIEW
	static const float		SCREEN_DEPTH		= 1000.0f;
	static const float		SCREEN_NEAR			= 0.1f;

	//SHADERS
	static WCHAR*			PATH_VS				= L"../Engine/ColorVertexShader.hlsl";
	static WCHAR*			PATH_PS				= L"../Engine/ColorPixelShader.hlsl";
}
#endif
