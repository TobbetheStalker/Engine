#include "cameraclass.h"

CameraClass::CameraClass()
{
	this->m_viewMatrix = DirectX::XMMatrixIdentity();
	this->m_camPos = DirectX::XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f);
	this->m_lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	this->m_camUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	this->m_roll = 0.0f;
	this->m_pitch = 0.0f;
	this->m_yaw = 0.0f;
}

CameraClass::CameraClass(const CameraClass &)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	this->m_camPos = DirectX::XMVectorSet(x, y, z, 1.f);
	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	this->m_roll	= x;
	this->m_pitch	= y;
	this->m_yaw		= z;
	return;
}

DirectX::XMVECTOR CameraClass::GetPosition()
{
	return this->m_camPos;
}

DirectX::XMFLOAT3 CameraClass::GetRotation()
{
	return DirectX::XMFLOAT3(this->m_roll, this->m_pitch, this->m_yaw);
}

void CameraClass::Render()
{
	DirectX::XMMATRIX camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(this->m_pitch, this->m_yaw, this->m_roll);

	DirectX::XMVECTOR camPos = DirectX::XMVector3TransformCoord(this->m_camPos, camRotationMatrix);
	DirectX::XMVECTOR lookAt = DirectX::XMVector3TransformCoord(this->m_lookAt, camRotationMatrix);
	DirectX::XMVECTOR camUp = DirectX::XMVector3TransformCoord(this->m_camUp, camRotationMatrix);

	this->m_viewMatrix = DirectX::XMMatrixLookAtLH(camPos, lookAt, camUp);

	return;
}

void CameraClass::GetViewMatrix(DirectX::XMMATRIX &viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}
