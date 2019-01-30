#include "TwinSword.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"
#include "../../Enemy/IEnemy.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/GameScene.h"
#include "../../Map/Map.h"
#include "../../Enemy/Boss/Maw.h"
#include "../../Enemy/EnemyGroup.h"

void CTwinSword::Init()
{
	m_normalTwinBoneMat = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"Spine");
	m_attackTwinBoneMat = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"LeftHand");


	m_position = { 0.0f, 50.0f, -17.0f };
	m_rotation = CQuaternion::Identity;
	CQuaternion multi;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation.Multiply(multi); 
	multi.SetRotationDeg(CVector3::AxisX, 70.0f);
	m_rotation.Multiply(multi);

	m_attackRotation = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_attackRotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_attackRotation.Multiply(multi);
	m_attackPosition = { -10.0f, 0.0f, 0.0f };


	//二つ目の剣用
	m_positionTwin = { 10.0f, 47.0f, -17.0f };
	m_rotationTwin = CQuaternion::Identity;
	CQuaternion multi2;
	multi2.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotationTwin.Multiply(multi2);
	multi2.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotationTwin.Multiply(multi2);
	multi2.SetRotationDeg(CVector3::AxisX, 50.0f);
	m_rotationTwin.Multiply(multi2);

	m_attackTwinRotation = CQuaternion::Identity;
	multi2.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_attackTwinRotation.Multiply(multi2);
	multi2.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_attackTwinRotation.Multiply(multi2);
	m_attackTwinPosition = { 10.0f, 0.0f, 0.0f };


	m_skinModel.Load(L"Assets/modelData/TwinSword.cmo", NULL);
	m_skinModelTwin.Load(L"Assets/modelData/TwinSword.cmo", NULL);
	m_skinModel.LoadSpecularMap(L"Assets/modelData/TwinSword_metallic.tif");
	m_skinModelTwin.LoadSpecularMap(L"Assets/modelData/TwinSword_metallic.tif");
	m_skinModel.LoadNormalmap(L"Assets/modelData/TwinSword_normal.tif");
	m_skinModelTwin.LoadNormalmap(L"Assets/modelData/TwinSword_normal.tif");
	float speculaPower = 1.0f;
	m_skinModel.SetSpecularPower(speculaPower);
	m_skinModelTwin.SetSpecularPower(speculaPower);

	m_maxAttackNum = 3;
	m_maxWeaponHitNum = 2;
	m_hitEffectParam = std::make_unique<SHitEffectParam[]>(m_maxAttackNum);
	m_attackAnimation = std::make_unique<EnPlayerAnimation[]>(m_maxAttackNum);
	m_combineAnimation = std::make_unique<EnPlayerAnimation[]>(m_maxAttackNum);
	m_hitEffectParam[0] = { 0.0f, 1.0f, 0.0f };
	m_hitEffectParam[1] = { 0.0f, 1.0f, 0.0f };
	m_hitEffectParam[2] = { 0.0f, 1.0f, 0.0f };
	for (int i = 0; i < m_maxAttackNum; i++)
	{
		m_attackAnimation[i]=(EnPlayerAnimation)(enPlayerAnimationTwinAttack1+i);
		m_combineAnimation[i]= (EnPlayerAnimation)(enPlayerAnimationTwinAttackCombine1 + i);
	}
	m_stanAttack = std::make_unique<bool[]>(m_maxAttackNum);
	m_stanAttack[0] = false;
	m_stanAttack[1] = false;
	m_stanAttack[2] = false;

	DirectX::Model* model = m_skinModelTwin.GetBody();
	//メッシュをなめる
	for (auto& mesh : model->meshes)
	{
		for (auto& meshPart : mesh->meshParts)
		{
			ID3D11Buffer* vertexBuffer = meshPart->vertexBuffer.Get();
			D3D11_BUFFER_DESC vertexDesc;
			vertexBuffer->GetDesc(&vertexDesc);

			//超点数を求める
			int vertexCount = vertexDesc.ByteWidth / meshPart->vertexStride;

			//頂点バッファを取得
			D3D11_MAPPED_SUBRESOURCE subresource;
			Engine().GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			//頂点バッファから座標を取得して配列に積む
			char* pData = (char*)subresource.pData;
			for (int i = 0; i < vertexCount; i++)
			{
				CVector3 vertexPos = *((CVector3*)pData);
				m_twinVertexBufferVector.push_back(vertexPos);
				pData += meshPart->vertexStride;
				m_twinVertexBufferCount++;
			}
		}
	}
}

