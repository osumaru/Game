#include "engineStdafx.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Engine.h"
#include "../Physics/Physics.h"

void CGameObjectManager::Init()
{
	m_objectVector.resize(PRIORITY_MAX);
}

void CGameObjectManager::Execute()
{
	//初期化
	for (GameObjectList& objList : m_objectVector)
	{
		for (SGameObjectData& object : objList)
		{
			object.gameObject->Starter();
		}
	}
	//更新
	for (GameObjectList& objList : m_objectVector)
	{
		for (SGameObjectData& object : objList)
		{
			object.gameObject->Updater();
		}
	}
	for (GameObjectList& objList : m_objectVector)
	{
		for (SGameObjectData& object : objList)
		{
			object.gameObject->Drawer();
		}
	}
	
	PhysicsWorld().Draw();
	for (GameObjectList& objList : m_objectVector)
	{
		for (SGameObjectData& object : objList)
		{
			object.gameObject->AfterDrawer();
		}
	}

	//最後にオブジェクトを消去
	DeleteExecute();
}

void CGameObjectManager::Delete(IGameObject* deleteObject)
{
	deleteObject->BeforeDead();
	deleteObject->m_isDelete = true;
}

void CGameObjectManager::DeleteExecute()
{
	for (GameObjectList& objList : m_objectVector)
	{
		std::list<SGameObjectData>::iterator it = objList.begin();
		while (it != objList.end())
		{
			if ((*it).gameObject->IsDelete())
			{
				if ((*it).isNew)
				{
					IGameObject *deleteObject = (*it).gameObject;
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