#include "WireAction.h"
#include "Player.h"
#include "../Enemy/IEnemy.h"
#include "../Scene/SceneManager.h"
#include "../Scene/GameScene.h"
#include "../Map/Map.h"

void CWireAction::Init(const CPlayer* player)
{
	m_pPlayer = player;
	m_wireCollisionSolver.Init(0.3f, 1.0f);
}

void CWireAction::Add(const CSkinModel& skinModel)
{
	const CSkelton* skelton = skinModel.GetSkelton();
	if (skelton != nullptr)
	{
		//�{�[�������Ԑ�̒n�_��o�^
		int boneNum = skinModel.GetSkelton()->GetBoneNum();
		for (int i = 0; i < boneNum; i++)
		{
			m_posWireFly.push_back((CVector3*)(skelton->GetBoneWorldMatrix(i).m[3]));
		}
	}
}

void CWireAction::Update()
{
	//���C���[�̏���
	if (Pad().IsTriggerButton(enButtonY) && !m_isWireMove)
	{
		float minLength = FLT_MAX;
		std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		//���C���[���΂�������߂�
		switch (m_state)
		{
		case enStateEnemy:
			for (auto& enemy : enemyList)
			{
				CVector3 enemyPos = enemy->GetPosition();
				CVector3 toEnemyPos = enemyPos - GetPlayer().GetPosition();
				float length = toEnemyPos.Length();
				if (minLength > length) {
					minLength = length;
					//��ԋ߂��G�̈ʒu���ړ���Ƃ���
					m_wirePosition = enemyPos;
				}
			}
			break;
		case enStateMap:
			for (const CVector3* pos : m_posWireFly)
			{
				CVector3 distance = m_pPlayer->GetPosition() - *pos;
				if (distance.LengthSq() < minLength)
				{
					minLength = distance.LengthSq();
					m_wirePosition = *pos;
				}
			}
			break;
		}

		if (!m_wireCollisionSolver.Execute(m_pPlayer->GetPosition(), m_wirePosition)) 
		{
			//���C���΂��ăv���C���[�Ƃ̊Ԃɏ�Q�����Ȃ��Ȃ烏�C���[���g��
			m_isWireMove = true;
			switch (m_state)
			{
			case enStateEnemy:
				for (auto& enemy : enemyList)
				{
					CVector3 enemyPos = enemy->GetPosition();
					CVector3 toMovePos = m_wirePosition - enemyPos;
					float length = toMovePos.Length();
					if (length < 0.1f) {
						//��ԋ߂��G�Ƀ��C���[�����������t���O��ݒ肷��
						enemy->SetIsWireHit(true);
					}
				}
				break;

			case enStateMap:
				break;
			}
		}
	}
}