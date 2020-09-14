/*==============================================================================*/
/*																				*/
/*	@file title	:	cResult.cpp													*/
/*  @brief		:	リザルトシーン												*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2020/04/11													*/
/*																				*/
/*==============================================================================*/

#include "..\..\..\cGame.h"
#include "cResult.h"
#include "..\..\cSceneManager.h"
#include "ScoreManager/cScoreManager.h"
#include "Input/cControllerManager.h"
#include "..\..\..\BaseObject\cSpriteObject.h"
#include "BaseObject/TextObject/cTextObject.h"
#include "SoundCtrl/cSoundCtrl.h"
#include "Utility/Timer/cTimer.h"
#include "Utility/Easing/Easing.h"
#include "Utility/SaveData/cSaveData.h"
#include "SoundCtrl/cSoundCtrl.h"

//==========================================================================================
//  定数
//==========================================================================================
const float cResult::PAPER_START_POSX = 1000;
const float cResult::PAPER_START_POSY = -500;
//==========================================================================================
//  コンストラクタ
//==========================================================================================
cResult::cResult(IBaseObject* parent)
	: IBaseScene(parent, "Result")
	, m_eResultState( RESULT_STATE::START )
	, m_nHiScore( 0 )
{
}
//==========================================================================================
//  デストラクタ
//==========================================================================================
cResult::~cResult(void)
{
}
//==========================================================================================
//  初期化
//==========================================================================================
void cResult::Initialize(void)
{
	cGame* game = (cGame*)GetRoot();

	// 背景スプライトの生成
	cSpriteObject* obj = CreateDrawObject<cSpriteObject>(this, "ResultBack", "data\\graphic\\resultback.png");
	obj->SetPriority(1000);
	obj->SetPos(game->GetWindowWidth() / 2.0f, game->GetWindowHeight() + game->GetWindowCenter().y);

	// BGMの再生
	cSoundCtrl* sc = (cSoundCtrl*)GetRoot()->FindChild("SoundCtrl");
	if (sc) sc->BGMPlay(SOUND_ID::BGM0);

	// セーブデータ読み込み
	cSaveData saveData;
	// セーブデータ構造体内のハイスコアを取得し、メンバに保存する
	m_nHiScore = saveData.Load("Score.dat").HiScore;

	IBaseObject::Initialize();
}
//==========================================================================================
//  更新
//==========================================================================================
void cResult::Update(void)
{
	IBaseObject::Update();

	switch (m_eResultState)
	{
	case RESULT_STATE::START: Start(); break;
	case RESULT_STATE::PAPER: Paper(); break;
	case RESULT_STATE::SCORETEXT: ScoreText(); break;
	case RESULT_STATE::HISCORETEXT: HiScoreText(); break;
	case RESULT_STATE::NEWRECORD: NewRecord(); break;
	case RESULT_STATE::WAIT: Wait(); break;
	}
	
}
//==========================================================================================
//  破棄
//==========================================================================================
IBaseObject* cResult::Finalize(void)
{

	IBaseObject::Finalize();
	return this;
}

