#pragma once
class CGameSound: public IGameObject
{
public:
	CGameSound();
	~CGameSound();
	bool Start();
	void Update();
	void SetIsShop(const bool set)
	{
		m_isShop = set;
	}
	void Set3DSoundPosition(const CVector3 pos)
	{
		m_3dSoundPosition = pos;
		m_backSound[enBossBgm].SetPosition(m_3dSoundPosition);
	}

private:
	enum EnSoundState
	{
		enWorldBgm,			//���[���h�}�b�v�ړ�����BGM
		enTownBgm,			//���ɓ���������BGM
		enBattleBgm,		//�퓬����BGM
		enShopBgm,			//���X��BGM
		enBossBgm,			//�{�X���BGM
		enBgmNum			//BGM�̐�
	};
	CSoundSource		m_backSound[5];
	EnSoundState		m_soundState = enWorldBgm;
	const float			MENU_SOUND_VOLUME = 0.5f;
	const float			MASTER_VOLUME = 0.3f;			//BGM�̉���
	const float			SHOP_MASTER_VOLUME = 0.1f;		//�V���b�v��BGM�̉���
	CVector3			m_3dSoundPosition = CVector3::Zero;
	bool				m_isMenu;					
	bool				m_isShop = false;
	bool				m_isTown;
};

