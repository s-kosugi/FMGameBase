/*==============================================================================*/
/*																				*/
/*	@file title	:	cDrawCtrl.cpp												*/
/*  @brief		:	�`��R���g���[���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/09/17													*/
/*																				*/
/*==============================================================================*/

#include "cDrawCtrl.h"
#include "..\Utility\memory.h"
#include "..\Utility\utility.h"
#include <algorithm>
#include <DxLib.h>
#pragma warning(disable: 26495)
#include "EffekseerForDXLib.h"
#include "SceneManager/cSceneManager.h"
#include <direct.h>
#include "cGame.h"

#ifdef DEBUG
#include "..\DebugFunc\cDebugFunc.h"
#endif


//==========================================================================================
//  ������
//==========================================================================================
void cDrawCtrl::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE::ACTIVE;
	m_sObjectName = "DrawCtrl";

	IBaseObject::Initialize();
}
//==========================================================================================
//  �`��
//==========================================================================================
void cDrawCtrl::Draw(void)
{
	if (m_listDrawObject.empty()) return;

	// �`��D��x�ύX�v������������D��x���Ƀ\�[�g����
	if (m_bPriChageRequest) m_listDrawObject.sort(CompAscPriority);

	// �e�I�u�W�F�N�g�̕`��
	for (auto it = m_listDrawObject.begin(); it != m_listDrawObject.end(); it++)
	{
		if ((*it)->GetVisible())
		{
			switch ((*it)->m_eDrawType)
			{
			case DRAWTYPE::SPRITE:
				DrawSprite((cSprite*)(*it));
				break;
			case DRAWTYPE::EFFECT:
				DrawEffect((cEffect*)(*it));
				break;
			case DRAWTYPE::BEGINSURFACE:
				BeginSurface((*it));
				break;
			case DRAWTYPE::SURFACE:
				if (DrawSurface((cSurface*)(*it)))
				{
					// �����҂��̃T�[�t�F�C�X���������ꍇ�C�e���[�^�[���������̃I�u�W�F�N�g�̏ꏊ�܂Ŗ߂�
					if (!m_listSurfaceWait.empty())
					{
						it = std::find(m_listDrawObject.begin(), m_listDrawObject.end(), (*m_listSurfaceWait.begin()));
						BeginSurface(*it);
						m_listSurfaceWait.pop_front();
					}
				}
				break;
			case DRAWTYPE::TRANSITION:
				DrawTransition((cTransition*)(*it));
				break;
			case DRAWTYPE::MODEL:
				DrawModel((cModel*)(*it));
				break;
			case DRAWTYPE::TEXT:
				DrawTextObj((cText*)(*it));
				break;
			}
		}
	}

	if (m_bScreenShot)
	{
		// �X�N���[���V���b�g�ۑ�
		SaveScreenFile();

		// �X�N���[���V���b�g�ۑ��v�������Z�b�g
		m_bScreenShot = false;
	}

	// �ύX�v�������Z�b�g
	m_bPriChageRequest = false;
}

//==========================================================================================
//  ���
//==========================================================================================
IBaseObject* cDrawCtrl::Finalize(void)
{
	IBaseObject::Finalize();

	//------------------------------------------------------------------------------------
	// �`�惊�X�g�̃N���A
	m_listDrawObject.clear();

	//------------------------------------------------------------------------------------
	// �ǂݍ��ݍςݕ`��t�@�C���̉��
	if (!m_listFileLoaded.empty())
	{
		// ���t���X�N���[�����ɃG���[��������\��������׃R�����g�A�E�g
		/*for (auto it = m_listFileLoaded.begin(); it != m_listFileLoaded.end(); it++)
		{
			if( (*it).Type == DRAW_TYPE_EFFECT) DeleteEffekseerEffect((*it).GraphHandle);
		}*/

		InitGraph();

		m_listFileLoaded.clear();
	}
	return nullptr;
}


