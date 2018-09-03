#pragma once
#pragma once
//�I�u�W�F�N�g�̃C���^�[�t�F�[�X

class IGameObject : Uncopyable
{
public:
	//�R���X�g���N�^
	IGameObject();
	
	//���z�f�X�g���N�^(���N���X�̃f�X�g���N�^�͉��z�֐��łȂ��Ă͂Ȃ�Ȃ��B)
	virtual ~IGameObject();

	//�������֐�
	virtual bool Start() { return true; }

	//�X�V�֐�
	virtual void Update() = 0;

	//�`��֐�
	virtual void Draw() {};

	//Draw���ĂяI�������ɂ�����x�ĂԊ֐��B�A���t�@�u�����h�������X�v���C�g��|�X�g�G�t�F�N�g��؂��ăX�v���C�g��`�悵�����Ƃ��Ɏg���B
	virtual void AfterDraw() {};

	//���ʑO�Ɉ�񂾂��Ă΂��֐�
	virtual void BeforeDead() {};

	void Reset()
	{
		m_isStart = false;
		m_isDelete = false;
	}

	//����ł��邩�H
	bool IsDelete() const
	{
		return m_isDelete;
	}
	//�������ς݂��H
	bool IsStart() const
	{
		return m_isStart;
	}


	void Dead()
	{
		m_isDelete = true;
	}

	void Starter()
	{
		if (!m_isStart && !m_isDelete)
		{
			m_isStart = Start();
		}
	}

	void Updater()
	{
		if (m_isStart && m_isActive && !m_isDelete)
		{
			Update();
		}
	}

	void Drawer()
	{
		if (m_isStart && m_isActive && !m_isDelete)
		{
			Draw();
		}
	}

	void AfterDrawer()
	{
		if (m_isStart && m_isActive && !m_isDelete)
		{
			AfterDraw();
		}
	}

	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

	bool IsActive()
	{
		return m_isActive;
	}
private:
	bool m_isDelete;			//�C���X�^���X���������Ɍ��Ă�t���O
	bool m_isStart;				//���������Ă邩�̃t���O
	bool m_isActive;			//�A�N�e�B�u���ǂ����̃t���O
};