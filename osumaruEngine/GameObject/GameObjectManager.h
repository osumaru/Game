#pragma once
class IGameObject;
//�I�u�W�F�N�g�}�l�[�W���[
#include "../Graphics/PostRendering/Deferred.h"
#include "../Graphics/PostRendering/PostEffect.h"
#include "GameObject.h"
struct SGameObjectData
{
	IGameObject* gameObject;		//�I�u�W�F�N�g
	bool isNew;					//���̃I�u�W�F�N�g��new����č�������ۂ�
};
const int PRIORITY_MAX = 16;

class CGameObjectManager : Uncopyable
{
public:
	~CGameObjectManager();

	//�������֐�
	void Init();

	//�Q�[����1���[�v�����s����֐�
	void Execute(CDeferred& deferred, CPostEffect& postEffect);

	//�Q�[���̃I�u�W�F�N�g����������֐�
	void Delete(IGameObject* deleteObject);


	/*
	�I�u�W�F�N�g�𐶐�����B
	priority	�I�u�W�F�N�g�̗D��x
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
	�I�u�W�F�N�g��o�^
	object		�o�^����I�u�W�F�N�g
	priority	�I�u�W�F�N�g�̗D��x
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

	//���ׂẴI�u�W�F�N�g���A�N�e�B�u������
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
	//���ׂẴI�u�W�F�N�g���A�N�e�B�u������
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

	//�I�u�W�F�N�g�����X�g�����������֐�
	void DeleteExecute();

private:
	typedef std::list<SGameObjectData> GameObjectList;	//�I�u�W�F�N�g�̃��X�g
	std::vector<GameObjectList> m_objectVector;		//�I�u�W�F�N�g
};