//==========================================================================================
//	�`����̓o�^(�X�v���C�g)
//  obj : �`�����ݒ肷��X�v���C�g�I�u�W�F�N�g
//  filename : �X�v���C�g�̃��\�[�X�t�@�C����
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cSprite& obj, const std::string& filename)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front((IDrawBase*)&obj);

	// �ǂݍ��ݍς݃O���t�B�b�N�n���h����ݒ�
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAWTYPE::SPRITE);

	int x = 0, y = 0;
	GetGraphSize(obj.m_nGraphHandle, &x, &y);
	obj.SetCenter(x / 2.0f, y / 2.0f);

	// Rect��ݒ肷��
	obj.SetSrcRect(0, 0, x, y);

	// �`���ʂ��X�v���C�g�ɐݒ�
	obj.m_eDrawType = DRAWTYPE::SPRITE;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}
//==========================================================================================
//	�`����̓o�^(�G�t�F�N�g)
//  obj : �`�����ݒ肷��G�t�F�N�g�I�u�W�F�N�g
//  filename : �G�t�F�N�g�̃��\�[�X�t�@�C����
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cEffect& obj, const std::string& filename)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �ǂݍ��ݍς݃O���t�B�b�N�n���h����ݒ�
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAWTYPE::EFFECT);

	// �`���ʂ��G�t�F�N�g�ɐݒ�
	obj.m_eDrawType = DRAWTYPE::EFFECT;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}
//==========================================================================================
//	�`����̓o�^(�T�[�t�F�C�X)
//  obj : �`�����ݒ肷��T�[�t�F�C�X
//==========================================================================================
void cDrawCtrl::RegistSurface(cSurface& obj, int width, int height, bool alpha)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �`��J�n�|�C���g��o�^
	m_listDrawObject.push_front(obj.GetBeginPointer());


	// �`���ʂ��T�[�t�F�C�X�ɐݒ�
	obj.m_eDrawType = DRAWTYPE::SURFACE;
	obj.GetBeginPointer()->m_eDrawType = DRAWTYPE::BEGINSURFACE;

	// �T�[�t�F�C�X���쐬����
	obj.m_nGraphHandle = MakeScreen(width, height, alpha);
	obj.GetBeginPointer()->m_nGraphHandle = obj.m_nGraphHandle;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}
//==========================================================================================
//	�`����̓o�^(�g�����W�V����)
//  obj : �`�����ݒ肷��g�����W�V�����I�u�W�F�N�g
//  filename : ���[���摜�̃��\�[�X�t�@�C����
//==========================================================================================
void cDrawCtrl::RegistTransition(cTransition& obj, const std::string& filename)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �ǂݍ��ݍς݃O���t�B�b�N�n���h����ݒ�
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAWTYPE::TRANSITION);

	// �`���ʂ��g�����W�V�����ɐݒ�
	obj.m_eDrawType = DRAWTYPE::TRANSITION;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}

//==========================================================================================
//	�`����̓o�^(���f��)
//  obj : �`�����ݒ肷�郂�f���I�u�W�F�N�g
//  filename : ���f���f�[�^�̃��\�[�X�t�@�C����
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cModel& obj, const std::string& filename)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �ǂݍ��ݍς݃O���t�B�b�N�n���h����ݒ�
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAWTYPE::MODEL);

	// �`���ʂ����f���ɐݒ�
	obj.m_eDrawType = DRAWTYPE::MODEL;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}
//==========================================================================================
//	�`����̓o�^(�e�L�X�g)
//  obj : �`�����ݒ肷��e�L�X�g�I�u�W�F�N�g
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cText& obj)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �f�t�H���g�t�H���g���g�p
	obj.m_nGraphHandle = LOADGRAPH_FAILED;

	// �`���ʂ����f���ɐݒ�
	obj.m_eDrawType = DRAWTYPE::TEXT;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}
