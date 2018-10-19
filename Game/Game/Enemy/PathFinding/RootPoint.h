/*
*	�o�H�T���p�̃|�C���g�N���X
*/

#pragma once

class CRootPoint : public IGameObject
{
public:
	//������
	//position			���W
	//listNumber		���X�g�̔ԍ�
	void Init(CVector3 position, int listNumer);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

	//���W���擾
	const CVector3& GetPosition()
	{
		return m_position;
	}

	//���X�g�Ɋi�[����Ă���ԍ����擾
	int GetListNumber()
	{
		return m_listNumber;
	}

private:
	CVector3 m_position;		//���W
	int      m_listNumber = 0;	//���X�g�Ɋi�[����Ă���ԍ�
};