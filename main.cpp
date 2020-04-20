#include "DxLib.h"
#include "Player.h"
#include "DungeonMake.h"
#include <time.h>
#include <stdlib.h>

static const int MAP_SIZE = 32;

static int Key[256]; //キーが押されているフレーム数を格納する

static int count = 0;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), SetDrawScreen(DX_SCREEN_BACK);	// Windowモードに変更 裏画面設定
	SetGraphMode(2048, 1536, 32);	//全Fieldの大きさ
	SetWindowSize(1024, 768);	//Windowサイズちょうどよく

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	Player_Initialize();		//Playerの初期化
	Field_Initialize();		//Fieldの初期化

	srand((unsigned int)time(NULL));	//乱数の初期化

	Sprite_Area(0);		//エリアの分割
	Generate_Field();


	//while(裏画面を表画面に反映 メッセージ処理 画面クリア キーの更新)
	while (!(ScreenFlip()) && !(ProcessMessage()) && !(ClearDrawScreen()) && !(gpUpdateKey(Key))) {

		DrawFormatString(100, 200, GetColor(255, 255, 255), "test");

		Player_Update(Key, MAP_SIZE);	//Player更新
		
		Display_Field();	//Field描画


		Display_Area(Key);
		Player_Draw();		//Player描画
		

		count++;

	}

	Player_Finalize();		

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}