//==========================================================================================
//	�`����̓o�^(�e�L�X�g)
//  obj : �`�����ݒ肷��e�L�X�g�I�u�W�F�N�g
//  �ȍ~���� : CreateFont�ɕK�v
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cText& obj, const std::string& fontname, int Size, int Thick, int FontType, int EdgeSize, int Italic)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �t�H���g�����p�̍\���̂��쐬
	FontCreated font;
	font.FontName = fontname;
	font.Size = Size;
	font.Thick = Thick;
	font.FontType = FontType;
	font.EdgeSize = EdgeSize;
	font.Italic = Italic;

	// �t�H���g�����ς݂łȂ���΍쐬
	int handle = SearchSameFont(font);
	if (handle == FONT_NOTFAUND)
	{
		// ��Z�ς݃��p�̃t�H���g�n���h�����쐬����
		SetFontCacheUsePremulAlphaFlag(TRUE);

		font.Handle = CreateFontToHandle(font.FontName.c_str(), font.Size, font.Thick, font.FontType, -1, font.EdgeSize, font.Italic);
		handle = font.Handle;
		m_listFontCreated.push_back(font);
	}

	obj.m_nGraphHandle = handle;

	// �`���ʂ����f���ɐݒ�
	obj.m_eDrawType = DRAWTYPE::TEXT;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}
//==========================================================================================
//	�`��t�@�C���̓ǂݍ���
//  filename : �t�@�C����
//  type : �`����
//  �߂�l : �ǂݍ��ݍς݂̃O���t�B�b�N�n���h��
//==========================================================================================
int cDrawCtrl::LoadDrawFile(const std::string& filename, DRAWTYPE type)
{
	if (!m_listFileLoaded.empty())
	{
		for (auto it : m_listFileLoaded)
		{
			// �O���t�B�b�N�ǂݍ��ݍς�
			if (it.FileName == filename) return it.GraphHandle;
		}
	}

	// �V�K�ǂݍ��݃t�@�C�������X�g�ɒǉ�����
	FileLoaded load;
	load.FileName = filename;

	load.Type = type;
	switch (type)
	{
	case DRAWTYPE::SPRITE:		load.GraphHandle = LoadGraph(filename.c_str(), FALSE);	break;
	case DRAWTYPE::EFFECT:		load.GraphHandle = LoadEffekseerEffect(filename.c_str());	break;
	case DRAWTYPE::TRANSITION:	load.GraphHandle = LoadBlendGraph(filename.c_str());	break;
	case DRAWTYPE::MODEL:		load.GraphHandle = MV1LoadModel(filename.c_str());	break;
	}
	// �O���t�B�b�N�n���h���ǂݍ��ݎ��s
	if (LOADGRAPH_FAILED == load.GraphHandle)
	{
#ifdef DEBUG
		cDebugFunc::GetInstance().PushDebugLog("LOADGRAPH_FAILED : " + filename);
#endif
		return LOADGRAPH_FAILED;
	}

	// �ǂݍ��ݍς݃��X�g�ɒǉ�
	m_listFileLoaded.push_back(load);
	return load.GraphHandle;
}

//==========================================================================================
//	�`����̓o�^����
//  obj : �`����𖕏��������I�u�W�F�N�g���g
//==========================================================================================
void cDrawCtrl::RemoveDrawObject(const IDrawBase* obj)
{
	//---------------------------------------------------------------------
	// m_listDrawObject����̖�������
	for (auto it : m_listDrawObject)
	{
		if (obj == it)
		{
			if (it->m_bUnload)
			{
				// ���Ɏg���Ă���I�u�W�F�N�g���Ȃ���΃���������A�����[�h����
				if (!SearchSameGrHandle(obj))
				{
					DeleteGraph(obj->m_nGraphHandle);

					// �ǂݍ��ݍς݃t�@�C�����X�g���疕��
					RemoveFileLoaded(obj->m_sFileName);
				}
			}
			it->m_nGraphHandle = LOADGRAPH_FAILED;
			m_listDrawObject.remove(it);
			return;
		}
	}
}
//==========================================================================================
//	�T�[�t�F�C�X�̓o�^����
//  obj : �o�^�������T�[�t�F�C�X���g
//==========================================================================================
void cDrawCtrl::RemoveSurface(const cSurface* obj)
{
	//---------------------------------------------------------------------
	// m_listDrawObject����̖�������
	for (auto it : m_listDrawObject)
	{
		if (obj == it)
		{
			DeleteGraph(it->m_nGraphHandle);
			it->m_nGraphHandle = LOADGRAPH_FAILED;
			RemoveDrawObject(((cSurface*)it)->GetBeginPointer());
			m_listDrawObject.remove(it);
			return;
		}
	}
}

