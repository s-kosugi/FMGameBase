/*==============================================================================*/
/*																				*/
/*	@file title	:	cAnimSprite.cpp												*/
/*  @brief		:	�A�j���[�V�����X�v���C�g�N���X								*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/04/14													*/
/*																				*/
/*==============================================================================*/

#include "cAnimSprite.h"
#include "..\cDrawCtrl.h"
#include "cGame.h"
#include "Utility/json_loader/rapidjson/document.h"
#include <fstream>
#include "Utility/StrControl/StrControl.h"

#ifdef DEBUG
#include "DebugFunc/cDebugFunc.h"
#endif

//==========================================================================================
// �萔
//==========================================================================================
// �L�[��
const char*     cAnimSprite::m_sKeyName[] =
{
	"file",
	"frame",
	"width",
	"height",
	"cols",
	"rows",
	"animations",
	"frames",
	"interval",
	"loop",
};

//==========================================================================================
//  �R���X�g���N�^
//==========================================================================================
cAnimSprite::cAnimSprite(const std::string& filename) :
	cSprite(filename),
	m_FrameSize({ 0,0 }),
	m_nFrameCols(0),
	m_nFrameRows(0),
	m_nCurrentAnimeID(-1),
	m_fCurrentFrame(0.0f),
	m_fCurrentAnimeFPS(1.0f),
	m_bStopFlag( false ),
	m_fPlaySpeedRate(1.0f)
{

	if (Ends_With(filename, ".ass"))
	{
		// ASS�t�@�C���Ǎ�
		if (LoadASS(filename))
		{
			// �A�j���[�V������ύX
			ChangeAnime(0);
			// �`�����o�^
			cDrawCtrl::GetInstance().RegistDrawObject(*this, m_sFileName);
		} else
		{
			// ASS�Ǎ����s
			m_nCurrentAnimeID = 0;
		}
	} else
	{
		// �ʏ�̉摜�t�@�C��
		m_nCurrentAnimeID = 0;
	}
	
}

//==========================================================================================
//  �f�X�g���N�^
//==========================================================================================
cAnimSprite::~cAnimSprite(void)
{
}

//==========================================================================================
//  ������
//==========================================================================================
void
cAnimSprite::
Initialize(void)
{
	// �A�j���[�V�������Z�b�g����Ă�����\���摜���X�V����
	if (0 < m_nFrameCols) {
		int index = (int)m_fCurrentFrame;
		index = (int)m_AnimationList[m_nCurrentAnimeID].Frames.size() - 1;

		// �w�肳�ꂽ�A�j���[�V��������`��͈͂��Z�o
		int frame = m_AnimationList[m_nCurrentAnimeID].Frames[index];

		// �\�����W�X�V
		m_SrcRect.left = (frame % m_nFrameCols) * m_FrameSize.x;
		m_SrcRect.top = (frame / m_nFrameCols) * m_FrameSize.y;
		m_SrcRect.right = m_SrcRect.left + m_FrameSize.x;
		m_SrcRect.bottom = m_SrcRect.top + m_FrameSize.y;

		// �A�j���[�V�������Z�b�g����Ă����璆�S�ʒu��ύX����B(�����_�ȉ��l�̌ܓ�)
		m_vCenter.x = (float)((int)(m_FrameSize.x / 2.0f + 0.5f));
		m_vCenter.y = (float)((int)(m_FrameSize.y / 2.0f + 0.5f));
	}
	IDrawBase::Initialize();
}

