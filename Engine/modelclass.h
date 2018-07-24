#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>



class ModelClass
{
private:
	//Structs
	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};

	// Variables
	ID3D11Buffer	*m_vertexBuffer;
	ID3D11Buffer	*m_indexBuffer;
	int				m_vertexCount, m_indexCount;

	// Functions
	bool InitializeBuffers(ID3D11Device *device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*deviceContext);


public:
	// Variables

	// Functions
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device *device);
	void Shutdown();
	void Render(ID3D11DeviceContext *deviceContext);

	int GetIndexCount();



};


#endif