//==========================================================================================
// �e�L�X�g�̕��������擾����
//==========================================================================================
int cDrawCtrl::GetTextWidth(cText* obj)
{
	// �f�t�H���g�t�H���g�̏ꍇ
	if (obj->m_nGraphHandle == FONT_NOTFAUND)
	{
		return GetDrawStringWidth(obj->GetText().c_str(), (int)obj->GetText().length());
	}
	// �쐬�ς݃t�H���g�̏ꍇ
	else
	{
		return GetDrawStringWidthToHandle(obj->GetText().c_str(), (int)obj->GetText().length(), obj->m_nGraphHandle);
	}
}

//==========================================================================================
//	�X�v���C�g�̕`��
//==========================================================================================
void cDrawCtrl::DrawSprite(cSprite* obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		SetDrawBlendMode(obj->GetBlendMode(), obj->GetAlpha());
		RECT rect = obj->GetSrcRect();

		unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
		// �F�̐ݒ�
		SetDrawBright(red, green, blue);
		// ��]�g�kRect�����������`��
		DrawRectRotaGraph3F(round(obj->GetPos().x), round(obj->GetPos().y), rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
			round(obj->GetCenter().x + obj->GetAnchor().x), round(obj->GetCenter().y + obj->GetAnchor().y), obj->GetScale().x, obj->GetScale().y, DEG_TO_RAD(obj->GetAngle()), obj->m_nGraphHandle,
			TRUE);
	}
}

