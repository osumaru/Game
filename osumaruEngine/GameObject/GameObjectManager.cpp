#include "engineStdafx.h"
#include "GameObjectManager.h"
#include "../Engine.h"
#include "../Physics/Physics.h"
#include  "../Input/Pad.h"

void CGameObjectManager::Init()
{
	m_objectVector.resize(PRIORITY_MAX);
}

CGameObjectManager::~CGameObjectManager()
{

}

void CGameObjectManager::Execute(CDeferred& deferred, CPostEffect& postEffect)
{
	static bool isFlg = false;
	static bool isBreak = false;
	if (Pad().IsTriggerButton(enButtonLStickPush))
	{
		isBreak = !isBreak;
	}
	if (Pad().IsTriggerButton(enButtonUp) && isBreak)
	{
		isFlg = true;
	}
	if (!isBreak || isFlg)
	{

		//初期化
		for (GameObjectList& objList : m_objectVector)
		{
			for (SGameObjectData& object : objList)
			{
				object.gameObject->Starter();
			}
		}

		//初期化
		for (GameObjectList& objList : m_objectVector)
		{
			for (SGameObjectData& object : objList)
			{
				object.gameObject->AsyncStarter();
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
	}
	isFlg = false;
	Engine().GetShadowMap().Draw();
	//

	Engine().SetAlphaBlendState(enAlphaBlendStateNone);
	Engine().SetDepthStencilState(enDepthStencilState3D);
	deferred.Start();

	for (GameObjectList& objList : m_objectVector)
	{
		for (SGameObjectData& object : objList)
		{
			object.gameObject->Drawer();
		}
	}
	PhysicsWorld().Draw();
	deferred.Draw();
	for (GameObjectList& objList : m_objectVector)
	{
		for (SGameObjectData& object : objList)
		{
			object.gameObject->AfterDrawer();
		}
	}
	Engine().GetTBDR().Draw();

	postEffect.Draw();
	Engine().GetEffectEngine().Draw();
	for (GameObjectList& objList : m_objectVector)
	{
		for (SGameObjectData& object : objList)
		{
			object.gameObject->PostAfterDrawer();
		}
	}
	GameTime().Draw();

	//最後にオブジェクトを消去
	DeleteExecute();
}

void CGameObjectManager::Delete(IGameObject* deleteObject)
{
	if (deleteObject->m_isDelete)
	{
		return;
	}
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