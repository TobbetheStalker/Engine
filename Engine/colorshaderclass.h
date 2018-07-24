#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <fstream>

#include "GlobalDefinitions.h"


class ColorShaderClass
{
private:
	//Structs
	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	// Variables
	ID3D11VertexShader	*m_vertexShader;
	ID3D11PixelShader	*m_pixelShader;
	ID3D11InputLayout	*m_layout;
	ID3D11Buffer		*m_matrixBuffer;

	// Functions
	bool InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsFilename, WCHAR *psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, WCHAR *shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext *deviceContext, DirectX::XMMATRIX& worldMatrix
							,DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

public:
	// Variables

	// Functions
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();

	bool Initialize(ID3D11Device *device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext *deviceContext, int indexCount, DirectX::XMMATRIX& worldMatrix
				,DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix);

};

#endif