void CTwinSword::Update()
{
	CVector3 position;
	CQuaternion rotation;
	const CMatrix* boneMat;
	if (m_pPlayer->GetWeaponManager().GetIsAttack() || m_pPlayer->GetWeaponManager().GetDrawingWeapon())
	{
		boneMat = m_attackTwinBoneMat;
		position = m_attackTwinPosition;
		rotation = m_attackTwinRotation;
	}
	else
	{
		boneMat = m_normalTwinBoneMat;
		position = m_positionTwin;
		rotation = m_rotationTwin;
	}
	position.Mul(*boneMat);
	CMatrix rotMat = *boneMat;
	((CVector3*)rotMat.m[0])->Div(((CVector3*)rotMat.m[0])->Length());
	((CVector3*)rotMat.m[1])->Div(((CVector3*)rotMat.m[1])->Length());
	((CVector3*)rotMat.m[2])->Div(((CVector3*)rotMat.m[2])->Length());
	rotMat.m[3][0] = 0.0f;
	rotMat.m[3][1] = 0.0f;
	rotMat.m[3][2] = 0.0f;
	CQuaternion multi;
	multi.SetRotation(rotMat);
	multi.Multiply(rotation);
	rotation = multi;
	m_skinModelTwin.Update(position, rotation, CVector3::One);

	
}

void CTwinSword::Draw()
{
	//二つ目の剣用
	const CCamera& camera = GetGameCamera().GetCamera();
	m_skinModelTwin.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
}

SWeaponEnemyAttackInfo CTwinSword::EnemyAttackPositionDecide()
{
	const CMatrix& mat = *m_attackBoneMat;
	CVector3 pos;
	pos.x = mat.m[3][0];
	pos.y = mat.m[3][1];
	pos.z = mat.m[3][2];
	CVector3 manip;
	manip.x = mat.m[1][0];
	manip.x = mat.m[1][1];
	manip.x = mat.m[1][2];
	manip.Normalize();
	manip.Scale(0.3f);
	pos += manip;

	const CMatrix& mat2 = *m_attackTwinBoneMat;
	CVector3 pos2;
	pos2.x = mat2.m[3][0];
	pos2.y = mat2.m[3][1];
	pos2.z = mat2.m[3][2];
	CVector3 manip2;
	manip2.x = mat2.m[1][0];
	manip2.x = mat2.m[1][1];
	manip2.x = mat2.m[1][2];
	manip2.Normalize();
	manip2.Scale(0.3f);
	pos2 += manip2;

	SWeaponEnemyAttackInfo info;
	info.isAttack = true;
	info.attackPos[0] = pos;
	info.attackPos[1] = pos2;
	return {info};
}

SWeaponTraceDrawInfo CTwinSword::WeaponTraceDraw()
{
	CVector3 xVec = *(CVector3*)m_skinModel.GetWorldMatrix().m[2];
	xVec.Normalize();
	xVec *= -1.0f;
	xVec.Scale(0.1f);
	CVector3 position = *(CVector3*)m_attackBoneMat->m[3];
	CVector3 manip = *(CVector3*)m_attackBoneMat->m[2];
	manip.Normalize();
	CVector3 manip2 = manip;
	manip.Scale(0.0f);
	manip2.Scale(0.65f);
	position.Add(xVec);
	CVector3 position2 = position + manip;
	CVector3 position3 = position + manip2;

	SWeaponTraceDrawInfo TraceInfo;
	TraceInfo.rootPos[0] = position2;
	TraceInfo.pointPos[0] = position3;
	TraceInfo.isDraw = true;

	xVec = *(CVector3*)m_skinModelTwin.GetWorldMatrix().m[2];
	xVec.Normalize();
	xVec.Scale(0.1f);
	CVector3 positionTwin = *(CVector3*)m_attackTwinBoneMat->m[3];
	CVector3 manipTwin = *(CVector3*)m_attackTwinBoneMat->m[2];
	manipTwin.Normalize();
	CVector3 manip2Twin = manipTwin;
	manipTwin.Scale(0.0f);
	manip2Twin.Scale(0.65f);
	positionTwin.Add(xVec);
	CVector3 position4 = positionTwin + manipTwin;
	CVector3 position5 = positionTwin + manip2Twin;

	TraceInfo.rootPos[1]=position4;
	TraceInfo.pointPos[1]=position5;
	return { TraceInfo };
}