//==========================================================================================
//	�G�t�F�N�g�̕`��
//==========================================================================================
void cDrawCtrl::DrawEffect(cEffect* obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		if (obj->m_nPlayingEffectHandle != EFFEKSEER_NOTPLAYING)
		{
			// �V�[��ID����v���Ȃ��ꍇ�ɂ̓G�t�F�N�g���ꎞ��~����
			if (obj->m_ePlayScene != SCENE_ID::NONE && obj->m_ePlayScene != cSceneManager::GetInstance().GetStackSceneID())
			{
				SetSpeedPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, 0.0f);
			}
			else
			{
				SetSpeedPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, 1.0f);
			}
			// �Đ��I�����͒�~�t���O�������Ă����ꍇ
			if (IsEffekseer2DEffectPlaying(obj->m_nPlayingEffectHandle) == EFFEKSEER_NOTPLAYING ||
				obj->m_bStop)
			{
				StopEffekseer2DEffect(obj->m_nPlayingEffectHandle);
				if (!obj->IsLoop())
				{
					return;
				}
				else {

					// ���[�v�ݒ�̃G�t�F�N�g��������ēx�Đ�
					obj->m_nPlayingEffectHandle = PlayEffekseer2DEffect(obj->m_nGraphHandle);
				}
			}
		}
		else
		{
			// �G�t�F�N�g�̍Đ��J�n
			obj->m_nPlayingEffectHandle = PlayEffekseer2DEffect(obj->m_nGraphHandle);
		}
		SetScalePlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vScale.x, obj->m_vScale.y, obj->m_vScale.z);
		SetPosPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vPos.x, obj->m_vPos.y, 0);
		SetRotationPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vAngle.x, obj->m_vAngle.y, obj->m_vAngle.z);

		unsigned int alpha = (obj->GetDrawColor() & 0xff000000) >> 24;
		unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor() & 0x000000ff);

		SetColorPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, red, green, blue, alpha);

		// �G�t�F�N�g��`�悷��
		DrawEffekseer2D_Begin();
		DrawEffekseer2D_Draw(obj->m_nPlayingEffectHandle);
		DrawEffekseer2D_End();
	}
}
//==========================================================================================
//	�T�[�t�F�C�X�̕`��
//==========================================================================================
bool cDrawCtrl::DrawSurface(cSurface* obj)
{
	// �ΏۊO�̃T�[�t�F�C�X�͈�U��΂�
	if (m_pBeginSurface != obj->GetBeginPointer()) return false;

	// �����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�
	SetDrawScreen(DX_SCREEN_BACK);

	RECT rect = obj->GetRect();
	SetDrawBlendMode(obj->GetBlendMode(), obj->GetAlpha());

	unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
	unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
	unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
	// �F�̐ݒ�
	SetDrawBright(red, green, blue);

	// �t�B���^�[�̐ݒ�
	switch (obj->GetFilterMode())
	{
	case cSurface::FILTER_MODE::MONO: GraphFilter(obj->m_nGraphHandle, DX_GRAPH_FILTER_MONO, obj->GetMonoBlue(), obj->GetMonoRed()); break;
	case cSurface::FILTER_MODE::GAUSS: GraphFilter(obj->m_nGraphHandle, DX_GRAPH_FILTER_GAUSS, obj->GetGaussPixelWidth(), obj->GetGaussParam()); break;
	case cSurface::FILTER_MODE::HSB: GraphFilter(obj->m_nGraphHandle, DX_GRAPH_FILTER_HSB, 0, obj->GetHSBHue(), obj->GetHSBSaturation(), obj->GetHSBBright()); break;
	case cSurface::FILTER_MODE::INVERT: GraphFilter(obj->m_nGraphHandle, DX_GRAPH_FILTER_INVERT); break;
	default: break;
	}

	// �\���t���O�������Ă��鎞�̂ݕ\������
	if (obj->IsShow())
	{
		// �T�[�t�F�C�X�̓��e��`��
		DrawRectRotaGraph3F(obj->GetPos().x, obj->GetPos().y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
			obj->GetCenter().x, obj->GetCenter().y, obj->GetScale().x, obj->GetScale().y, DEG_TO_RAD(obj->GetAngle()), obj->m_nGraphHandle,
			TRUE);
	}
	// �������̃T�[�t�F�C�X�|�C���^��������
	m_pBeginSurface = nullptr;

	return true;
}
//==========================================================================================
//	�T�[�t�F�C�X�̕`��J�n
//==========================================================================================
void cDrawCtrl::BeginSurface(IDrawBase* obj)
{
	if (obj->IsFileLoaded())
	{
		// �������T�[�t�F�C�X���������ꍇ�ɂ̓T�[�t�F�C�X�������҂��ɂ���
		if (m_pBeginSurface)
		{
			// ���o�^�̃T�[�t�F�C�X�̏ꍇ�͏����҂����X�g�ɒǉ�����
			if (m_listSurfaceWait.end() == std::find(m_listSurfaceWait.begin(), m_listSurfaceWait.end(), obj))
				m_listSurfaceWait.push_back(obj);
			return;
		}

		m_pBeginSurface = obj;
		// �����_�[�^�[�Q�b�g���T�[�t�F�C�X�ɂ���
		SetDrawScreen(obj->m_nGraphHandle);
		ClearDrawScreen();
	}
}
//==========================================================================================
//	�g�����W�V�����̕`��
//==========================================================================================
void cDrawCtrl::DrawTransition(cTransition* obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		// �g�����W�V�����̓u�����h���[�h��ݒ肵�Ȃ�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
		// �F�̐ݒ�
		SetDrawBright(red, green, blue);

		// �`��
		DrawBlendGraph((int)obj->m_vPos.x, (int)obj->m_vPos.y, obj->GetTransObject()->m_nGraphHandle, TRUE, obj->m_nGraphHandle, (int)obj->GetBorderParam(), (int)obj->GetBorderRange());
	}
}
//==========================================================================================
//	���f���̕`��
//==========================================================================================
void cDrawCtrl::DrawModel(cModel* obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		// ���f���̕`��
		MV1DrawModel(obj->m_nGraphHandle);
	}
}
//==========================================================================================
//	�e�L�X�g�̕`��
//==========================================================================================
void cDrawCtrl::DrawTextObj(cText* obj)
{
	// �e�L�X�g��Alpha�u�����h���[�h�ɕύX
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, obj->GetAlpha());

	unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
	unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
	unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
	// �F�̐ݒ�
	SetDrawBright(red, green, blue);

	if (obj->m_nGraphHandle == LOADGRAPH_FAILED)
	{
		// �W�������`��
		DrawStringF(obj->GetPos().x, obj->GetPos().y, obj->GetText().c_str(), obj->GetDrawColor());
	}
	else
	{
		// �t�H���g�n���h����p�����`��
		DrawStringToHandle((int)obj->GetPos().x, (int)obj->GetPos().y, obj->GetText().c_str(), obj->GetDrawColor(), obj->m_nGraphHandle, obj->GetEdgeColor(), obj->GetVerticalFlag());
	}
}
//==========================================================================================
// �����O���t�B�b�N�n���h�������I�u�W�F�N�g�����邩��T��
// �߂�l : true �������� false ������Ȃ�����
//==========================================================================================
bool cDrawCtrl::SearchSameGrHandle(const IDrawBase* obj)
{
	for (auto it : m_listDrawObject)
	{
		if (obj != it)
		{
			if (obj->m_nGraphHandle == it->m_nGraphHandle) return true;
		}
	}
	return false;
}
//==========================================================================================
// �����ς݂̓��t�H���g�����邩��T��
// �߂�l : -1 �����t�H���g��������Ȃ����� -1�ȊO �t�H���g�n���h��
//==========================================================================================
int cDrawCtrl::SearchSameFont(FontCreated& font)
{
	for (auto it : m_listFontCreated)
	{
		if (font.FontName == it.FontName &&
			font.Size == it.Size &&
			font.Thick == it.Thick &&
			font.FontType == it.FontType &&
			font.EdgeSize == it.EdgeSize &&
			font.Italic == it.Italic)
		{
			return it.Handle;
		}
	}
	return FONT_NOTFAUND;
}
//==========================================================================================
// �ǂݍ��ݍς݃t�@�C�����X�g���疕������
// filename : ��������t�@�C����
//==========================================================================================
void cDrawCtrl::RemoveFileLoaded(std::string filename)
{
	// �A�����[�h������ǂݍ��ݍς݃��X�g���疕��
	if (!m_listFileLoaded.empty())
	{
		auto end = m_listFileLoaded.end();
		auto it = m_listFileLoaded.begin();
		while (it != end)
		{
			// ���[�h�ς݂̃t�@�C���𖕏�����
			if ((*it).FileName == filename)
			{
				m_listFileLoaded.erase(it);
				return;
			}
			it++;
		}
	}
}

