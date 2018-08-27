#include "engineStdafx.h"
#include "Camera.h"
#include "Engine.h"

Camera::Camera() :
	m_viewMatrix(Matrix::Identity),
	m_projectionMatrix(Matrix::Identity),
	m_position(0.0f, 0.0f, 0.0f),
	m_target(0.0f, 0.0f, 0.0f),
	m_up(0.0f, 1.0f, 0.0f),
	m_Far(1000.0),
	m_Near(0.1f),
	m_Aspect((float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT),
	m_angle(Math::PI / 4)
{
}

Camera::~Camera()
{
}

void Camera::SetAspect(float _aspect)
{
	m_Aspect = _aspect;
}

float Camera::GetAspect() const
{
	return m_Aspect;
}

void  Camera::SetFar(float _far)
{
	m_Far = _far;
}

float Camera::GetFar() const
{
	return m_Far;
}

void Camera::SetNear(float _near)
{
	m_Near = _near;
}

float Camera::GetNear() const
{
	return m_Near;
}

void Camera::SetAngle(float angle)
{
	m_angle = angle;
}

float Camera::GetAngle() const
{
	return m_angle;
}

void Camera::SetTarget(const Vector3& target)
{
	m_target = target;
}

const Vector3& Camera::GetTarget() const
{
	return m_target;
}

void Camera::SetPosition(const Vector3& position)
{
	m_position = position;
}

const Vector3& Camera::GetPosition() const
{
	return m_position;
}

void Camera::SetUp(const Vector3& up)
{
	m_up = up;
}

const Vector3& Camera::GetUp() const
{
	return m_up;
}

void Camera::SetViewMatrix(const Matrix& view)
{
	m_viewMatrix = view;
}

const Matrix& Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

void Camera::SetProjectionMatrix(const Matrix& projection)
{
	m_projectionMatrix = projection;
}

const Matrix& Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

void Camera::Update()
{
	m_viewMatrix.MakeLookAt(m_position, m_target, m_up);
	m_projectionMatrix.MakeProjectionMatrix(m_angle, m_Aspect, m_Near, m_Far);

}

void Camera::Init()
{
	m_position = Vector3(0.0f, 0.5f, 2.0f);
	m_target = Vector3(0.0f, 0.5f, 0.0f);
	m_up = Vector3(0.0f, 1.0f, 0.0f);
	Update();
}