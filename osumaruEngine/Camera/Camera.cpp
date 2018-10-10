#include "engineStdafx.h"
#include "Camera.h"
#include "Engine.h"

CCamera::CCamera() :
	m_viewMatrix(CMatrix::Identity),
	m_projectionMatrix(CMatrix::Identity),
	m_position(0.0f, 0.0f, 0.0f),
	m_target(0.0f, 0.0f, 0.0f),
	m_up(0.0f, 1.0f, 0.0f),
	m_Far(1000.0),
	m_Near(0.1f),
	m_Aspect((float)FrameBufferWidth() / (float)FrameBufferHeight()),
	m_angle(CMath::PI / 4)
{
}

CCamera::~CCamera()
{
}

void CCamera::SetAspect(float _aspect)
{
	m_Aspect = _aspect;
}

float CCamera::GetAspect() const
{
	return m_Aspect;
}

void  CCamera::SetFar(float _far)
{
	m_Far = _far;
}

float CCamera::GetFar() const
{
	return m_Far;
}

void CCamera::SetNear(float _near)
{
	m_Near = _near;
}

float CCamera::GetNear() const
{
	return m_Near;
}

void CCamera::SetAngle(float angle)
{
	m_angle = angle;
}

float CCamera::GetAngle() const
{
	return m_angle;
}

void CCamera::SetTarget(const CVector3& target)
{
	m_target = target;
}

const CVector3& CCamera::GetTarget() const
{
	return m_target;
}

void CCamera::SetPosition(const CVector3& position)
{
	m_position = position;
}

const CVector3& CCamera::GetPosition() const
{
	return m_position;
}

void CCamera::SetUp(const CVector3& up)
{
	m_up = up;
}

const CVector3& CCamera::GetUp() const
{
	return m_up;
}

const CVector3& CCamera::GetFlont() const
{
	return m_flont;
}

const CVector3& CCamera::GetRight() const
{
	return m_right;
}

void CCamera::SetViewMatrix(const CMatrix& view)
{
	m_viewMatrix = view;
}

const CMatrix& CCamera::GetViewMatrix() const
{
	return m_viewMatrix;
}

void CCamera::SetProjectionMatrix(const CMatrix& projection)
{
	m_projectionMatrix = projection;
}

const CMatrix& CCamera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

void CCamera::Update()
{
	m_viewMatrix.MakeLookAt(m_position, m_target, m_up);
	m_projectionMatrix.MakeProjectionMatrix(m_angle, m_Aspect, m_Near, m_Far);
	m_viewMatrixInv.Inverse(m_viewMatrix);

	//ÉJÉÅÉâÇÃëOï˚å¸
	m_flont = { m_viewMatrixInv.m[2][0],m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2] };
	//ÉJÉÅÉâÇÃâ°ï˚å¸
	m_right = { m_viewMatrixInv.m[0][0],m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2] };

}

void CCamera::Init()
{
	m_position = CVector3(0.0f, 0.5f, 2.0f);
	m_target = CVector3(0.0f, 0.5f, 0.0f);
	m_up = CVector3(0.0f, 1.0f, 0.0f);
	Update();
}