//==========================================================================================
// �X�N���[���V���b�g�ۑ�
//==========================================================================================
void cDrawCtrl::SaveScreenFile(void)
{
	// �X�N���[���V���b�g�v��������Εۑ�����
	DATEDATA date;
	GetDateTime(&date);
	if (_mkdir("ScreenShot") != 0) return;
	// �N�ȊO�͂O���߂��Ă���
	char mon[8], day[8], hour[8], min[8], sec[8];
	sprintf_s(mon, 8, "%02d", date.Mon);
	sprintf_s(day, 8, "%02d", date.Day);
	sprintf_s(hour, 8, "%02d", date.Hour);
	sprintf_s(min, 8, "%02d", date.Min);
	sprintf_s(sec, 8, "%02d", date.Sec);
	// �X�N���[���V���b�g����t�̃t�@�C�����ɂ���
	std::string datestr = "ScreenShot\\" + std::to_string(date.Year) + mon + day + hour + min + sec + ".png";

	SaveDrawScreenToPNG(0, 0, cGame::GetInstance().GetWindowWidth(), cGame::GetInstance().GetWindowHeight(), datestr.c_str(), 0);
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cDrawCtrl::cDrawCtrl(void) :
	m_bPriChageRequest(false),
	m_bScreenShot(false),
	m_pBeginSurface(nullptr)
{
	m_listFileLoaded.clear();
	m_listDrawObject.clear();
	m_listFontCreated.clear();
	m_listSurfaceWait.clear();
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cDrawCtrl::cDrawCtrl(IBaseObject* parent) :
	cDrawCtrl::cDrawCtrl()
{
}

//==========================================================================================
// �R���X�g���N�^
//==========================================================================================
cDrawCtrl::cDrawCtrl(IBaseObject* parent, const std::string& name) :
	cDrawCtrl::cDrawCtrl(parent)
{
}

//==========================================================================================
// �R�s�[�R���X�g���N�^
//==========================================================================================
cDrawCtrl::cDrawCtrl(const cDrawCtrl& t) :
	cDrawCtrl::cDrawCtrl()
{
}
