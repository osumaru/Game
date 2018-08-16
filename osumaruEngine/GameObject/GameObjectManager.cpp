#include "engineStdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Engine.h"
#include "../Physics/Physics.h"

void GameObjectManager::Init()
{
	m_objectVector.resize(PRIORITY_MAX);
}

void GameObjectManager::Execute()
{
	//������
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObjectData& object : objList)
		{
			object.gameObject->Starter();
		}
	}
	//�X�V
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObjectData& object : objList)
		{
			object.gameObject->Updater();
		}
	}
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObjectData& object : objList)
		{
			object.gameObject->Drawer();
		}
	}
	
	GetPhysicsWorld().Draw();
	for (GameObjectList& objList : m_objectVector)
	{
		for (GameObjectData& object : objList)
		{
			object.gameObject->AfterDrawer();
		}
	}

	//�Ō�ɃI�u�W�F�N�g������
	DeleteExecute();
}

void GameObjectManager::Delete(GameObject* deleteObject)
{
	deleteObject->BeforeDead();
	deleteObject->Dead();
}

void GameObjectManager::DeleteExecute()
{
	for (GameObjectList& objList : m_objectVector)
	{
		std::list<GameObjectData>::iterator it = objList.begin();
		while (it != objList.end())
		{
			if ((*it).gameObject->IsDelete())
			{
				if ((*it).isNew)
				{
					GameObject *deleteObject = (*it).gameObject;
					delete deleteObject;
				}
				else
				{
					(*it).gameObject->Reset();
				}
				it = objList.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

}