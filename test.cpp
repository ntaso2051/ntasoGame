#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), SetDrawScreen(DX_SCREEN_BACK);	// Windowモードに変更 裏画面設定

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//while(裏画面を表画面に反映 メッセージ処理 画面クリア キーの更新
	while (!(ScreenFlip()) && !(ProcessMessage()) && !(ClearDrawScreen())) {

		DrawFormatString(100, 200, GetColor(255, 255, 255), "test");

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}