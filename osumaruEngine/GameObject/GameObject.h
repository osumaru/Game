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

	//�񓯊��̏������֐�
	virtual bool AsyncStart(){ return true; }

	//�X�V�֐�
	virtual void Update() = 0;

	//�`��֐�
	virtual void Draw() {};

	//Draw���ĂяI�������ɂ�����x�ĂԊ֐��B�A���t�@�u�����h�������X�v���C�g��|�X�g�G�t�F�N�g��؂��ăX�v���C�g��`�悵�����Ƃ��Ɏg���B
	virtual void AfterDraw() {};

	//���ʑO�Ɉ�񂾂��Ă΂��֐�
	virtual void BeforeDead() {};

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

	//�A�N�e�B�u�t���O��ݒ�
	void SetIsActive(bool isActive)
	{
		m_isActiveUpdate = isActive;
		m_isActiveDraw = isActive;
	}

	//�X�V�̃A�N�e�B�u�t���O��ݒ�
	void SetIsActiveUpdate(bool isActive)
	{
		m_isActiveUpdate = isActive;
	}

	//�X�V���A�N�e�B�u���H
	bool IsActiveUpdate()
	{
		return m_isActiveUpdate;
	}

	//�`��̃A�N�e�B�u�t���O��ݒ�
	void SetIsActiveDraw(bool isActive)
	{
		m_isActiveDraw = isActive;
	}

	//�`�悪�A�N�e�B�u���H
	bool IsActiveDraw()
	{
		return m_isActiveDraw;
	}

	//�A�N�e�B�u���H
	bool IsActive()
	{
		return m_isActiveUpdate && m_isActiveDraw;
	}

	friend class CGameObjectManager;
private:

	//AsyncStart���ĂԊ֐�
	void AsyncStarter()
	{
		if (!m_isAsyncStart && !m_isDelete)
		{
			m_isAsyncStart = AsyncStart();
		}
	}

	//Start�֐����ĂԊ֐�
	void Starter()
	{
		if (!m_isStart && !m_isDelete)
		{
			m_isStart = Start();
		}
	}
	//Update�֐����ĂԊ֐�
	void Updater()
	{
		if (m_isStart && m_isAsyncStart && m_isActiveUpdate && !m_isDelete)
		{
			Update();
		}
	}
	//Draw�֐����ĂԊ֐�
	void Drawer()
	{
		if (m_isStart && m_isAsyncStart && m_isActiveDraw && !m_isDelete)
		{
			Draw();
		}
	}

	//AfterDrawer���ĂԊ֐�
	void AfterDrawer()
	{
		if (m_isStart && m_isAsyncStart && m_isActiveDraw && !m_isDelete)
		{
			AfterDraw();
		}
	}


	//���Z�b�g�֐��AAdd�ŃI�u�W�F�N�g�}�l�[�W���[�ɓo�^���ꂽ���̂�Delete�����Ƃ��ɌĂ�
	void Reset()
	{
		m_isStart = false;
		m_isDelete = false;
		m_isAsyncStart = false;
		m_isActiveUpdate = true;
		m_isActiveDraw = true;
	}
private:
	bool m_isDelete;			//�C���X�^���X���������Ɍ��Ă�t���O
	bool m_isStart;				//���������Ă邩�̃t���O
	bool m_isAsyncStart;		//�񓯊��̏����������Ă邩�̃t���O
	bool m_isActiveUpdate;		//�`�悪�A�N�e�B�u���ǂ����̃t���O
	bool m_isActiveDraw;		//�`�悪�A�N�e�B�u���ǂ����̃t���O
};