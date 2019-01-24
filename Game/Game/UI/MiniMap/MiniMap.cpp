#include "stdafx.h"
#include "MiniMap.h"
#include "../../Player/Player.h"
#include "../../Enemy/IEnemy.h"
#include "../../Camera/GameCamera.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"

CMiniMap::CMiniMap()
{
}

CMiniMap::~CMiniMap()
{
}

void CMiniMap::Init()
{
	m_mapCenterPos = { 540.0f,-260.0f };
	//�~�j�}�b�v��������
	m_miniMapTexture = TextureResource().LoadTexture(L"Assets/sprite/miniMap.png");
	m_miniMap.Init(m_miniMapTexture);
	m_miniMap.SetPosition(m_mapCenterPos);
	m_miniMap.SetSize({ 180.0f,180.0f });
	m_miniMap.SetAlpha(0.8f);
	//�v���C���[�A�C�R����������
	m_playerIconTexture = TextureResource().LoadTexture(L"Assets/sprite/player_Icon.png");
	m_playerIcon.Init(m_playerIconTexture);
	m_playerIcon.SetPosition(m_mapCenterPos);
	m_playerIcon.SetSize({ 15.0f,15.0f });
	//�G�l�~�[�A�C�R����������
	m_enemyIconTexture = TextureResource().LoadTexture(L"Assets/sprite/enemy_Icon.png");
	m_enemyList = &GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
	for (int i = 0; i < m_enemyList->size(); i++) {
		m_enemyIcon.emplace_back(std::make_unique<CSprite>());
		m_enemyIcon[i]->Init(m_enemyIconTexture);
		m_enemyIcon[i]->SetPosition(m_mapCenterPos);
		m_enemyIcon[i]->SetSize({ 10.0f,10.0f });
		m_enemyIcon[i]->SetAlpha(0.8f);
	}
}

void CMiniMap::Update()
{
	//�J�����̏������ݒ�
	CVector3 cameraUp = GetGameCamera().GetCamera().GetTarget() - GetGameCamera().GetCamera().GetPosition();
	cameraUp.y = 0.0f;
	//�J�����̒����_��ݒ�
	CVector3 target = GetPlayer().GetPosition();
	//�J�����̍��W��ݒ�
	CVector3 cameraPos = target;
	cameraPos.y += 20.0f;
	//�r���[�s����v�Z
	CMatrix viewMatrix;
	viewMatrix.MakeLookAt(cameraPos, target, cameraUp);
	//�v���W�F�N�V�����s����v�Z
	CMatrix projectionMatrix;
	projectionMatrix.MakeOrthoProjectionMatrix(100.0f, 100.0f, 1.0f, 100.0f);

	//�G�A�C�R���̏���
	{
		m_enemyList = &GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		int idx = 0;
		for (auto& enemy : *m_enemyList)
		{
			CVector3 toCameraXZ = cameraPos - enemy->GetPosition();
			toCameraXZ.y = 0.0f;
			float length = toCameraXZ.Length();
			if (length <= 50.0f) {
				//�r���[�ϊ�
				CVector4 viewPosition;
				viewPosition.Set(enemy->GetPosition());
				viewMatrix.Mul(viewPosition);
				//�v���W�F�N�V�����ϊ�
				CVector4 projectionPosition = viewPosition;
				projectionMatrix.Mul(projectionPosition);
				projectionPosition = projectionPosition / projectionPosition.w;
				//�X�N���[���ϊ�
				CVector2 screenPosition;
				screenPosition.x = (1.0f + projectionPosition.x) / 2.0f * m_miniMap.GetSize().x - (m_miniMap.GetSize().x / 2.0f);
				screenPosition.y = (1.0f + projectionPosition.y) / 2.0f * m_miniMap.GetSize().y - (m_miniMap.GetSize().y / 2.0f);
				screenPosition += m_mapCenterPos;
				//�G�̃A�C�R���̍��W���X�V
				m_enemyIcon[idx]->SetPosition(screenPosition);
				m_enemyIcon[idx]->SetIsDraw(true);
			}
			else {
				m_enemyIcon[idx]->SetIsDraw(false);
			}
			idx++;
		}
	}

	//�v���C���[�A�C�R���̏���
	{
		//�v���C���[�̃��[���h�s�񂩂�L�����N�^�[�̌������擾
		CMatrix playerWorldMatrix = GetPlayer().GetSkinmodel().GetWorldMatrix();
		CVector3 playerForward;
		playerForward.x = playerWorldMatrix.m[2][0];
		playerForward.y = 0.0f;
		playerForward.z = playerWorldMatrix.m[2][2];
		playerForward.Normalize();
		//�v���C���[�A�C�R���̌�����ݒ�
		CVector3 playerIconVec = cameraUp;
		playerIconVec.Normalize();
		float angle = playerForward.Dot(playerIconVec);
		if (angle > 1.0f) {
			angle = 1.0f;
		}
		else if (angle < -1.0f) {
			angle = -1.0f;
		}
		angle = acosf(angle);
		//�E��]������]�����߂�
		CVector3 Cross = playerForward;
		Cross.Cross(playerIconVec);
		if (Cross.y > 0.0f) {
			angle *= -1.0f;
		}
		//�v���C���[�A�C�R������]������
		m_playerIcon.SetRotationAngle(angle);
	}
}

void CMiniMap::PostAfterDraw()
{
	m_miniMap.Draw();
	for (int i = 0; i < m_enemyList->size(); i++) {
		m_enemyIcon[i]->Draw();
	}
	m_playerIcon.Draw();
}