//==========================================================================================
//  �X�V
//==========================================================================================
void cAnimSprite::Update(void)
{
	// ��~�t���O�܂��̓A�j���[�V�������Ȃ��ꍇ�ɂ͐i�߂Ȃ��悤�ɂ���
	if (!m_bStopFlag && !m_AnimationList.empty())
	{

		// �f���^�^�C���擾
		float delta_time = cGame::GetInstance().GetDeltaTime();

		// �f���^�^�C�����g���ăA�j���[�V�����t���[�����X�V
		// �A�j���[�V�����̍Đ����x�������f
		m_fCurrentFrame += m_fCurrentAnimeFPS * m_fPlaySpeedRate * delta_time;

		// �A�j���[�V�����̍ő�t���[���𒴂��Ă��Ȃ�
		if (!(m_fCurrentFrame < m_AnimationList[m_nCurrentAnimeID].Frames.size()))
		{
			// ���[�v�ݒ�ł���΃t���[����擪�ɂ��ǂ�
			// �����łȂ���΍ŏI�t���[���ŌŒ肷��
			if (m_AnimationList[m_nCurrentAnimeID].Loop)
				m_fCurrentFrame = 0.0f;
		}

		// �J�����g�t���[�����擾
		int index = (int)m_fCurrentFrame;

		// �ő�t���[���𒴂��Ă����琧��
		if (index >= (int)m_AnimationList[m_nCurrentAnimeID].Frames.size())
			index = (int)m_AnimationList[m_nCurrentAnimeID].Frames.size() - 1;

		// �w�肳�ꂽ�A�j���[�V��������`��͈͂��Z�o
		int frame = m_AnimationList[m_nCurrentAnimeID].Frames[index];

		m_SrcRect.left = (frame % m_nFrameCols) * m_FrameSize.x;
		m_SrcRect.top = (frame / m_nFrameCols) * m_FrameSize.y;
		m_SrcRect.right = m_SrcRect.left + m_FrameSize.x;
		m_SrcRect.bottom = m_SrcRect.top + m_FrameSize.y;
	}

	IDrawBase::Update();
}
//==========================================================================================
//  ���
//==========================================================================================
void cAnimSprite::Finalize(void)
{
	IDrawBase::Finalize();
}
//==========================================================================================
//  �A�j���[�V�����̕ύX
//  animID : �ύX����A�j���[�V�������O
//==========================================================================================
void cAnimSprite::ChangeAnime(const std::string & animName)
{
	if (m_AnimationList.empty()) return;

	for (int i = 0; i < (int)m_AnimationList.size(); ++i)
	{
		// ���O����v����ID�ŃA�j���[�V������ύX����
		if (m_AnimationList[i].Name == animName)
		{
			ChangeAnime( i );
			return;
		}
	}
}

//==========================================================================================
//  �A�j���[�V�����̕ύX
//  animID : �ύX����A�j���[�V������ID
//==========================================================================================
void cAnimSprite::ChangeAnime(int animID)
{
	// �A�j���[�V����ID�������Ȃ�ύX���Ȃ�
	if (m_nCurrentAnimeID == animID)
		return;

	m_nCurrentAnimeID = animID;
	m_fCurrentFrame = 0.0f;

	// �A�j���[�V�������X�g������΍Đ�FPS���Z�o
	if (m_AnimationList.size())
		m_fCurrentAnimeFPS = (float)(1.0f / (float)m_AnimationList[m_nCurrentAnimeID].Interval);

	// ��~�t���O��OFF
	m_bStopFlag = false;
}
//==========================================================================================
//  �A�j���[�V�����̃R�s�[
//  src : ���ƂȂ�A�j���[�V�����N���X
//==========================================================================================
void cAnimSprite::CopyAnime(const cAnimSprite & src)
{
	m_FrameSize = src.m_FrameSize;
	m_nFrameCols = src.m_nFrameCols;
	m_nFrameRows = src.m_nFrameRows;

	m_AnimationList = src.m_AnimationList;

	m_nCurrentAnimeID = src.m_nCurrentAnimeID;
	m_fCurrentFrame = src.m_fCurrentFrame;
	m_fCurrentAnimeFPS = src.m_fCurrentAnimeFPS;
	m_bStopFlag = src.m_bStopFlag;
	m_fPlaySpeedRate = src.m_fPlaySpeedRate;
}
//==========================================================================================
//  �A�j���[�V�����̐ݒ�(��FMGB�݊��֐�)
//==========================================================================================
void cAnimSprite::SetAnimation(int Startx, int Starty, int width, int height, short AnimMax, float AnimTime)
{
	m_AnimationList.clear();

	AnimationData data;
	for( int i = 0; i < AnimMax; i++)
		data.Frames.push_back(Startx / width + (Starty / height) * (AnimMax) + i);
	data.Interval = AnimTime;
	data.Loop = true;
	data.Name = "OLDFMGBANIM";

	m_AnimationList.push_back(data);

	m_FrameSize.x = width;
	m_FrameSize.y = height;
	m_nFrameCols = AnimMax;
	m_nFrameRows = 1;

	m_fCurrentFrame = 0.0f;
	m_nCurrentAnimeID = 0;
	m_fCurrentAnimeFPS = (float)(1.0f / (float)m_AnimationList[m_nCurrentAnimeID].Interval);
	m_fPlaySpeedRate = 1.0f;
	m_bStopFlag = false;
}

