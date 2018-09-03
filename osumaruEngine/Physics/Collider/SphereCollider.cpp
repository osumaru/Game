#include "engineStdafx.h"
#include "SphereCollider.h"


CSphereCollider::CSphereCollider() :
	m_sphereShape(nullptr)
{
}

CSphereCollider::~CSphereCollider()
{
}

void CSphereCollider::Create(float radius)
{
	m_sphereShape.reset(new btSphereShape(radius));
}