//==========================================================================================
//  リザルト開始
//==========================================================================================
void cResult::Start(void)
{
	cSpriteObject* back = (cSpriteObject*)FindChild("ResultBack");
	cGame* game = (cGame*)GetRoot();
	cControllerManager* cm = (cControllerManager*)GetParent()->FindSibling("ControllerManager");
	cTimer* startTimer = (cTimer*)FindChild("StartTimer");
	float startPos = game->GetWindowHeight() + game->GetWindowCenter().y;
	float goalPos = game->GetWindowCenter().y + game->GetWindowCenter().y / 2.0f;

	if (back)
	{
		if (!startTimer)
		{
			startTimer = CreateObject<cTimer>(this, "StartTimer");
			startTimer->Setup(1.0f);
		}
		back->SetPosY(Easing::OutBack(startTimer->GetTime(),startTimer->GetLimit(), goalPos,startPos,3.5f));
	}

	// ボタンが押されたら次の状態に遷移
	if (cm->CheckTrigger(cControllerManager::KEY_DEFINE::KEY_1)|| startTimer->Finished())
	{
		if (startTimer) startTimer->DeleteObject();
		m_eResultState = RESULT_STATE::PAPER;
		if (back) back->SetPosY(goalPos);

		cSoundCtrl::GetInstance().Play(SOUND_ID::WOOD2);
	}
}
//==========================================================================================
//  紙出現
//==========================================================================================
void cResult::Paper(void)
{
	cGame* game = (cGame*)GetRoot();
	cSpriteObject* obj = (cSpriteObject*)FindChild("ResultPaper");
	cVector2 goalPos = cVector2(game->GetWindowCenter().x, game->GetWindowHeight() - game->GetWindowCenter().y - 30.0f);
	cTimer* paperTimer = (cTimer*)FindChild("PaperTimer");
	cTimer* seTimer = (cTimer*)FindChild("SETimer");
	cControllerManager* cm = (cControllerManager*)GetParent()->FindSibling("ControllerManager");

	// リザルト用紙が生成されていなかったら生成
	if (!obj)
	{
		obj = CreateDrawObject<cSpriteObject>(this, "ResultPaper", "data\\graphic\\result_paper.png");
		obj->SetPriority(1001);
		// 初期座標
		obj->SetPos(PAPER_START_POSX,-PAPER_START_POSY);

		// タイマー作成
		paperTimer = CreateObject<cTimer>(this, "PaperTimer");
		paperTimer->Setup(1.0f);

		// サウンド再生開始タイマー作成
		seTimer = CreateObject<cTimer>(this, "SETimer");
		seTimer->Setup(0.8f);
	}
	// 紙の移動アニメーション
	cVector2 nowPos;
	nowPos.x = Easing::OutSine(paperTimer->GetTime(), paperTimer->GetLimit(), goalPos.x, PAPER_START_POSX);
	nowPos.y = Easing::OutSine(paperTimer->GetTime(), paperTimer->GetLimit(), goalPos.y, PAPER_START_POSY);
	obj->SetPos(nowPos.x,nowPos.y);

	if (seTimer)
	{
		if (seTimer->Finished())
		{
			cSoundCtrl::GetInstance().Play(SOUND_ID::PAPER);
			seTimer->DeleteObject();
		}
	}


	// ボタンが押された又はタイマー経過で次の状態に遷移
	if (cm->CheckTrigger(cControllerManager::KEY_DEFINE::KEY_1) || paperTimer->Finished())
	{
		if (paperTimer) paperTimer->DeleteObject();
		if (seTimer) seTimer->DeleteObject();

		m_eResultState = RESULT_STATE::SCORETEXT;
		obj->SetPos(goalPos.x, goalPos.y);
		obj->SetScale(1.0f);
	}
}