//=========================================================================
// ASS�t�@�C���̓ǂݍ��݂Ɖ��
// filename : ass�t�@�C���p�X
// return : ���� : true ���s : false
//=========================================================================
bool cAnimSprite::LoadASS(const std::string& filename)
{
	// �t�@�C�����J��
	std::ifstream ifs(filename, std::ios::in);

	if (ifs.fail())
	{
#ifdef DEBUG
		cDebugFunc::GetInstance().PushDebugLog("LoadASS Error :" + filename);
#endif
		return false;
	}

	// �f�[�^�̓ǂݍ���
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	// �t�@�C�������
	ifs.close();

	// RapicJSON�h�L�������g
	rapidjson::Document doc;

	// JSON�f�[�^����͂���
	doc.Parse(json.c_str());

	// �\������������͂ł������ǂ���
	if (doc.HasParseError())
	{
#ifdef DEBUG
		cDebugFunc::GetInstance().PushDebugLog("ASS SyntaxError : " + filename);
#endif
		return false;
	}

	// �t�@�C�����擾
	m_sFileName = doc[m_sKeyName[ASS_KEY_FILE]].GetString();

	// �t���[���I�u�W�F�N�g�擾
	const rapidjson::Value& frame_object = doc[m_sKeyName[ASS_KEY_FRAME]];

	// �t���[���̕�
	m_FrameSize.x = frame_object[m_sKeyName[ASS_KEY_WIDTH]].GetInt();

	// �t���[���̍���
	m_FrameSize.y = frame_object[m_sKeyName[ASS_KEY_HEIGHT]].GetInt();

	// ���ɕ���ł���t���[����
	m_nFrameCols = frame_object[m_sKeyName[ASS_KEY_COLS]].GetInt();

	// �c�ɕ���ł���t���[����
	m_nFrameRows = frame_object[m_sKeyName[ASS_KEY_ROWS]].GetInt();

	// �A�j���[�V�����I�u�W�F�N�g�擾
	const rapidjson::Value& animations_object = doc[m_sKeyName[ASS_KEY_ANIMATIONS]];

	rapidjson::Value::ConstMemberIterator it = animations_object.MemberBegin();
	rapidjson::Value::ConstMemberIterator end = animations_object.MemberEnd();

	while (it != end)
	{
		AnimationData data;

		// ���O���擾
		data.Name = it->name.GetString();

		// �t���[�����Ȃǂ̃A�j���[�V�����f�[�^�擾
		const rapidjson::Value& animation_data = it->value;

		// �A�j���[�V�����t���[���e�[�u���擾
		const rapidjson::Value& frames = animation_data[m_sKeyName[ASS_KEY_FRAMES]];

		for (rapidjson::SizeType i = 0; i < frames.Size(); ++i)
			data.Frames.push_back(frames[i].GetInt());

		// �X�V�Ԋu�擾
		data.Interval = (float)animation_data[m_sKeyName[ASS_KEY_INTERVAL]].GetDouble();

		// ���[�v�ݒ�擾
		data.Loop = animation_data[m_sKeyName[ASS_KEY_LOOP]].GetBool();

		// �A�j���[�V�����f�[�^���X�g�ɒǉ�
		m_AnimationList.push_back(data);

		++it;
	}
	return true;
}