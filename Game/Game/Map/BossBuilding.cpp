#include "BossBuilding.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"
#include "../UI/Message/Message.h"

void CBossBuilding::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/TestBox1.cmo");
	m_position = position;
	m_message = New<CMessage>(PRIORITY_UI);
	m_message->Init({ 200.0f,400.0f }, L"�{�X�ɒ��݂܂����H");
	m_message->SetIsActive(false);
}

void CBossBuilding::Update()
{
	if (GetSceneManager().GetSceneChange())
	{
		//�V�[���؂�ւ����������
		Delete(this);
		return;
	}

	CVector3 playerPos = GetPlayer().GetPosition();
	//�v���C���[�Ƃ̋��������߂�
	CVector3 distance = playerPos - m_position;
	float length = distance.Length();
	if (length < 2.0f)
	{
		m_message->SetIsActive(true);
		////�{�X�V�[���ɐ؂�ւ���
		//GetSceneManager().ChangeScene(CSceneManager::enBossScene);
	}
	else {
		m_message->SetIsActive(false);
	}

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CBossBuilding::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
