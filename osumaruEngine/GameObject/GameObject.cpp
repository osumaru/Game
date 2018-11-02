#include "engineStdafx.h"
#include "GameObject.h"

IGameObject::IGameObject() :
	m_isDelete(false),
	m_isStart(false),
	m_isActiveUpdate(true),
	m_isActiveDraw(true)
{
}

IGameObject::~IGameObject()
{

}

