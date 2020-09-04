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
#include "EffekseerForDXLib.h"

cDrawCtrl::~cDrawCtrl()
{
}

//==========================================================================================
//  ������
//==========================================================================================
void cDrawCtrl::Initialize(void)
{
	m_listChildObject.clear();
	m_eObjectState = OBJECT_STATE_ACTIVE;
	m_sObjectName = "DrawCtrl";

	m_bPriChageRequest = false;

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

	std::list<IDrawBase*>::iterator it = m_listDrawObject.begin();
	std::list<IDrawBase*>::iterator end = m_listDrawObject.end();

	while (it != end)
	{
		if ((*it)->GetVisible())
		{
			switch ((*it)->m_eDrawType)
			{
			case DRAW_TYPE_SPRITE:
				DrawSprite((cSprite*)(*it));
				break;
			case DRAW_TYPE_EFFECT:
				DrawEffect((cEffect*)(*it));
				break;
			case DRAW_TYPE_BEGINSURFACE:
				BeginSurface(*it);
				break;
			case DRAW_TYPE_SURFACE:
				DrawSurface((cSurface*)(*it));
				break;
			case DRAW_TYPE_TRANSITION:
				DrawTransition((cTransition*)(*it));
				break;
			}
		}
		it++;
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
		InitGraph();

		for (auto it = m_listFileLoaded.begin(); it != m_listFileLoaded.end(); it++)
		{
			if( (*it).Type == DRAW_TYPE_EFFECT) DeleteEffekseerEffect((*it).GraphHandle);
		}

		m_listFileLoaded.clear();
	}
	return nullptr;
}


//==========================================================================================
//	�`����̓o�^(�X�v���C�g)
//  obj : �`�����ݒ肷��X�v���C�g�I�u�W�F�N�g
//  filename : �X�v���C�g�̃��\�[�X�t�@�C����
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cSprite& obj,const std::string& filename)
{
	if(obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front((IDrawBase*)&obj);

	// �ǂݍ��ݍς݃O���t�B�b�N�n���h����ݒ�
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAW_TYPE_SPRITE);

	int x = 0,y = 0;
	GetGraphSize(obj.m_nGraphHandle,&x,&y);
	obj.SetCenter(x/2.0f,y/2.0f);
	// Rect��ݒ肷��
	obj.SetSrcRect(0,0,x,y);

	// �`���ʂ��X�v���C�g�ɐݒ�
	obj.m_eDrawType = DRAW_TYPE_SPRITE;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}
//==========================================================================================
//	�`����̓o�^(�G�t�F�N�g)
//  obj : �`�����ݒ肷��G�t�F�N�g�I�u�W�F�N�g
//  filename : �G�t�F�N�g�̃��\�[�X�t�@�C����
//==========================================================================================
void cDrawCtrl::RegistDrawObject(cEffect & obj, const std::string & filename)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �ǂݍ��ݍς݃O���t�B�b�N�n���h����ݒ�
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAW_TYPE_EFFECT);

	// �`���ʂ��G�t�F�N�g�ɐݒ�
	obj.m_eDrawType = DRAW_TYPE_EFFECT;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}

