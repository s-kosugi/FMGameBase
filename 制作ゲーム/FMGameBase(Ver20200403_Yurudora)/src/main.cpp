#include <DxLib.h>
#pragma warning(disable: 26495)
#include "EffekseerForDXLib.h"
#include "cGame.h"
#include "DrawCtrl\cDrawCtrl.h"
#include "..\resource.h"
#ifdef DEBUG
	#include <direct.h>
	#include "DebugFunc/cDebugFunc.h"
	#include <string>
#endif
void MainLoop(void);
int  InitEffekseer(void);

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
#ifdef DEBUG
	// �A�v���P�[�V�������O���o��
	SetOutApplicationLogValidFlag(TRUE);
	SetUseDateNameLogFile(TRUE);
	
	_mkdir("Log");
	int ret = SetApplicationLogSaveDirectory("Log");

#else
	SetOutApplicationLogValidFlag(FALSE);
#endif
	
	// �E�B���h�E�^�C�g��
	SetWindowText("FMGameBase");

	// �A�C�R���ݒ�
	SetWindowIconID(MAINICON);

#ifdef DEBUG
	// �E�B���h�E���[�h
	ChangeWindowMode(true);
#else
	// �E�B���h�E���[�h
	ChangeWindowMode(false);
#endif


	// ���d�N���֎~
	SetDoubleStartValidFlag(FALSE);
	// ��ʃT�C�Y�ƃJ���[�r�b�g���̎w��
	SetGraphMode(cGame::GetInstance().GetWindowWidth(), cGame::GetInstance().GetWindowHeight(), 32);

	// DirectX9���g�p����悤�ɂ���B(DirectX11����)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
		return -1;			// �G���[���N�����璼���ɏI��

	// Effekseer�̏�����
	if (InitEffekseer() == -1) return -1;

	//�`���𗠉�ʂɐݒ�(�_�u���o�b�t�@)
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
		return -1;

	// ALT�L�[��F10�L�[�𖳌��ɂ���
	SetSysCommandOffFlag(1);

	// �E�B���h�E����A�N�e�B�u��Ԃł����삳����
	SetAlwaysRunFlag(TRUE);

	// �`�惊�X�g�̐����A������
	cDrawCtrl::GetInstance().ClearDrawList();

	// �Q�[���N���X�̍쐬
	cGame& game = cGame::GetInstance();

	// ������
	game.Initialize();
#ifdef DEBUG
	cDebugFunc::GetInstance().PushDebugLog("ShaderVersion = " + std::to_string(GetValidShaderVersion()));
	cDebugFunc::GetInstance().PushDebugLog("MultiDrawScreenNum = " + std::to_string(GetMultiDrawScreenNum()));
#endif
	// ���C�����[�v
	MainLoop();

	// �j��
	game.Finalize();

	// Effekseer���I������B
	// ���t���X�N���[�����ɃG���[����������׈�U�R�����g�A�E�g
	//Effkseer_End();

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

//==========================================================================================
// ���C�����[�v
//==========================================================================================
void MainLoop(void)
{
	cGame& game = cGame::GetInstance();

	for (;;) {
		int StartTime;

		// �v���J�n������ۑ�
		StartTime = GetNowCount();

		// ��ʂ̃N���A
		ClearDrawScreen();
		// �Q�[���̍X�V
		game.Update();
		// �`��
		game.Draw();

		// ��ʂ��X�V(��������+����ʂ̓��e��\��ʂɃR�s�[)
		ScreenFlip();

		// ���b�Z�[�W����
		if (ProcessMessage() != 0)
			return;

		// 1/60�b���z����܂őҋ@������
		while(GetNowCount() < StartTime + 1000 / (int)game.GetFPS());
	}
}

//==========================================================================================
// Effekseer�֘A�̏�����
//==========================================================================================
int InitEffekseer(void)
{
	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseer��2D�`��̐ݒ������B
	Effekseer_Set2DSetting(cGame::GetInstance().GetWindowWidth(), cGame::GetInstance().GetWindowHeight());

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

	return 0;
}