#include "Bow.h"
#include "../Player.h"
#include "../PlayerArrow.h"
#include "../../Camera/GameCamera.h"

CBow::~CBow()
{

}

void CBow::Release()
{
	for (auto& arrow : m_arrowList)
	{
		Delete(arrow);
	}
	m_arrowList.clear();
}

void CBow::Init()
{
	m_attackBoneMat = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"LeftHand");
	m_position = { 0.0f, 0.0f, -10.0f };
	m_rotation = CQuaternion::Identity;
	CQuaternion multi;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation.Multiply(multi);

	m_attackRotation = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_attackRotation.Multiply(multi);
	m_attackPosition = { 10.0f, 0.0f, 0.0f };
	m_skinModel.Load(L"Assets/modelData/LongBow.cmo", NULL);

	m_texture = TextureResource().LoadTexture(L"Assets/sprite/arrowTag.png");
	m_tag.Init(m_texture);
	m_tag.SetPosition({ 0.0f,0.0f });
	m_tag.SetSize({ 50.0f,50.0f });
	m_tag.SetAlpha(0.7f);

	m_hitEffectParam = std::make_unique<SHitEffectParam[]>(1);
	m_hitEffectParam[0] = { 0.0f, 1.0f, 0.0f };
}

void CBow::Update()
{
	std::list<CPlayerArrow*>::iterator it;
	it = m_arrowList.begin();
	it = m_arrowList.begin();
	while (it != m_arrowList.end())
	{
		if ((*it)->IsDelete())
		{
			//éÄñSÇµÇƒÇ¢ÇΩÇÁÉäÉXÉgÇ©ÇÁçÌèú
			CPlayerArrow* enemy = *it;
			it = m_arrowList.erase(it);
		}
		else
		{
			it++;
		}
	}

	if (!m_pPlayer->GetWireAction().IsWireMove() && Pad().GetLeftTrigger())
	{
		GetGameCamera().SetCmareaState(GetGameCamera().enArrow);
		m_isZoom = true;
	}
	else
	{
		GetGameCamera().SetCmareaState(GetGameCamera().enNormal);
		m_isZoom = false;
	}
}

void CBow::AfterDraw()
{
	//ÉJÉÅÉâÇêÿÇËë÷Ç¶ÇƒÇÈéûÇÕï`âÊÇ∑ÇÈ
	if (m_isZoom)
	{
		m_tag.Draw();
	}
}

void CBow::ArrowCreate()
{
	CPlayerArrow* arrow = New<CPlayerArrow>(PRIORITY_ARROW);
	m_arrowList.push_back(arrow);
}


void CBow::ArrowDelete(std::list<CPlayerArrow*>::iterator it)
{
	Delete(*it);
	m_arrowList.erase(it);
}