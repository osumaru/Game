#include "stdafx.h"
#include "Player.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Map/Map.h"
#include "../Scene/SceneManager.h"
#include "../Enemy/IEnemy.h"

void CPlayer::OnInvokeAnimationEvent(//�A�j���[�V�����C�x���g���Ă΂�邲�ƂɌĂяo�����H
	const wchar_t* animClipName,
	const wchar_t* eventName
)
{

	if (wcscmp(animClipName, L"Assets/modelData/PlayerDash60fpsEvent.tka") == 0) {//�C�x���g���ŏ�����ς���H
		const float footVolume = 1.0f;
		CSoundSource* footSound = New<CSoundSource>(0);
		footSound->Init("Assets/sound/Jump.wav");
		footSound->Play(false);
		footSound->SetVolume(footVolume);

	}

	if (wcscmp(animClipName, L"Assets/modelData/PlayerThrustAttack.tka") == 0) {//���Ԃ�Ă΂ꂽ
		/*auto soundSource = New<CSoundSource>(0);
		soundSource->Init("sound/Footstep_00.wav");
		soundSource->Play(false);*/
	}
}

void CPlayer::Init(CVector3 position)
{
	//�v���C���[�̃X�L�������f���̃��[�h
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_skinmodel.LoadNormalmap(L"Assets/modelData/Player_normal.png");
	//����̃��f���̃��[�h
	m_weaponskin[0].Load(L"Assets/modelData/Sword.cmo", NULL);
	m_weaponskin[1].Load(L"Assets/modelData/LargeSword.cmo", NULL);
	m_weaponskin[2].Load(L"Assets/modelData/LongBow.cmo", NULL);
	m_weaponskin[3].Load(L"Assets/modelData/TwinSword.cmo", NULL);

	m_position = position;
	m_characterController.Init(0.3f, 1.0f,m_position);
	m_characterController.SetGravity(-9.8f);
	//���C�g�̐ݒ�
	m_light.SetAmbientLight({ 0.5f,0.5f,0.5f,1.0f});
	m_light.SetDiffuseLight(0, { 1.0f,1.0f,1.0f,1.0f });
	m_skinmodel.SetLight(m_light);

	m_wireCollisionSolver.Init(0.3f, 1.0f);

	m_weaponBoxCollider.Create({ 0.05f,0.4f,0.05f });
	SRigidBodyInfo rInfo;
	rInfo.collider = &m_weaponBoxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_weaponPosition;
	rInfo.rot = m_weaponRotation;

	m_weaponRigitBody.Create(rInfo);
	m_weaponRigitBody.SetPosition(m_weaponPosition);
	m_weaponRigitBody.SetRotation(m_weaponRotation);
	m_weaponRigitBody.PhysicsWorldRemoveRigidBody();

	//�T�[�N���̓ǂݍ���
	{
		m_arrowtexture.Load(L"Assets/sprite/arrowTag.png");
		m_arrowtag.Init(&m_arrowtexture);
		m_arrowtag.SetPosition({ 0.0f,0.0f });
		m_arrowtag.SetSize({ 50.0f,50.0f });
		m_arrowtag.SetAlpha(0.7f);
	}

	//�A�j���[�V�����̏�����
	{
		wchar_t* animClip[enPlayerNum] = {
											{ L"Assets/modelData/PlayerStand.tka"},				//�ҋ@�A�j���[�V����	
											{ L"Assets/modelData/PlayerWalkStay.tka" },			//���s�A�j���[�V����
											{ L"Assets/modelData/PlayerDash60fpsEvent.tka" },		//����A�j���[�V����
											{ L"Assets/modelData/PlayerJump3.tka" },			//����W�����v�A�j���[�V����
											{ L"Assets/modelData/PlayerJump.tka" },				//�W�����v�A�j���[�V����
											{ L"Assets/modelData/PlayerCombo3.tka" },			//�U���A�j���[�V����
											{ L"Assets/modelData/PlayerThrustAttack.tka" },		//�A���A�j���[�V����
											{ L"Assets/modelData/PlayerDamage.tka" },			//�_���[�W�A�j���[�V����
											{ L"Assets/modelData/PlayerKaihiStay.tka" }	,		//����A�N�V����
											{ L"Assets/modelData/PlayerDeath.tka" },			//���S�A�j���[�V����
											{ L"Assets/modelData/PlayerWire.tka" },				//���C���[�ړ��A�j���[�V����


											{ L"Assets/modelData/PlayerArrowAttack.tka" },		//�|�̍U���A�j���[�V����
											{ L"Assets/modelData/PlayerArrowAttackEvent.tka" },
											{ L"Assets/modelData/PlayerLeageSwordAttack.tka" },	//�匕�̍U���A�j���[�V����
											{ L"Assets/modelData/PlayerTwinSwordAttack.tka" }	//�񓁗��̍U���A�j���[�V����
		};

		m_animation.Init(animClip, enPlayerNum);
		m_animation.SetLoopFlg(enPlayerStand, true);
		m_animation.SetLoopFlg(enPlayerWalk, true);
		m_animation.SetLoopFlg(enPlayerRun, true);

		//�A�j���[�V�����C�x���g���X�i�[�̓o�^�@�Ăяo�����֐��̓o�^�H
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName) {
			OnInvokeAnimationEvent(animClipname, eventName);
		});
	}


	//�v���C���[�̃X�e�[�^�X�̏�����
	{
		m_status.Strength	= 10;						//�U����
		m_status.Defense	= 3;						//�h���
		m_status.Health		= 100;						//�̗�
		m_status.MaxHealth = m_status.Health;			//���x�����Ƃ̍ő�HP
		m_status.Level		= 1;						//���x��
		m_status.OldExp		= 15;						//�ЂƂO�̃��x���ɕK�v�Ȍo���l
		m_status.NextExp	= ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12 )) / 2 + 0.5;		//���̃��x���A�b�v�ɕK�v�Ȍo���l
		m_status.ExperiencePoint = 0;					//�o���l
		m_status.AccumulationExp += m_status.OldExp;	//�ݐόo���l
		m_status.Gold = 0;								//������
	}
	
	m_PlayerStateMachine.Start();
	m_PlayerMove.Start();
	m_PlayerRotation.Start();
	Add(&m_PlayerStateMachine,0);
	Add(&m_PlayerMove, 0);
	Add(&m_PlayerRotation, 0);
	Add(this, 1);
	m_skinmodel.SetIsShadowCaster(true);
	
}

