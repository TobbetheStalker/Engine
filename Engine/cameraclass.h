#ifndef _CAMERQACLASS_H_
#define _CAMERACLASS_H_

#include <DirectXMath.h>



class CameraClass
{
public:
	// Variables

	// Functions
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	DirectX::XMVECTOR GetPosition();
	DirectX::XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(DirectX::XMMATRIX&);

private:
	// Variables
	DirectX::XMVECTOR m_camPos, m_lookAt, m_camUp;
	DirectX::XMMATRIX m_viewMatrix;
	float m_roll, m_pitch, m_yaw;

	// Functions
};

#endif
