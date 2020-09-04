#pragma once
/*==============================================================================*/
/*																				*/
/*	@file title	:	cDrawCtrl.h													*/
/*  @brief		:	�`��R���g���[���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include "IDrawBase.h"
#include "Sprite\cSprite.h"
#include "Effect\cEffect.h"
#include "Surface/cSurface.h"
#include "Transition\cTransition.h"
#include "Model/cModel.h"
#include "../BaseObject/IBaseObject.h"
#include <list>
#include "Text/cText.h"

//===============================================================================
// �`��R���g���[���N���X
class cDrawCtrl : public IBaseObject
{
public:
	void Initialize(void);
	void Draw(void);
	IBaseObject* Finalize(void);

	// �`��I�u�W�F�N�g�̓o�^
	void RegistDrawObject(cSprite& obj, const std::string& filename);

	// �`��I�u�W�F�N�g�̓o�^
	void RegistDrawObject(cEffect& obj, const std::string& filename);

	// �T�[�t�F�C�X�̓o�^
	void RegistSurface(cSurface& obj, int width, int height, bool alpha);

	// �g�����W�V�����̓o�^
	void RegistTransition(cTransition& obj, const std::string& filename);

	// ���f���̓o�^
	void RegistDrawObject(cModel& obj, const std::string& filename);

	// �e�L�X�g�̓o�^
	void RegistDrawObject(cText& obj);

	// �e�L�X�g�̓o�^(�t�H���g��������)
	void RegistDrawObject(cText& obj, const std::string& fontname, int Size, int Thick, int FontType, int EdgeSize, int Italic);

	// �`��t�@�C���Ǎ�����
	// �߂�l : �O���t�B�b�N�n���h��
	int LoadDrawFile(const std::string& filename, DRAWTYPE type);

	// �`��I�u�W�F�N�g�̓o�^����
	void RemoveDrawObject(const IDrawBase* obj);

	// �T�[�t�F�C�X�̓o�^����
	void RemoveSurface(const cSurface* obj);

	// �e�L�X�g�̕��������擾����
	int GetTextWidth(cText* obj);

	// �`�惊�X�g�̃N���A
	inline void ClearDrawList(void) { m_listDrawObject.clear(); m_listFileLoaded.clear(); };

	// �`��D��ύX�v��
	inline void RequestChangeDrawPriority(void) { m_bPriChageRequest = true; };

	// �X�N���[���V���b�g�̎B�e�v��
	inline void RequestScreenShot(void) { m_bScreenShot = true; };

private:
	// �X�v���C�g�̕`��
	void DrawSprite(cSprite* obj);
	// �G�t�F�N�g�̕`��
	void DrawEffect(cEffect* obj);
	// �T�[�t�F�C�X�̕`��
	// ret : �T�[�t�F�C�X�`�搬�� : true
	bool DrawSurface(cSurface* obj);
	// �T�[�t�F�C�X�̕`��J�n
	void BeginSurface(IDrawBase* obj);
	// �g�����W�V�����̕`��
	void DrawTransition(cTransition* obj);
	// ���f���̕`��
	void DrawModel(cModel* obj);
	// �e�L�X�g�̕`��
	void DrawTextObj(cText* obj);

	//--------------------------------------------------------------------------------------
	// ���X�g�̏�����r�֐�
	// DrawObject�̕\���D�悪�Ⴂ���̂����ɕ`�������
	// static�����Ȃ���std����C���X�^���X�ŌĂт����׃G���[���o��
	static bool CompAscPriority(IDrawBase* left, IDrawBase* right) { return left->GetPriority() < right->GetPriority(); };

	//--------------------------------------------------------------------------------------
	// �����O���t�B�b�N�n���h�������I�u�W�F�N�g�����邩��T��
	// �߂�l : true �������� false ������Ȃ�����
	bool SearchSameGrHandle(const IDrawBase* obj);

	// �����σt�H���g�\����
	struct FontCreated
	{
		std::string	FontName;
		int			Size = 30;
		int			Thick = 0;
		int			FontType = 0;
		int			EdgeSize = 0;
		int			Italic = 0;
		int			Handle = -1;		// �����ς݃t�H���g�n���h��
	};

	//--------------------------------------------------------------------------------------
	// �����t�H���g�������ς݂���T��
	// �߂�l : -1 �����t�H���g��������Ȃ����� -1�ȊO �t�H���g�n���h��
	int SearchSameFont(FontCreated& font);

	//--------------------------------------------------------------------------------------
	// �ǂݍ��ݍς݃t�@�C�����疕��
	void RemoveFileLoaded(std::string filename);

	//--------------------------------------------------------------------------------------
	// �X�N���[���V���b�g�ۑ�
	void SaveScreenFile(void);

	//--------------------------------------------------------------------------------------
	// �t�@�C���ǂݍ��݊֘A
	// �ǂݍ��݃t�@�C���\����
	struct FileLoaded
	{
		std::string FileName;
		int GraphHandle = -1;
		DRAWTYPE Type = DRAWTYPE::SPRITE;
	};
	// �ǂݍ��ݍς݃t�@�C�����X�g
	std::list<FileLoaded> m_listFileLoaded;

	//--------------------------------------------------------------------------------------
	// �`��I�u�W�F�N�g���X�g
	std::list<IDrawBase*> m_listDrawObject;

	// �`��D��ύX�v��
	bool m_bPriChageRequest;

	// �X�N���[���V���b�g�ۑ��v��
	bool m_bScreenShot;


	// �����ς݃t�H���g���X�g
	std::list<FontCreated> m_listFontCreated;

	// �������T�[�t�F�C�X�|�C���^
	IDrawBase* m_pBeginSurface;
	// �T�[�t�F�C�X�����҂����X�g
	std::list<IDrawBase*> m_listSurfaceWait;

	//--------------------------------------------------------------------------------------
	// �萔
	const int LOADGRAPH_FAILED = -1;		 // �摜�Ǎ����s
	const int FONT_NOTFAUND = -1;			 // �t�H���g��������Ȃ�
	const int EFFEKSEER_NOTPLAYING = -1;	 // �G�t�F�N�g���Đ�

//-----------------------------------------------------------------------------------------------------
// �V���O���g���p
private:
	cDrawCtrl(void);     //  ������̐������֎~
	cDrawCtrl(IBaseObject* parent);
	cDrawCtrl(IBaseObject* parent, const std::string& name);
	~cDrawCtrl(void) {};   // ������̍폜���֎~(�f�X�g���N�^��private�ɂ��鎖�ŊO���폜�s��)
	cDrawCtrl(const cDrawCtrl& t);       // �I�u�W�F�N�g�̕����֎~(�R�s�[�R���X�g���N�^�̃I�[�o���C�h)
	cDrawCtrl& operator = (const cDrawCtrl& t) {};  // �I�u�W�F�N�g�̕����֎~(������Z�q�̃I�[�o�[���[�h)
public:

	static cDrawCtrl& GetInstance(void) {
		static cDrawCtrl instance;   // �B��̎��̂ł���I�u�W�F�N�g�Astatic�ϐ����g�p���鎖�łP�̋��L�̕ϐ��ƂȂ�
		return instance;    // ��ɋ��ʂ̃C���X�^���X��Ԃ�
	};
	//-----------------------------------------------------------------------------------------------------
};