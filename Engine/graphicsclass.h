#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

/* INCLUDES */
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"

class GraphicsClass
{
public:
//Varibales

//Functions
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int screenWidth, int screenHeight, HWND);
	void Shutdown();
	bool Frame();

private:
//Varibales
	D3DClass* m_D3D;

	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;

//Functions
	bool Render();
};

#endif
