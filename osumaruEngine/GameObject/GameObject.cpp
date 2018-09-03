#include "engineStdafx.h"
#include "GameObject.h"

IGameObject::IGameObject() :
	m_isDelete(false),
	m_isStart(false),
	m_isActive(true)
{
}

IGameObject::~IGameObject()
{

}

