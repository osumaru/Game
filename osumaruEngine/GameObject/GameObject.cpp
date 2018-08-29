#include "engineStdafx.h"
#include "GameObject.h"

GameObject::GameObject() :
	m_isDelete(false),
	m_isStart(false),
	m_isActive(true)
{
}

GameObject::~GameObject()
{

}