void CPlayer::Update()
{
	//�A�j���[�V�����̍X�V
	m_animation.Update(GameTime().GetDeltaFrameTime());
	if (m_isDied) { return; }
	WeaponChange();

	//���G���Ԃ̏���
	if (m_intervalOn)
	{
		m_intervalTime += GameTime().GetDeltaFrameTime();
		if (m_intervalTime >= INTERVAL)
		{
			m_intervalOn = false;
			m_intervalTime = 0.0f;
		}
	}

	StatusCalculation();	//�X�e�[�^�X�̏���
	PlayerAttack();

	if (Pad().IsTriggerButton(enButtonB))
	{
		ExpUP(100);
	}
	
	std::list<CPlayerArrow*>::iterator it;
	it = m_arrowList.begin();
	while (it != m_arrowList.end()) {
		if ((*it)->IsDelete()) {
			//���S���Ă����烊�X�g����폜
			CPlayerArrow* enemy = *it;
			it = m_arrowList.erase(it);
		}
		else {
			it++;
		}
	}

	//���C���[�̏���
	if (Pad().IsTriggerButton(enButtonY) && !m_isWireMove)
	{
		float minLength = FLT_MAX;
		std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		//���C���[���΂�������߂�
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

		if (!m_wireCollisionSolver.Execute(m_position, m_wirePosition)) {
			//���C���΂��ăv���C���[�Ƃ̊Ԃɏ�Q�����Ȃ��Ȃ烏�C���[���g��
			m_isWireMove = true;
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
		}
	}
	if (Pad().IsPressButton(enButtonX))
	{
		Engine().GetPointLightManager().AddPointLight(m_position, { (float)Random().GetRandDouble(), (float)Random().GetRandDouble(), (float)Random().GetRandDouble() });
	}

	if (Pad().GetLeftTrigger())
	{
		GetGameCamera().SetCmareaState(GetGameCamera().enArrow);
		m_isZoom = true;
	}

	else
	{
		GetGameCamera().SetCmareaState(GetGameCamera().enNormal);
		m_isZoom = false;
	}

	//�X�L�����f���̍X�V
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);

	m_weaponskin[m_weaponState].Update(m_weaponPosition, m_weaponRotation, m_weaponScale, true);

	m_cameraTargetPos = m_position;
	CMatrix viewMat;
	CVector3 cameraPos = m_position;
	cameraPos.y += 50.0f;
	CVector3 shadowCameraUp = GetGameCamera().GetSpringCamera().GetTarget() - GetGameCamera().GetSpringCamera().GetPosition();
	shadowCameraUp.y = 0.0f;
	shadowCameraUp.Normalize();
	viewMat.MakeLookAt(cameraPos, m_position, CVector3::AxisX);
	CMatrix projMat;
	projMat.MakeOrthoProjectionMatrix(5, 5, 1.0f, 100.0f);
	Engine().GetShadowMap().SetViewMatrix(viewMat);
	Engine().GetShadowMap().SetProjectionMatrix(projMat);
}