//==========================================================================================
//	�`����̓o�^(�T�[�t�F�C�X)
//  obj : �`�����ݒ肷��T�[�t�F�C�X
//==========================================================================================
void cDrawCtrl::RegistSurface(cSurface & obj,int width , int height ,bool alpha)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �`��J�n�|�C���g��o�^
	m_listDrawObject.push_front(obj.GetBeginPointer());


	// �`���ʂ��T�[�t�F�C�X�ɐݒ�
	obj.m_eDrawType = DRAW_TYPE_SURFACE;
	obj.GetBeginPointer()->m_eDrawType = DRAW_TYPE_BEGINSURFACE;

	// �`��Ώۂɂł���O���t�B�b�N���쐬����B
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
void cDrawCtrl::RegistTransition(cTransition & obj, const std::string & filename)
{
	if (obj.IsFileLoaded()) return;

	// �`��I�u�W�F�N�g�̓o�^
	m_listDrawObject.push_front(&obj);

	// �ǂݍ��ݍς݃O���t�B�b�N�n���h����ݒ�
	obj.m_nGraphHandle = LoadDrawFile(filename, DRAW_TYPE_TRANSITION);

	// �`���ʂ��g�����W�V�����ɐݒ�
	obj.m_eDrawType = DRAW_TYPE_TRANSITION;

	// �`�揇�̕ύX�v��������
	m_bPriChageRequest = true;
}

//==========================================================================================
//	�`��t�@�C���̓ǂݍ���
//  filename : �t�@�C����
//  type : �`����
//  �߂�l : �ǂݍ��ݍς݂̃O���t�B�b�N�n���h��
//==========================================================================================
int cDrawCtrl::LoadDrawFile(const std::string & filename, DrawType type)
{
	if (!m_listFileLoaded.empty())
	{
		std::list<FileLoaded>::iterator end = m_listFileLoaded.end();
		std::list<FileLoaded>::iterator it = m_listFileLoaded.begin();
		while (it != end)
		{
			// ���[�h�ς݂̃t�@�C���͓ǂݍ��݂��Ȃ�
			if ((*it).FileName == filename) return (*it).GraphHandle;

			it++;
		}
	}
	// �V�K�ǂݍ��݃t�@�C�������X�g�ɒǉ�����
	FileLoaded load;
	load.FileName = filename;
	load.Type = type;
	switch (type)
	{
	case DRAW_TYPE_SPRITE:		load.GraphHandle = LoadGraph(filename.c_str(), FALSE);
		break;
	case DRAW_TYPE_EFFECT:		load.GraphHandle = LoadEffekseerEffect(filename.c_str());
		break;
	case DRAW_TYPE_TRANSITION:	load.GraphHandle = LoadBlendGraph(filename.c_str());
		break;
	}
	// �O���t�B�b�N�n���h���ǂݍ��ݎ��s
	if (LOADGRAPH_FAILED == load.GraphHandle)
		return LOADGRAPH_FAILED;

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
	std::list<IDrawBase*>::iterator it = m_listDrawObject.begin();
	std::list<IDrawBase*>::iterator end = m_listDrawObject.end();

	while (it != end)
	{
		if (obj == (*it))
		{
			if ((*it)->m_bUnload)
			{
				// ���Ɏg���Ă���I�u�W�F�N�g���Ȃ���΃���������A�����[�h����
				if (!SearchSameGrHandle(obj))
				{
					DeleteGraph(obj->m_nGraphHandle);

					// �ǂݍ��ݍς݃t�@�C�����X�g���疕��
					RemoveFileLoaded(obj->m_sFileName);
				}
			}
			(*it)->m_nGraphHandle = LOADGRAPH_FAILED;
			m_listDrawObject.remove(*it);
			return;
		}

		it++;
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
	std::list<IDrawBase*>::iterator it = m_listDrawObject.begin();
	std::list<IDrawBase*>::iterator end = m_listDrawObject.end();

	while (it != end)
	{
		if (obj == (*it))
		{
			DeleteGraph((*it)->m_nGraphHandle);
			(*it)->m_nGraphHandle = LOADGRAPH_FAILED;
			RemoveDrawObject(((cSurface*)*it)->GetBeginPointer());
			m_listDrawObject.remove(*it);
			return;
		}

		it++;
	}
}

//==========================================================================================
//	�X�v���C�g�̕`��
//==========================================================================================
void cDrawCtrl::DrawSprite(cSprite * obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		SetDrawBlendMode(obj->GetBlendMode(), obj->GetAlpha());
		RECT rect = obj->GetSrcRect();

		unsigned int red = (obj->GetDrawColor()   & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor()  & 0x000000ff);
		// �F�̐ݒ�
		SetDrawBright(red, green, blue);
		switch (obj->GetSpriteType())
		{
		case cSprite::SPTYPE_NORMAL:
			// ��]�g�kRect�����������`��
			DrawRectRotaGraph3F(obj->GetPos().x, obj->GetPos().y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
				obj->GetCenter().x, obj->GetCenter().y, obj->GetScale().x, obj->GetScale().y, DEG_TO_RAD(obj->GetAngle()), obj->m_nGraphHandle,
				TRUE);
			break;
		case cSprite::SPTYPE_CIRCLEGAUGE:
			DrawCircleGauge((int)obj->GetPos().x, (int)obj->GetPos().y, obj->GetEndAngle(), obj->m_nGraphHandle, obj->GetStartAngle());
			break;
		}
	}
}

//==========================================================================================
//	�G�t�F�N�g�̕`��
//==========================================================================================
void cDrawCtrl::DrawEffect(cEffect * obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{
		if (obj->m_nPlayingEffectHandle != -1)
		{
			// �Đ��I��
			if (IsEffekseer2DEffectPlaying(obj->m_nPlayingEffectHandle) == -1)
			{
				StopEffekseer2DEffect(obj->m_nPlayingEffectHandle);
				return;
			}
		} else
		{
			// �G�t�F�N�g�̍Đ��J�n
			obj->m_nPlayingEffectHandle = PlayEffekseer2DEffect(obj->m_nGraphHandle);
		}
		SetScalePlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vScale.x, obj->m_vScale.y, obj->m_vScale.z);
		SetPosPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vPos.x, obj->m_vPos.y, 0);
		SetRotationPlayingEffekseer2DEffect(obj->m_nPlayingEffectHandle, obj->m_vAngle.x, obj->m_vAngle.y, obj->m_vAngle.z);

		unsigned int alpha = (obj->GetDrawColor() & 0xff000000) >> 24;
		unsigned int red = (obj->GetDrawColor()   & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor()  & 0x000000ff);

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
void cDrawCtrl::DrawSurface(cSurface * obj)
{
	// �����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂�
	SetDrawScreen(DX_SCREEN_BACK);

	RECT rect = obj->GetRect();
	SetDrawBlendMode(obj->GetBlendMode(), obj->GetAlpha());

	unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
	unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
	unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
	// �F�̐ݒ�
	SetDrawBright(red, green, blue);

	// �T�[�t�F�C�X�̓��e��`��
	DrawRectRotaGraph3F(obj->GetPos().x, obj->GetPos().y, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		obj->GetCenter().x, obj->GetCenter().y, obj->GetScale().x, obj->GetScale().y, DEG_TO_RAD(obj->GetAngle().x), obj->m_nGraphHandle,
		TRUE);
}
//==========================================================================================
//	�T�[�t�F�C�X�̕`��J�n
//==========================================================================================
void cDrawCtrl::BeginSurface(IDrawBase * obj)
{
	if (obj->IsFileLoaded())
	{
		// �����_�[�^�[�Q�b�g���T�[�t�F�C�X�ɂ���
		SetDrawScreen(obj->m_nGraphHandle);
		ClearDrawScreen();
	}
}
//==========================================================================================
//	�g�����W�V�����̕`��
//==========================================================================================
void cDrawCtrl::DrawTransition(cTransition * obj)
{
	if (obj->m_nGraphHandle != LOADGRAPH_FAILED)
	{

		unsigned int red = (obj->GetDrawColor() & 0x00ff0000) >> 16;
		unsigned int green = (obj->GetDrawColor() & 0x0000ff00) >> 8;
		unsigned int blue = (obj->GetDrawColor() & 0x000000ff);
		// �F�̐ݒ�
		SetDrawBright(red, green, blue);
		
		// �`��
		int ret = DrawBlendGraph(0, 0, obj->GetTransObject()->m_nGraphHandle, TRUE, obj->m_nGraphHandle, (int)obj->GetBorderParam(), (int)obj->GetBorderRange());
	}
}
//==========================================================================================
// �����O���t�B�b�N�n���h�������I�u�W�F�N�g�����邩��T��
// �߂�l : true �������� false ������Ȃ�����
//==========================================================================================
bool cDrawCtrl::SearchSameGrHandle(const IDrawBase * obj)
{
	auto it = m_listDrawObject.begin();
	auto end = m_listDrawObject.end();
	while (it != end)
	{
		if (obj != (*it))
		{
			if(obj->m_nGraphHandle == (*it)->m_nGraphHandle) return true;
		}
		it++;
	}

	return false;
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
		std::list<FileLoaded>::iterator end = m_listFileLoaded.end();
		std::list<FileLoaded>::iterator it = m_listFileLoaded.begin();
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