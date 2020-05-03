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
	SetGraphMode(512, 384, 32);
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
	Goal_Initialize();
	Enemy_Initialize();


	while (!(ScreenFlip()) && !(ProcessMessage()) && !(ClearDrawScreen()) && !(gpUpdateKey(Key))) {
		if (Return_Player().isClear) {
			DrawFormatString(32, 300, GetColor(255, 0, 0), "GAME CLEAR !!\nPlease input escape key");
			if (Key[KEY_INPUT_ESCAPE]) {
				break;
			}
		}
		else {

			if (!Return_Player().isLiving) {
				DrawFormatString(32, 300, GetColor(255, 0, 0), "GAME OVER\nPlease input escape key");
				if (Key[KEY_INPUT_ESCAPE]) {
					break;
				}
			}
			else {

				//DrawFormatString(100, 200, GetColor(255, 255, 255), "test");

				Player_Update(Key, MAP_SIZE);

				//Enemy_Update(Key, MAP_SIZE);

				//Display_Field();	

				Main_Camera();

				Dungeon_Rebuild();
				//Display_Area(Key);
				//Player_Draw_Debug();		

				count++;
				//Debug();
			}
		}
	}

	Player_Finalize();		

	DxLib_End();			

	return 0;	
}