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
#include "Surface/cSurFace.h"
#include "Transition\cTransition.h"
#include "../BaseObject/IBaseSingleton.h"
#include <list>
#include "Surface\cSurFace.h"

//===============================================================================
// �`��R���g���[���N���X
class cDrawCtrl : public IBaseSingleton<cDrawCtrl>
{
public:
	~cDrawCtrl();

	void Initialize(void);
	void Draw(void);
	IBaseObject* Finalize(void);

	// �`��I�u�W�F�N�g�̓o�^
	void RegistDrawObject(cSprite& obj,const std::string& filename);

	// �`��I�u�W�F�N�g�̓o�^
	void RegistDrawObject(cEffect& obj, const std::string& filename);

	// �T�[�t�F�C�X�̓o�^
	void RegistSurface(cSurface& obj,int width,int height,bool alpha);

	// �g�����W�V�����̓o�^
	void RegistTransition(cTransition& obj, const std::string& filename);

	// �`��t�@�C���Ǎ�����
	// �߂�l : �O���t�B�b�N�n���h��
	int LoadDrawFile(const std::string& filename, DrawType type);

	// �`��I�u�W�F�N�g�̓o�^����
	void RemoveDrawObject(const IDrawBase* obj);

	// �T�[�t�F�C�X�̓o�^����
	void RemoveSurface(const cSurface* obj);

	// �`�惊�X�g�̃N���A
	inline void ClearDrawList(void) { m_listDrawObject.clear(); m_listFileLoaded.clear();};

	// �`��D��ύX�v��
	inline void RequestChangeDrawPriority(void) { m_bPriChageRequest = true;};
private:
	// �X�v���C�g�̕`��
	void DrawSprite(cSprite* obj);
	// �G�t�F�N�g�̕`��
	void DrawEffect(cEffect* obj);
	// �T�[�t�F�C�X�̕`��
	void DrawSurface(cSurface* obj);
	// �T�[�t�F�C�X�̕`��J�n
	void BeginSurface(IDrawBase* obj);
	// �g�����W�V�����̕`��
	void DrawTransition(cTransition* obj);

	//--------------------------------------------------------------------------------------
	// ���X�g�̏�����r�֐�
	// DrawObject�̕\���D�悪�Ⴂ���̂����ɕ`�������
	// static�����Ȃ���std����C���X�^���X�ŌĂт����׃G���[���o��
	static bool CompAscPriority(IDrawBase* left, IDrawBase* right) { return left->GetPriority() < right->GetPriority(); };

	//--------------------------------------------------------------------------------------
	// �����O���t�B�b�N�n���h�������I�u�W�F�N�g�����邩��T��
	// �߂�l : true �������� false ������Ȃ�����
	bool SearchSameGrHandle( const IDrawBase* obj );

	//--------------------------------------------------------------------------------------
	// �ǂݍ��ݍς݃t�@�C�����疕��
	void RemoveFileLoaded( std::string filename );

	//--------------------------------------------------------------------------------------
	// �t�@�C���ǂݍ��݊֘A
	// �ǂݍ��݃t�@�C���\����
	struct FileLoaded
	{
		std::string FileName;
		int GraphHandle;
		DrawType Type;
	};
	// �ǂݍ��ݍς݃t�@�C�����X�g
	std::list<FileLoaded> m_listFileLoaded;

	//--------------------------------------------------------------------------------------
	// �`��I�u�W�F�N�g���X�g
	std::list<IDrawBase*> m_listDrawObject;

	// �`��D��ύX�v��
	bool m_bPriChageRequest;

	//--------------------------------------------------------------------------------------
	// �萔
	const int LOADGRAPH_FAILED = -1;		 // �摜�Ǎ����s
};