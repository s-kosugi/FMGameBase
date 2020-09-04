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
#include "BaseObject\IBaseSingleton.h"
#include "Utility/Vector/cVector2.h"

//===============================================================================
// �Q�[���N���X
class cGame : public IBaseSingleton<cGame>
{
public:
	~cGame();

	void Initialize(void);
	void Update(void);
	void Draw(void);
	IBaseObject* Finalize(void);


	// �����̔���
	static int Random(int min, int max);

	// FPS�̎擾
	inline unsigned int GetFPS(void) { return m_nFPS; };

	// �v���C�G���A�̎擾
	inline RECT GetPlayArea(void) { return m_PlayArea; };
	inline int  GetPlayAreaWidth(void) { return m_PlayArea.right - m_PlayArea.left; };
	inline int  GetPlayAreaHeight(void) { return m_PlayArea.bottom - m_PlayArea.top; };
	inline cVector2 GetPlayAreaCenter( void ){
		cVector2 center;
		center.x = (m_PlayArea.right - m_PlayArea.left) / 2.0f;
		center.y = (m_PlayArea.bottom - m_PlayArea.top) / 2.0f;
		return center;
	};

	// �E�B���h�E�T�C�Y�̎擾
	inline int GetWindowWidth(void) { int x, y; GetWindowSize(&x, &y); return x; };
	inline int GetWindowHeight(void) { int x, y; GetWindowSize(&x, &y); return y; };

	// �E�B���h�E�̒��S�ʒu���擾
	inline cVector2 GetWindowCenter(void) { int x, y; GetWindowSize(&x, &y); cVector2 ret((float)(x / 2), (float)(y / 2)); return ret; };

	// �X�V�̉񐔂̃Z�b�g(1Frame��)
	inline int GetOneFrameUpdate(void) { return m_nOneFrameUpdate; };


	// FPS�̐ݒ�
	inline void SetFPS(unsigned int fps) { m_nFPS = fps; };
	// FPS�����Z�b�g
	inline void ResetFPS(void) { m_nFPS = DEFAULT_FPS ;};

	// �X�V�̉񐔂̃Z�b�g(1Frame��)
	inline void SetOneFrameUpdate(int num) { m_nOneFrameUpdate = num; };

private:
	// FPS
	unsigned int m_nFPS;

	// �X�V��(1Frame��)
	int			 m_nOneFrameUpdate;

	// �v���C�G���A
	RECT	m_PlayArea;


	// �f�t�H���gFPS
	static const unsigned int DEFAULT_FPS = 60;

	// �v���C�G���A�̒�`
	static const int  PLAYAREA_TOP = 0;
	static const int  PLAYAREA_BOTTOM = 600;
	static const int  PLAYAREA_LEFT = 0;
	static const int  PLAYAREA_RIGHT = 600;

};