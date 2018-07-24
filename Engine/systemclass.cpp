#include "systemclass.h"

SystemClass::SystemClass()
{
	this->m_Input		= nullptr;
	this->m_Graphics	= nullptr;

}

SystemClass::SystemClass(const SystemClass &)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{	
	int screenWidth, screenHeight;
	bool result;

	screenWidth		= 0;
	screenHeight	= 0;

	// Init the windows API
	this->InitializeWindows(screenWidth, screenHeight);

	// INPUT
	this->m_Input = new InputHandler;
	if (!this->m_Input)
	{
		return false;
	}

	this->m_Input->Initialize(this->m_hinstance, this->m_hwnd, screenWidth, screenHeight);



	// GRAPHICS
	this->m_Graphics = new GraphicsClass;
	if (!this->m_Graphics)
	{
		return false;
	}

	result = this->m_Graphics->Initialize(screenWidth, screenHeight, this->m_hwnd);
	if (!result)
	{
		return false;
	}



	return true;
}

void SystemClass::Shutdown()
{
	if (this->m_Graphics)
	{
		this->m_Graphics->Shutdown();
		delete this->m_Graphics;
		this->m_Graphics = nullptr;
	}

	if (this->m_Input)
	{
		delete this->m_Input;
		this->m_Input = nullptr;
	}

	this->ShutdownWindows();

	return;
}

void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Init  message structure.
	ZeroMemory(&msg, sizeof(MSG));

	//Run.
	done = false;
	while (!done)
	{
		// Handle windows messgaes.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signlas to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Do frame processing.
			result = this->Frame();
			if (!result)
			{
				done = true;
			}
		}
	}

	return;
}

LRESULT SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if a key has been pressed or released on the keyboard.
		case WM_KEYDOWN:
		{
			this->m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			this->m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

bool SystemClass::Frame()
{
	bool result;

	// Check if the user pressed escape.
	if (this->m_Input->isKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// Do the frame processing for graphics.
	result = this->m_Graphics->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::InitializeWindows(int & screenWidth, int & screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	//Get an external pointer to this object.
	ApplicationHandle = this;

	//Get the instance of this application.
	this->m_hinstance = GetModuleHandle(NULL);

	//Give the application a name.
	this->m_applicationName = globals::APPLICATION_NAME;

	//Window default settings.
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= this->m_hinstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm			= wc.hIcon;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= this->m_applicationName;
	wc.cbSize			= sizeof(WNDCLASSEX);

	//Register the window class
	RegisterClassEx(&wc);

	//Determine the resolution of the clients desktop screen.
	screenWidth		= GetSystemMetrics(SM_CXSCREEN);
	screenHeight	= GetSystemMetrics(SM_CYSCREEN);

	//Setup the screen settings
	if (globals::FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to windowed resolution.
		screenWidth		= globals::WINDOWED_WIDTH;
		screenHeight	= globals::WINDOWED_HEIGHT;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//Create the window
	this->m_hwnd = CreateWindowEx(WS_EX_APPWINDOW
									,this->m_applicationName
									,this->m_applicationName
									,WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP
									,posX, posY
									,screenWidth, screenHeight
									,NULL
									,NULL
									,this->m_hinstance
									,NULL);

	// Bring the window up on the sxreen and set it as main focus.
	ShowWindow(this->m_hwnd, SW_SHOW);
	SetForegroundWindow(this->m_hwnd);
	SetFocus(this->m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(globals::SHOW_CURSOR);

	return;
}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (globals::FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}
