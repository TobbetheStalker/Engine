#include "systemclass.h"

#include <crtdbg.h>
#include <shellapi.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SystemClass*	System;
	bool			result;
	LPWSTR*			szArgList;
	int				argCount;

	//Arguments
	szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
	if (szArgList == NULL)
	{
		//Could not parse the command line.
	}
	else
	{
		//Loop the command line
	}

	// Create the system object.
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	// Initialize and run the system object.
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}