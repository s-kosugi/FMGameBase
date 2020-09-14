#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cGame.h														*/
/*  @brief		:	�Q�[���N���X												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/11/14													*/
/*																				*/
/*==============================================================================*/

#include "DxLib.h"
#include "BaseObject\IBaseObject.h"
#include "Utility/Vector/cVector2.h"

//===============================================================================
// �Q�[���N���X
class cGame : public IBaseObject
{
public:
	void Initialize(void) override;
	void Update(void) override;
	void Draw(void);


	// �����̔���
	static int Random(int min, int max);

	//-----------------------------------------------------------------------------------------
	// Getter
	//-----------------------------------------------------------------------------------------
	// FPS�̎擾
	inline unsigned int GetFPS(void) { return m_nFPS; };

	// �v���C�G���A�̎擾
	inline RECT GetPlayArea(void) { return m_PlayArea; };
	inline int  GetPlayAreaWidth(void) { return m_PlayArea.right - m_PlayArea.left; };
	inline int  GetPlayAreaHeight(void) { return m_PlayArea.bottom - m_PlayArea.top; };

	// �E�B���h�E�T�C�Y�̎擾
	inline int GetWindowWidth(void) { return WINDOW_SIZE_X; };
	inline int GetWindowHeight(void) { return WINDOW_SIZE_Y; };

	// �E�B���h�E�̒��S�ʒu���擾
	inline cVector2 GetWindowCenter(void) { cVector2 ret((float)(WINDOW_SIZE_X / 2), (float)(WINDOW_SIZE_Y / 2)); return ret; };

	// �X�V�̉񐔂̎擾(1Frame��)
	inline int GetOneFrameUpdate(void) { return m_nOneFrameUpdate; };

	// �f���^�^�C���擾
	inline float GetDeltaTime(void) const { return m_fDeltaTime * m_fDeltaTimeScale; };

	// �E�B���h�E�ʒu�����_�ɂ���
	void SetWindowPosOrigin(void);

	// �E�B���h�E�̈ʒu�������ʒu�ɂ���
	void SetWindowPosDefault(void);

	//-----------------------------------------------------------------------------------------
	// Setter
	//-----------------------------------------------------------------------------------------
	// FPS�̐ݒ�
	inline void SetFPS(unsigned int fps) { m_nFPS = fps; };
	// FPS�����Z�b�g
	inline void ResetFPS(void) { m_nFPS = DEFAULT_FPS; };
	// �X�V�̉񐔂̃Z�b�g(1Frame��)
	inline void SetOneFrameUpdate(int num) { m_nOneFrameUpdate = num; };
private:
	// �X�V����t���[���J�E���g�̌v�Z
	void CalcFrameCount( void );

	// �V�X�e���L�[�̃`�F�b�N
	void CheckSystemKey(void);

	// �E�B���h�E�ʒu�̐؂�ւ�
	void ChangeWindowPos(void);

	//-----------------------------------------------------------------------------------------
	// �ϐ�
	//-----------------------------------------------------------------------------------------
	unsigned int	m_nFPS;				// FPS
	int				m_nOneFrameUpdate;	// �X�V��(1Frame��)
	float			m_fDeltaTime;		// �f���^�^�C��
	float			m_fDeltaTimeScale;	// �f���^�^�C���{��
	int				m_nFrameCount;		// �t���[���J�E���g
	int				m_nStartTime;		// �t���[���v���J�n����
	int             m_nPrevTime;		// 1�t���[���O�̎���

	POINT			m_DefaultWindowPos;	// �����E�B���h�E�ʒu

	RECT			m_PlayArea;			// �v���C�G���A

	//-----------------------------------------------------------------------------------------
	// �萔
	//-----------------------------------------------------------------------------------------
	static const unsigned int DEFAULT_FPS = 60; // �f�t�H���gFPS
	static const float		  MAX_DELTA_TIME;	// �ő�f���^�^�C��
	static const float		  ONE_MILL_SECOND;	// �P�~���b
	static const int		  CALC_FRAME_COUNT; // ���ς��v�Z����t���[���̐�

	static const int		  WINDOW_SIZE_X;	// �E�B���h�E��
	static const int		  WINDOW_SIZE_Y;	// �E�B���h�E����

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cGame(void);     //  ������̐������֎~
	cGame(IBaseObject* parent);
	cGame(IBaseObject* parent, const std::string& name);
	~cGame(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cGame(const cGame& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cGame& operator = (const cGame& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:
	// �V���O���g���I�u�W�F�N�g�ɂ�DELETE�A�N�Z�X�������Ȃ��B
	IBaseObject* Finalize(void) override { IBaseObject::Finalize(); return nullptr; };

	static cGame& GetInstance(void) {
		static cGame instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
//-----------------------------------------------------------------------------------------------------
};