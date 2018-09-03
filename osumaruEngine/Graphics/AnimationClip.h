#pragma once
class Skelton;
class Keyframe;


/*!
*@brief	�A�j���[�V�����N���b�v�̃w�b�_�[�B
*/
struct SAnimClipHeader {
	std::uint32_t numKey;				//!<�L�[�t���[���̐��B
	std::uint32_t numAnimationEvent;	//!<�A�j���[�V�����C�x���g�̐��B
};
/*!
*@brief	�A�j���[�V�����C�x���g
*/
struct SAnimationEvent {
	float	invokeTime;					//!<�A�j���[�V�����C�x���g���������鎞��(�P��:�b)
	std::uint32_t eventNameLength;		//!<�C�x���g���̒����B
};
/*!
*@brief	�L�[�t���[���B
*/
struct SKeyframe {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	CMatrix transform;			//!<�g�����X�t�H�[���B
};
/*!
*@brief	�L�[�t���[���B
*/
struct SKeyframeRow {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	CVector3 transform[4];		//!<�g�����X�t�H�[���B
};

//�A�j���[�V�����N���b�v(��̃A�j���[�V�������Ǘ�����N���X)

class CAnimationClip : Uncopyable
{
public:
	/*
	�A�j���[�V������ǂݍ��ފ֐��B
	filePath	�A�j���[�V�����t�@�C���̃p�X
	*/
	void Load(wchar_t* filePath);


	//�X�V�֐��B
	void Update(float deltaTime);

	//�{�[���̍s����擾�B
	const std::vector<CMatrix>& GetLocalMatrix() const
	{
		return m_localMatrix;
	}

	//�A�j���[�V�������Đ��B
	void Play();
	
	//���[�v�t���O��ݒ�B
	void SetIsLoop(bool isLoop)
	{
		m_isLoop = isLoop;
	}

	//���[�v�t���O���擾�B
	bool IsLoop() const
	{
		return m_isLoop;
	}

	//�Đ������̃t���O���擾�B
	bool IsPlay() const
	{
		return m_isPlay;
	}

private:
	bool									m_isPlay;					//�Đ������H
	bool									m_isLoop;					//���[�v���Ă邩�H
	std::wstring							m_clipName;					//�A�j���[�V�����N���b�v�̖��O�B
	std::vector<std::unique_ptr<SKeyframe>>	m_keyframes;				//�L�[�t���[���B
	std::vector<std::vector<SKeyframe*>>	m_keyFramePtrListArray;		//�{�[�����̃L�[�t���[���̃��X�g
	std::vector<SKeyframe*>*				m_topBoneKeyFrameList;		//��ԍŏ��̃L�[�t���[��
	std::vector<CMatrix>					m_localMatrix;				//�{�[���̍s���ۑ����邽�߂̂���
	float									m_frameTime;				//�t���[����i�߂邽�߂̃^�C�}�[
	int										m_currentFrameNo;			//���݂̃t���[���i���o�[
};