//==========================================================================================
// スコア文字出現
//==========================================================================================
void cResult::ScoreText(void)
{
	cGame* game = (cGame*)GetRoot();
	cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	cTimer* timer = (cTimer*)FindChild("TextAppearTimer");
	cControllerManager* cm = (cControllerManager*)GetParent()->FindSibling("ControllerManager");
	cTextObject* titleText = (cTextObject*)FindChild("TitleText");
	cTextObject* scoreText = (cTextObject*)FindChild("ScoreText");

	if (!titleText)
	{
		titleText = CreateTextObject<cTextObject>(this, "TitleText", "たおしたかず","メイリオ",50,8, DX_FONTTYPE_NORMAL,-1,0);
		titleText->SetDrawColor(IDrawBase::COLOR_FULL_BLACK);
		titleText->SetPriority(1002);
		titleText->SetPos(game->GetWindowCenter().x - titleText->GetWidth() / 2.0f,game->GetWindowCenter().y / 2.0f);
		titleText->SetAlpha(0);
	}
	if (!scoreText)
	{
		scoreText = CreateTextObject<cTextObject>(this,"ScoreText",std::to_string(sm->GetScore()) + " ひき","メイリオ",50,8,DX_FONTTYPE_NORMAL,-1,0);
		scoreText->SetDrawColor(IDrawBase::COLOR_FULL_BLACK);
		scoreText->SetPriority(1002);
		scoreText->SetPos(game->GetWindowCenter().x - scoreText->GetWidth() / 2.0f,game->GetWindowCenter().y / 2.0f + 80);
		scoreText->SetAlpha(0);
	}

	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "TextAppearTimer");
		timer->Setup(1.0f);

		cSoundCtrl::GetInstance().Play(SOUND_ID::WOOD3);
	}
	// テキストを徐々に出現させる
	titleText->SetAlpha((unsigned int)Easing::Linear(timer->GetTime(),timer->GetLimit(),255.0f,0.0f));
	scoreText->SetAlpha((unsigned int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 255.0f, 0.0f));

	// ボタンが押された又はタイマー経過で次の状態に遷移
	if (cm->CheckTrigger(cControllerManager::KEY_DEFINE::KEY_1) || timer->Finished())
	{
		if (timer) timer->DeleteObject();
		titleText->SetAlpha(255);
		scoreText->SetAlpha(255);

		m_eResultState = RESULT_STATE::HISCORETEXT;
	}
}
//==========================================================================================
// ハイスコア文字出現
//==========================================================================================
void cResult::HiScoreText(void)
{
	cGame* game = (cGame*)GetRoot();
	cScoreManager* sm = (cScoreManager*)GetRoot()->FindChild("ScoreManager");
	cTimer* timer = (cTimer*)FindChild("TextAppearTimer");
	cControllerManager* cm = (cControllerManager*)GetParent()->FindSibling("ControllerManager");
	cTextObject* hiTitleText = (cTextObject*)FindChild("HiScoreTitle");
	cTextObject* hiScoreText = (cTextObject*)FindChild("HiScoreText");

	if (!hiTitleText)
	{
		hiTitleText = CreateTextObject<cTextObject>(this, "HiScoreTitle", "さいこうきろく", "メイリオ", 50, 8, DX_FONTTYPE_NORMAL, -1, 0);
		hiTitleText->SetDrawColor(IDrawBase::COLOR_FULL_BLACK);
		hiTitleText->SetPriority(1002);
		hiTitleText->SetPos(game->GetWindowCenter().x - hiTitleText->GetWidth() / 2.0f, game->GetWindowCenter().y);
		hiTitleText->SetAlpha(0);
	}
	if (!hiScoreText)
	{
		hiScoreText = CreateTextObject<cTextObject>(this, "HiScoreText", std::to_string(m_nHiScore) + " ひき", "メイリオ", 50, 8, DX_FONTTYPE_NORMAL, -1, 0);
		hiScoreText->SetDrawColor(IDrawBase::COLOR_FULL_BLACK);
		hiScoreText->SetPriority(1002);
		hiScoreText->SetPos(game->GetWindowCenter().x - hiScoreText->GetWidth() / 2.0f, game->GetWindowCenter().y + 80);
		hiScoreText->SetAlpha(0);
	}

	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "TextAppearTimer");
		timer->Setup(1.0f);

		cSoundCtrl::GetInstance().Play(SOUND_ID::WOOD3);
	}
	// テキストを徐々に出現させる
	hiTitleText->SetAlpha((unsigned int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 255.0f, 0.0f));
	hiScoreText->SetAlpha((unsigned int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 255.0f, 0.0f));

	// ボタンが押された又はタイマー経過で次の状態に遷移
	if (cm->CheckTrigger(cControllerManager::KEY_DEFINE::KEY_1) || timer->Finished())
	{
		if (timer) timer->DeleteObject();
		hiTitleText->SetAlpha(255);
		hiScoreText->SetAlpha(255);

		// ハイスコア更新
		if (m_nHiScore < sm->GetScore())
		{
			cSaveData saveData;
			cSaveData::Data data;
			data.HiScore = sm->GetScore();
			saveData.Save("Score.dat", data);
			m_eResultState = RESULT_STATE::NEWRECORD;
		}
		else
		{
			m_eResultState = RESULT_STATE::WAIT;
		}
	}
}
//==========================================================================================
// ハイスコア更新
//==========================================================================================
void cResult::NewRecord(void)
{
	cGame* game = (cGame*)GetRoot();
	cControllerManager* cm = (cControllerManager*)GetParent()->FindSibling("ControllerManager");
	cTimer* timer = (cTimer*)FindChild("NewRecordTimer");
	cSpriteObject* stamp = (cSpriteObject*)FindChild("NewRecordStamp");
	cTextObject* titleText = (cTextObject*)FindChild("TitleText");

	if (!stamp)
	{
		stamp = CreateDrawObject<cSpriteObject>(this, "NewRecordStamp", "data\\graphic\\hiscoreStamp.png");
		stamp->SetPriority(1010);
		stamp->SetPos(titleText->GetPos().x - 50.0f, titleText->GetPos().y);
	}


	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "NewRecordTimer");
		timer->Setup(0.5f);
		cSoundCtrl::GetInstance().Play(SOUND_ID::NEWRECORD);
	}

	stamp->SetAngle(Easing::OutExp(timer->GetTime(),timer->GetLimit(),15.0f,0.0f));
	stamp->SetScale(Easing::OutBack(timer->GetTime(), timer->GetLimit(), 1.0f, 0.0f, 2.0f));
	
	// ボタンが押された又はタイマー経過で次の状態に遷移
	if (cm->CheckTrigger(cControllerManager::KEY_DEFINE::KEY_1) || timer->Finished())
	{
		stamp->SetScale(1.0f);
		stamp->SetAngle(15.0f);
		if (timer) timer->DeleteObject();
			m_eResultState = RESULT_STATE::WAIT;
	}
}

