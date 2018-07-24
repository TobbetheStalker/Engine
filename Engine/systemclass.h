#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

/* PRE-PROCESSING DIRECTIVES */
#define WIN32_LEAN_AND_MEAN

/* MY CLASS INCLUDES */
#include "InputHandler.h"
#include "graphicsclass.h"


class SystemClass
{

public:
// Variables


// Functions
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:
// Varaibles
	LPCWSTR		m_applicationName;
	HINSTANCE	m_hinstance;
	HWND		m_hwnd;

	InputHandler*		m_Input;
	GraphicsClass*	m_Graphics;

// Functions
	bool Frame();
	void InitializeWindows(int& screenWidth, int& screenHeight);
	void ShutdownWindows();

};

static SystemClass* ApplicationHandle = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

#endif
