#pragma once
class Skelton;
class Keyframe;


/*!
*@brief	�A�j���[�V�����N���b�v�̃w�b�_�[�B
*/
struct AnimClipHeader {
	std::uint32_t numKey;				//!<�L�[�t���[���̐��B
	std::uint32_t numAnimationEvent;	//!<�A�j���[�V�����C�x���g�̐��B
};
/*!
*@brief	�A�j���[�V�����C�x���g
*/
struct AnimationEvent {
	float	invokeTime;					//!<�A�j���[�V�����C�x���g���������鎞��(�P��:�b)
	std::uint32_t eventNameLength;		//!<�C�x���g���̒����B
};
/*!
*@brief	�L�[�t���[���B
*/
struct Keyframe {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	Matrix transform;			//!<�g�����X�t�H�[���B
};
/*!
*@brief	�L�[�t���[���B
*/
struct KeyframeRow {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	Vector3 transform[4];		//!<�g�����X�t�H�[���B
};

class AnimationClip
{
public:
	void Load(wchar_t* filePath);


	bool Update();

	std::vector<Matrix> GetLocalMatrix()
	{
		return m_localMatrix;
	}

	void Play();

private:
	bool m_isPlaying;
	std::wstring m_clipName;	//!<�A�j���[�V�����N���b�v�̖��O�B
	std::vector<std::unique_ptr<Keyframe>>			m_keyframes;				//�L�[�t���[���B
	std::vector<std::vector<Keyframe*>> m_keyFramePtrListArray;
	std::vector<Keyframe*>* m_topBoneKeyFrameList;
	std::vector<Matrix> m_localMatrix;
	float m_frameTime;
	int	m_currentFrameNo;
};