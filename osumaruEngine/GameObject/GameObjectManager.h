#pragma once
class IGameObject;
//オブジェクトマネージャー
#include "../Graphics/PostRendering/Deferred.h"
#include "../Graphics/PostRendering/PostEffect.h"
#include "GameObject.h"
struct SGameObjectData
{
	IGameObject* gameObject;		//オブジェクト
	bool isNew;					//このオブジェクトがnewされて作ったか否か
};
const int PRIORITY_MAX = 16;

class CGameObjectManager : Uncopyable
{
public:
	~CGameObjectManager();

	//初期化関数
	void Init();

	//ゲームの1ループを実行する関数
	void Execute(CDeferred& deferred, CPostEffect& postEffect);

	//ゲームのオブジェクトを消去する関数
	void Delete(IGameObject* deleteObject);


	/*
	オブジェクトを生成する。
	priority	オブジェクトの優先度
	*/
	template<class T, class... TArgs>
	T* New(int priority, TArgs... args)
	{
		if (priority < 0 || PRIORITY_MAX <= priority)
		{
			return nullptr;
		}
		T* newObject = new T(args...);
		m_objectVector[priority].push_back({ newObject, true });
		return newObject;
	}

	/*
	オブジェクトを登録
	object		登録するオブジェクト
	priority	オブジェクトの優先度
	*/
	void Add(IGameObject* object, int priority)
	{
		for (GameObjectList& objList : m_objectVector)
		{
			for (SGameObjectData& obj : objList)
			{
				if (object == obj.gameObject)
				{
					return;
				}
			}
		}
		m_objectVector[priority].push_back({ object, false });
	}

	//すべてのオブジェクトを非アクティブ化する
	void AllInactive()
	{
		for (auto& gameObjectVector : m_objectVector)
		{
			for (auto& gameObject : gameObjectVector)
			{
				gameObject.gameObject->m_isActiveUpdate = false;
				gameObject.gameObject->m_isActiveDraw = false;
			}
		}
	}
	//すべてのオブジェクトをアクティブ化する
	void AllActive()
	{
		for (auto& gameObjectVector : m_objectVector)
		{
			for (auto& gameObject : gameObjectVector)
			{
				gameObject.gameObject->m_isActiveUpdate = true; 
				gameObject.gameObject->m_isActiveDraw = true;
			}
		}
	}

	//オブジェクトをリストから消去する関数
	void DeleteExecute();

private:
	typedef std::list<SGameObjectData> GameObjectList;	//オブジェクトのリスト
	std::vector<GameObjectList> m_objectVector;		//オブジェクト
};