//==========================================================================================
//  リザルト入力待機
//==========================================================================================
void cResult::Wait(void)
{
	cGame* game = (cGame*)GetRoot();
	cTimer* timer = (cTimer*)FindChild("AppearTimer");
	cTimer* vanishTimer = (cTimer*)FindChild("VanishTimer");
	// ボタンを押してタイトルへアナウンス
	cSpriteObject* back = (cSpriteObject*)FindChild("BackLogo");

	if (!back)
	{
		back = CreateDrawObject<cSpriteObject>(this,"BackLogo","data\\graphic\\back.png");
		back->SetPos(game->GetWindowCenter().x,game->GetWindowCenter().y + 200);
		back->SetPriority(1020);
		back->SetAlpha(0);
	}

	if (!timer)
	{
		timer = CreateObject<cTimer>(this, "AppearTimer");
		timer->Setup(1.0f);
	}
	else
	{
		if (timer->Finished())
		{
			if (!vanishTimer)
			{
				vanishTimer = CreateObject<cTimer>(this,"VanishTimer");
				vanishTimer->Setup(1.0f);
				back->SetAlpha(255);
			}
		}
		else
		{
			back->SetAlpha((int)Easing::Linear(timer->GetTime(), timer->GetLimit(), 255.0f, 0.0f));
		}
	}
	if (vanishTimer)
	{
		if (vanishTimer->Finished())
		{
			timer->DeleteObject();
			vanishTimer->DeleteObject();
			back->SetAlpha(0);
		}
		else
		{
			back->SetAlpha((int)Easing::Linear(vanishTimer->GetTime(), vanishTimer->GetLimit(), 0.0f, 255.0f));
		}
	}
	
	// タイトルシーンへ
	cControllerManager* cm = (cControllerManager*)GetParent()->FindSibling("ControllerManager");
	if (cm)
	{
		if (cm->CheckTrigger(cControllerManager::KEY_DEFINE::KEY_1))
		{
			cSceneManager* sm = (cSceneManager*)GetParent();
			sm->ChangeSceneUniTrans(SCENE_ID::TITLE, "data\\graphic\\rule_00.png");
			if(timer)timer->DeleteObject();
			if(vanishTimer)vanishTimer->DeleteObject();

			cSoundCtrl::GetInstance().Play(SOUND_ID::WARP);
		}
	}
}
