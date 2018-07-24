#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	this->m_D3D = nullptr;
	this->m_Camera = nullptr;
	this->m_Model = nullptr;
	this->m_ColorShader = nullptr;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	this->m_D3D = new D3DClass;
	if (!this->m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = this->m_D3D->Initialize(	screenWidth, screenHeight, globals::VSYNC_ENABLED, hwnd
								,globals::FULL_SCREEN, globals::SCREEN_DEPTH, globals::SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}


	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	this->m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the model object.
	this->m_Model = new ModelClass;
	if (!this->m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = this->m_Model->Initialize(this->m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	this->m_ColorShader = new ColorShaderClass;
	if (!this->m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = this->m_ColorShader->Initialize(this->m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if (this->m_ColorShader)
	{
		this->m_ColorShader->Shutdown();
		delete this->m_ColorShader;
		this->m_ColorShader = 0;
	}

	// Release the model object.
	if (this->m_Model)
	{
		this->m_Model->Shutdown();
		delete this->m_Model;
		this->m_Model = 0;
	}

	// Release the camera object.
	if (this->m_Camera)
	{
		delete this->m_Camera;
		this->m_Camera = 0;
	}

	if (this->m_D3D)
	{
		this->m_D3D->Shutdown();
		delete this->m_D3D;
		this->m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;


	// Render the graphics scene.
	result = this->Render();
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	DirectX::XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	this->m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	this->m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	this->m_Camera->GetViewMatrix(viewMatrix);
	this->m_D3D->GetWorldMatrix(worldMatrix);
	this->m_D3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	this->m_Model->Render(this->m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	result = this->m_ColorShader->Render(this->m_D3D->GetDeviceContext(), this->m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}


	// Present the rendered scene to the screen.
	this->m_D3D->EndScene();

	return true;
}
