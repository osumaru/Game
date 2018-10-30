#include "stdafx.h"
#include "PlayerRotation.h"
#include "Player.h"
#include "PlayerSate/PlayerStateMachine.h"
#include "PlayerSate/PlayerState.h"
#include "../Camera/GameCamera.h"

CPlayerRotation::CPlayerRotation()
{
}

CPlayerRotation::~CPlayerRotation()
{
}

void CPlayerRotation::Update()
{
	//if (!m_isActive)
	//{
	//	return;
	//}
	//GetPlayer().GetPlayerSkin().Update(GetPlayer().GetPosition(), GetPlayer().GetPlayerrRot(), { 1.0f,1.0f,1.0f },true);
	//CVector3 playerVec = GetPlayer().GetMoveSpeed();
	//playerVec.y = 0.0f;
	////プレイヤーのワールド行列の取得
	//CMatrix PlayerWorldMatrix = GetPlayer().GetPlayerSkin().GetWorldMatrix();
	////武器の座標と回転の初期化
	//CVector3		weaponPosition = CVector3::Zero;//GetPlayer().GetWeaponPosition();
	//CQuaternion		weaponRot;
	////プレイヤーの前方向の取得
	//CVector3 PlayerFront = { PlayerWorldMatrix.m[1][0],PlayerWorldMatrix.m[1][1],PlayerWorldMatrix.m[1][2] };
	//PlayerFront.Normalize();


	//プレイヤーの背中に武器を持たせえるための処理
	//if (!GetPlayer().GetIsAttack())
	{
		////プレイヤーのボーンの情報を取得
		////CMatrix PlayerSpine = GetPlayer().GetPlayerSkin().FindBoneWorldMatrix(L"Spine2");
		////CVector3 PlayerSpinePos = { PlayerSpine.m[3][0],PlayerSpine.m[3][1],PlayerSpine.m[3][2] };
		////CVector3 PlayerHndScale = { PlayerSpine.m[0][0], PlayerSpine.m[0][1], PlayerSpine.m[0][2] };
		////float len = PlayerHndScale.Length();
		////PlayerSpine.m[0][0] /= len;
		////PlayerSpine.m[0][1] /= len;
		////PlayerSpine.m[0][2] /= len;

		////PlayerSpine.m[1][0] /= len;
		////PlayerSpine.m[1][1] /= len;
		////PlayerSpine.m[1][2] /= len;

		////PlayerSpine.m[2][0] /= len;
		////PlayerSpine.m[2][1] /= len;
		////PlayerSpine.m[2][2] /= len;
		////GetPlayer().SetWeaponPosition(PlayerSpinePos);

		////移動中の武器の座標の設定
		////if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerWalk ||
		////	GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerRun)
		////{
		////	/*PlayerFront *= 0.0f;
		////	weaponPosition = GetPlayer().GetPosition();
		////	weaponPosition.y = PlayerSpinePos.y;
		////	weaponPosition.Add(PlayerFront);
		////	GetPlayer().SetWeaponPosition(weaponPosition);*/

		////}
		////ジャンプ中の武器の位置
		////if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerJump)
		////{
		////	PlayerFront *= 0.0f;
		////	weaponPosition = GetPlayer().GetPosition();
		////	weaponPosition.y = PlayerSpinePos.y;
		////	weaponPosition.Add(PlayerFront);
		////	GetPlayer().SetWeaponPosition(weaponPosition);
		////}

		////移動中以外の武器の座標の設定
		////else
		////{

		////	PlayerFront *= 0.16f;
		////	weaponPosition = GetPlayer().GetPosition();
		////	weaponPosition.y = PlayerSpinePos.y;
		////	weaponPosition.Add(PlayerFront);
		////	GetPlayer().SetWeaponPosition(weaponPosition);
		////}

		////武器の回転を行う処理
		////{
		////	weaponRot.SetRotation(PlayerSpine);
		////	CQuaternion rotX, rotY ,rotZ;
		////	rotX.SetRotationDeg(CVector3::AxisX, 180.0f);
		////	rotY.SetRotationDeg(CVector3::AxisY, 90.0f);
		////	rotZ.SetRotationDeg(CVector3::AxisZ, 90.0f);
		////	weaponRot.Multiply(rotX);
		////	weaponRot.Multiply(rotY);
		////	GetPlayer().SetWeaponRotation(weaponRot);
		////}
	}
	//プレイヤーの手のボーンに武器を持たせる処理
	//else 
	{
		//プレイヤーの手のボーンを取得
		//CMatrix PlayerHnd = GetPlayer().GetPlayerSkin().FindBoneWorldMatrix(L"LeftHandMiddle1");
		//CVector3 PlayerHndPos = { PlayerHnd.m[3][0],PlayerHnd.m[3][1],PlayerHnd.m[3][2] };
		//CVector3 PlayerHndScale = { PlayerHnd.m[0][0], PlayerHnd.m[0][1], PlayerHnd.m[0][2] };
		//float len = PlayerHndScale.Length();
		//PlayerHnd.m[0][0] /= len;
		//PlayerHnd.m[0][1] /= len;
		//PlayerHnd.m[0][2] /= len;

		//PlayerHnd.m[1][0] /= len;
		//PlayerHnd.m[1][1] /= len;
		//PlayerHnd.m[1][2] /= len;

		//PlayerHnd.m[2][0] /= len;
		//PlayerHnd.m[2][1] /= len;
		//PlayerHnd.m[2][2] /= len;
		//weaponPosition = PlayerHndPos;
		//weaponRot.SetRotation(PlayerHnd);
		//CQuaternion multi;
		//multi.SetRotationDeg(CVector3::AxisY, 45.0f);
		//multi.SetRotationDeg(CVector3::AxisX, 90.0f);
		//weaponRot.Multiply(multi);
		//GetPlayer().SetWeaponPosition(weaponPosition);
		//武器の回転処理
		//{
		//	weaponRot.SetRotation(PlayerHnd);
		//	CQuaternion rotX, rotY;
		//	//rotX.SetRotationDeg(CVector3::AxisX, 90.0f);
		//	//rotY.SetRotationDeg(CVector3::AxisY, 180.0f);
		//	weaponRot.Multiply(rotX);
		//	weaponRot.Multiply(rotY);
		//	//GetPlayer().SetWeaponRotation(weaponRot);
		//}

	}

	//if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerArrowAttack)
	//{
	//	CQuaternion rotXZ, rotY;
	//	CVector3 cameraFlont = GetGameCamera().GetCamera().GetFlont();
	//	rotXZ.SetRotation(CVector3::AxisY, atan2f(cameraFlont.x, cameraFlont.z));
	//	rotY.SetRotation(CVector3::AxisX, atanf(-cameraFlont.y));
	//	rotXZ.Multiply(rotY);
	//	//GetPlayer().SetPlayerRot(rotXZ);
	//}

	////プレイヤーの回転の処理
	//else if (playerVec.LengthSq() > 0.001f)
	//{
	//	//if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerArrowAttack ||
	//	//	GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerArrowShoot) { return; }
	//	CQuaternion Playerrot = GetPlayer().GetPlayerrRot();
	//	CQuaternion rot = CQuaternion::Identity;
	//	rot.SetRotation(CVector3::AxisY, atan2f(playerVec.x, playerVec.z));		//Y軸周りの回転
	//	Playerrot.Slerp(0.2f, Playerrot, rot);
	//	//GetPlayer().SetPlayerRot(Playerrot);
	//}
}

void CPlayerRotation::WeaponRot()
{
	
}
