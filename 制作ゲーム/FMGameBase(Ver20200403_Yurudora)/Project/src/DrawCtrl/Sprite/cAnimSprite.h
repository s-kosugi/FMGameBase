#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cAnimSprite.h												*/
/*  @brief		:	�A�j���[�V�����X�v���C�g�N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/14													*/
/*																				*/
/*==============================================================================*/

#include "cSprite.h"
#include <string>
#include <vector>

//================================================================================================
// �A�j���[�V�����X�v���C�g�N���X
class cAnimSprite : public cSprite
{
public:
	cAnimSprite(const std::string& filename);
	~cAnimSprite();

	void Initialize(void);
	void Update(void);
	void Finalize(void);

	//---------------------------------------------------------------------------------------------
	// �A�j���[�V�������
	struct AnimationData {
		std::string         Name;				// �A�j���[�V������
		std::vector<int>    Frames;				// �t���[���f�[�^
		float               Interval = 0.0f;	// �X�V�Ԋu(�b�P��)
		bool                Loop = false;       // ���[�v�t���O
	};

	// �A�j���[�V�����̕ύX
	void ChangeAnime(const std::string& animName);
	// �A�j���[�V�����̕ύX
	void ChangeAnime(int animID);

	// �A�j���[�V�����̃R�s�[
	void CopyAnime(const cAnimSprite& src);

	//---------------------------------------------------------------------------------------------
	// Getter
	inline POINT	GetFrameSize(void) { return m_FrameSize; };
	inline int		GetFrameCols(void) { return m_nFrameCols; };
	inline int		GetFrameRows(void) { return m_nFrameRows; };
	inline int		GetCurrentAnimeID(void) { return m_nCurrentAnimeID; };
	inline float	GetCurrentFrame(void) { return m_fCurrentFrame; };
	inline float	GetCurrentAnimeFPS(void) { return m_fCurrentAnimeFPS; };
	inline int		IsStop(void) { return m_bStopFlag; };
	inline float	GetPlaySpeedRate(void) { return m_fPlaySpeedRate; };

	//---------------------------------------------------------------------------------------------
	// Setter
	inline void		SetFrameCols(short col) { m_nFrameCols = col; };
	inline void		SetFrameRows(short row) { m_nFrameRows = row; };
	inline void		SetPlayRate(float rate) { m_fPlaySpeedRate = rate; };
	inline void		SetCurrentFrame(float frame) { m_fCurrentFrame = frame; };


	// ��FMGB�݊��p�A�j���[�V�����Z�b�g�֐�
	void SetAnimation(int Startx, int Starty, int width, int height, short AnimMax, float AnimTime);

protected:

	//---------------------------------------------------------------------------------------------
	// �A�j���[�V�����f�[�^���X�g
	typedef std::vector<AnimationData> ANIMATION_LIST;


private:

	// ASS�t�@�C������̃X�v���C�g�L�[ID
	enum ASS_KEY
	{
		ASS_KEY_FILE,           // �g�p����t�@�C����
		ASS_KEY_FRAME,          // �t���[���I�u�W�F�N�g
		ASS_KEY_WIDTH,          // �t���[���̕�
		ASS_KEY_HEIGHT,         // �t���[���̍���
		ASS_KEY_COLS,           // ���ɕ���ł���t���[���̐�
		ASS_KEY_ROWS,           // �c�ɕ���ł���t���[���̐�
		ASS_KEY_ANIMATIONS,     // �A�j���[�V�����I�u�W�F�N�g
		ASS_KEY_FRAMES,         // �A�j���[�V�����Ŏg�p����t���[���ԍ�
		ASS_KEY_INTERVAL,       // �A�j���[�V�����X�V�Ԋu(�b�P��)
		ASS_KEY_LOOP,           // �A�j���[�V�������[�v�t���O

		ASS_KEY_MAX             // ASS�L�[�̐�
	};

	bool LoadASS(const std::string& filename);		// ASS�t�@�C���̓Ǎ��Ɖ��


	// �A�j���[�V�����S�̂ŕK�v�ȕϐ�
	POINT		m_FrameSize;		// 1�����̑傫��
	short		m_nFrameCols;		// ���ɕ���ł���t���[����
	short		m_nFrameRows;		// �c�ɕ���ł���t���[����

	ANIMATION_LIST	m_AnimationList;            // �A�j���[�V�������X�g

	// �A�j���[�V�����Đ��p�ϐ�
	int				m_nCurrentAnimeID;		// ���݂̃A�j���[�V����ID
	float			m_fCurrentFrame;		// ���݂̃A�j���[�V�����t���[��
	float			m_fCurrentAnimeFPS;		// ���݂̃A�j���[�V�����X�V���x
	bool			m_bStopFlag;			// ��~�t���O
	float			m_fPlaySpeedRate;		// �A�j���[�V�����̍Đ����x�{��


	//---------------------------------------------------------------------------------------------
	// �萔
	static const char* m_sKeyName[ASS_KEY_MAX];   // �L�[��

};
//=================================================================================================
