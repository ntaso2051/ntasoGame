#include "DxLib.h"
#include "Player.h"
#include "DungeonMake.h"
#include <time.h>
#include <stdlib.h>

static const int MAP_SIZE = 32;

static int Key[256];

static int count = 0;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), SetDrawScreen(DX_SCREEN_BACK);	
	//SetGraphMode(2048, 1536, 32);	
	SetGraphMode(384, 288, 32);
	SetWindowSize(1024, 768);	

	if (DxLib_Init() == -1)	
	{
		return -1;		
	}

	Field_Initialize();		

	srand((unsigned int)time(NULL));	

	Sprite_Area(0);		
	Generate_Field();
	Player_Initialize();		


	while (!(ScreenFlip()) && !(ProcessMessage()) && !(ClearDrawScreen()) && !(gpUpdateKey(Key))) {

		DrawFormatString(100, 200, GetColor(255, 255, 255), "test");

		Player_Update(Key, MAP_SIZE);	
		
		//Display_Field();	

		Main_Camera();

		//Display_Area(Key);
		Player_Draw();		
		

		count++;
		Debug();

	}

	Player_Finalize();		

	DxLib_End();			

	return 0;	
}