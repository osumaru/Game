#include "BossBuilding.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../Scene/SceneManager.h"
#include "../UI/Message/Message.h"
#include "../UI/Message/Choices.h"

void CBossBuilding::Init(CVector3 position)
{
	//���f���̏�����
	m_skinModel.Load(L"Assets/modelData/CastleDoor2.cmo");
	//���W��ݒ�
	m_position = position;
}

void CBossBuilding::Update()
{
	if (GetSceneManager().GetSceneChange())
	{
		//�V�[���؂�ւ����������
		Delete(this);
		return;
	}

	if (!m_isChoice)
	{
		//�I�𒆂łȂ��Ȃ�^�C�}�[��i�߂�
		m_timer += GameTime().GetDeltaFrameTime();
	}
	//�v���C���[�̍��W���擾
	CVector3 playerPos = GetPlayer().GetPosition();
	//�v���C���[�Ƃ̋��������߂�
	CVector3 distance = playerPos - m_position;
	float length = distance.Length();
	if (!m_isChoice && length < 2.0f && m_timer >= 3.0f)
	{
		//���b�Z�[�W�ƑI������\������
		m_message = New<CMessage>(PRIORITY_UI);
		m_message->Init({ 500.0f,250.0f }, L"bossTry");
		m_choices = New<CChoices>(PRIORITY_UI);
		m_choices->Init(L"�͂�", L"������");
		m_choices->SetIsActive(false);
		m_isChoice = true;
		m_timer = 0.0f;
	}

	if (m_isChoice)
	{
		//�I�𒆂Ȃ�v���C���[�͓����Ȃ�
		GetPlayer().SetIsAction(false);
		//���b�Z�[�W��`�悵�I�����
		if (m_message->GetIsDrawEnd())
		{
			//�I������\������
			m_choices->SetIsActive(true);
		}
		//�I������I��
		if (m_choices->GetIsSelect())
		{
			//�͂���I��
			if (m_choices->GetState() == CChoices::Yes)
			{
				//�{�X�V�[���ɐ؂�ւ���
				GetSceneManager().ChangeScene(CSceneManager::enBossScene);
			}
			//��������I��
			else
			{
				//�v���C���[�𓮂�����悤�ɂ���
				GetPlayer().SetIsAction(true);
				m_isChoice = false;
			}
			//���b�Z�[�W�ƑI����������
			Delete(m_message);
			Delete(m_choices);
		}
	}

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}

void CBossBuilding::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