//�`�揈��
void CPlayer::Draw()
{
	if (m_isAttack)
	{
		CVector3 weponUpVec = { m_weaponskin[m_weaponState].GetWorldMatrix().m[2][0],m_weaponskin[m_weaponState].GetWorldMatrix().m[2][1],m_weaponskin[m_weaponState].GetWorldMatrix().m[2][2] };
		weponUpVec *= 0.7f;
		m_weaponPosition.Add(weponUpVec);
		m_weaponRigitBody.SetPosition(m_weaponPosition);

	}
	if (m_isZoom)
	{
		m_arrowtag.Draw();
	}
	m_weaponskin[m_weaponState].Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CPlayer::InitArrow()
{
	CPlayerArrow*	Arrow = New<CPlayerArrow>(0);
	Arrow->Start();
	m_arrowList.push_back(Arrow);
	m_initArrow = true;
}

void CPlayer::StatusCalculation()
{
	//���x���A�b�v�̏���
	if (m_status.NextExp <= m_status.ExperiencePoint)
	{
		m_status.ExperiencePoint -= m_status.NextExp;

		m_status.Level += 1;

		m_status.OldExp = m_status.NextExp;

		m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5;		//���̃��x���A�b�v�ɕK�v�Ȍo���l

		//10���x�����Ƃ̃X�e�[�^�X�̏㏸��
		if (m_status.Level % 10 == 0)
		{

			m_status.Strength	+= 9;
			m_status.Defense	+= 6;
			m_status.MaxHealth	+= 25;
			m_status.Health = m_status.MaxHealth;


		}
		//�������x�����Ƃ̃X�e�[�^�X�̏㏸��
		else if (m_status.Level % 2 == 0)
		{

			m_status.Strength += 5;
			m_status.Defense += 3;
			m_status.MaxHealth += 14;
			m_status.Health = m_status.MaxHealth;


		}

		else
		{
			m_status.Strength += 2;
			m_status.Defense += 2;
			m_status.MaxHealth += 11;
			m_status.Health = m_status.MaxHealth;
		}

	}


}

void  CPlayer::WeaponChange()
{
	if (GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerAttack) { return; }
	if (m_weaponState == (EnPlayerWeapon)GetSceneManager().GetGameScene().GetWeaponSelect()->GetWeapon()) { return; }
	m_weaponState = (EnPlayerWeapon)GetSceneManager().GetGameScene().GetWeaponSelect()->GetWeapon();
	switch (m_weaponState)
	{
		//�Ў茕�̎��̍U�����[�V�����̐ݒ�
	case CWeaponSelect::enSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack);
		break;
		//�|�̎��̍U�����[�V�����̐ݒ�
	case CWeaponSelect::enBow:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerArrowAttack);
		break;
		//�匕�̎��̍U�����[�V�����̐ݒ�
	case CWeaponSelect::enLargeSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerLongSwordAttack);
		break;
		//�o���̎��̍U�����[�V�����̐ݒ�
	case CWeaponSelect::enTwinSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerTwinSwordAttack);
		break;
	}
}

void CPlayer::PlayerAttack()
{
	if (!m_isAttack) { return; }
	
	//�G�l�~�[�̃��X�g���擾
	for (const auto& enemys : GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
	{
		if (!enemys->IsDamage()) {

			CVector3 EnemyVec = enemys->GetPosition();
			EnemyVec.y += 1.3f;
			EnemyVec -= m_weaponPosition;
			float len = EnemyVec.Length();

			if (fabs(len) < 2.0f)
			{
				enemys->SetIsDamage(true);
			}

		}
	}
	

}