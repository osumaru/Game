#include "stdafx.h"
#include "Result.h"
#include "../../Player/Player.h"


CResult::CResult()
{
}


CResult::~CResult()
{
}

void CResult::Init()
{
	m_resultTexture.Load(L"Assets/sprite/YouDied.png");
	m_result.Init(&m_resultTexture);
	m_result.SetPosition({ -1.0f, -1.0f });
	m_result.SetSize({ 400.0f,200.0f });
	m_result.SetAlpha(0.0f);
}

void CResult::Update()
{


}

void CResult::Draw()
{
	//�v���C���[�������Ă��邩�̔���
	if (!GetPlayer().GetIsDied()) { return; }
	m_result.Draw();

}