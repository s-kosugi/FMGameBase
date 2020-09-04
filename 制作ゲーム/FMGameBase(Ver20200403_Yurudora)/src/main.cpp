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

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
#ifdef DEBUG
	// アプリケーションログを出力
	SetOutApplicationLogValidFlag(TRUE);
	SetUseDateNameLogFile(TRUE);
	
	_mkdir("Log");
	int ret = SetApplicationLogSaveDirectory("Log");

#else
	SetOutApplicationLogValidFlag(FALSE);
#endif
	
	// ウィンドウタイトル
	SetWindowText("FMGameBase");

	// アイコン設定
	SetWindowIconID(MAINICON);

#ifdef DEBUG
	// ウィンドウモード
	ChangeWindowMode(true);
#else
	// ウィンドウモード
	ChangeWindowMode(false);
#endif


	// 多重起動禁止
	SetDoubleStartValidFlag(FALSE);
	// 画面サイズとカラービット数の指定
	SetGraphMode(cGame::GetInstance().GetWindowWidth(), cGame::GetInstance().GetWindowHeight(), 32);

	// DirectX9を使用するようにする。(DirectX11も可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
		return -1;			// エラーが起きたら直ちに終了

	// Effekseerの初期化
	if (InitEffekseer() == -1) return -1;

	//描画先を裏画面に設定(ダブルバッファ)
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
		return -1;

	// ALTキーやF10キーを無効にする
	SetSysCommandOffFlag(1);

	// ウィンドウが非アクティブ状態でも動作させる
	SetAlwaysRunFlag(TRUE);

	// 描画リストの生成、初期化
	cDrawCtrl::GetInstance().ClearDrawList();

	// ゲームクラスの作成
	cGame& game = cGame::GetInstance();

	// 初期化
	game.Initialize();
#ifdef DEBUG
	cDebugFunc::GetInstance().PushDebugLog("ShaderVersion = " + std::to_string(GetValidShaderVersion()));
	cDebugFunc::GetInstance().PushDebugLog("MultiDrawScreenNum = " + std::to_string(GetMultiDrawScreenNum()));
#endif
	// メインループ
	MainLoop();

	// 破棄
	game.Finalize();

	// Effekseerを終了する。
	// ※フルスクリーン時にエラーが発生する為一旦コメントアウト
	//Effkseer_End();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

//==========================================================================================
// メインループ
//==========================================================================================
void MainLoop(void)
{
	cGame& game = cGame::GetInstance();

	for (;;) {
		int StartTime;

		// 計測開始時刻を保存
		StartTime = GetNowCount();

		// 画面のクリア
		ClearDrawScreen();
		// ゲームの更新
		game.Update();
		// 描画
		game.Draw();

		// 画面を更新(垂直同期+裏画面の内容を表画面にコピー)
		ScreenFlip();

		// メッセージ処理
		if (ProcessMessage() != 0)
			return;

		// 1/60秒を越えるまで待機させる
		while(GetNowCount() < StartTime + 1000 / (int)game.GetFPS());
	}
}

//==========================================================================================
// Effekseer関連の初期化
//==========================================================================================
int InitEffekseer(void)
{
	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(cGame::GetInstance().GetWindowWidth(), cGame::GetInstance().GetWindowHeight());

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	return 0;
}