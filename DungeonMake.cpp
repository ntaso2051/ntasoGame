#include "DxLib.h"
#include "DungeonMake.h"
#include <time.h>
#include <stdlib.h>
#include "Player.h"

int wallImage;
int floorImage;

static const int MAP_SIZE = 32;
static const int FIELD_WIDTH = 64;
static const int FIELD_HEIGHT = 48;
static const int AREA_MAX = 48;
static const int AREA_SIZE_MIN = 8;
const int SCREEN_HEIGHT = 9;
const int SCREEN_WIDTH = 12;



static FIELD field;
static AREA areas[AREA_MAX];
static int areaCount;
static int Display[SCREEN_HEIGHT][SCREEN_WIDTH];

FIELD Return_Field(){
	return field;
}

AREA* Return_Areas() {
	return areas;
}

int Return_areaCount() {
	return areaCount;
}

int Return_wallImage() {
	return wallImage;
}

int Return_floorImage() {
	return floorImage;
}

void Main_Camera() {
	CHARACTER player = Return_Player();
	for (int y = -1; y < 10; y++) {
		for (int x = -1; x < 13; x++) {
			if (field.field[player.y / 32 + y - 4][player.x / 32 + x - 6] == CELL_TYPE_NONE && player.y / 32 + y - 4 >=0 && player.x / 32 + x - 6>=0 && player.y / 32 + y - 4 < 48 && player.x / 32 + x - 6 <64) {
				DrawGraph(32 * x - player.scrollX, 32 * y - player.scrollY, floorImage, TRUE);
			}
			else if(field.field[player.y / 32 + y - 4][player.x / 32 + x - 6] == CELL_TYPE_WALL && player.y / 32 + y - 4 >= 0 && player.x / 32 + x - 6 >= 0 && player.y / 32 + y - 4 < 48 && player.x / 32 + x - 6 < 64){
				DrawGraph(32 * x  - player.scrollX, 32 * y - player.scrollY, wallImage, TRUE);
			}
		}
	}
	Player_Draw();
}


//Fieldの初期化
void Field_Initialize() {
	areaCount = 0;
	wallImage = LoadGraph("source/image/Wall.png");
	floorImage = LoadGraph("source/image/floor.png");
	areas[0].x = 0;
	areas[0].y = 0;
	areas[0].w = FIELD_WIDTH;
	areas[0].h = FIELD_HEIGHT;
	areaCount++;
}

//Fieldの作成
void Generate_Field() {

	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			field.field[y][x] = CELL_TYPE_WALL;
		}
	}

	for (int i = 0; i < areaCount; i++) {
		//エリアの内部だけroomにする
		areas[i].room.x = areas[i].x + 2;
		areas[i].room.y = areas[i].y + 2;
		areas[i].room.h = areas[i].h - 4;
		areas[i].room.w = areas[i].w - 4;

		//room部分を床に
		for (int y = areas[i].room.y; y < areas[i].room.y + areas[i].room.h; y++) {
			for (int x = areas[i].room.x; x < areas[i].room.x + areas[i].room.w; x++) {
				field.field[y][x] = CELL_TYPE_NONE;
			}
		}

		//エリアの右下に通路を追加
		for (int x = areas[i].x; x < areas[i].x + areas[i].w; x++) {
			field.field[areas[i].y + areas[i].h - 1][x] = CELL_TYPE_NONE;
		}
		for (int y = areas[i].y; y < areas[i].y + areas[i].h; y++) {
			field.field[y][areas[i].x + areas[i].w - 1] = CELL_TYPE_NONE;
		}

		//通路と部屋をつなげる
		for (int j = areas[i].y; j < areas[i].room.y; j++) {
			srand((unsigned int)time(NULL));
			if (rand() % 2 == 0) {
				field.field[j][areas[i].x + 4] = CELL_TYPE_NONE;
			}
			else {
				field.field[j][areas[i].x + areas[i].w - 4] = CELL_TYPE_NONE;
			}
		}
		for (int j = areas[i].room.y + areas[i].room.h; j < areas[i].y + areas[i].h; j++) {
			srand((unsigned int)time(NULL));
			if (rand() % 2 == 1) {
				field.field[j][areas[i].x + 4] = CELL_TYPE_NONE;
			}
			else {
				field.field[j][areas[i].x + areas[i].w - 4] = CELL_TYPE_NONE;
			}
		}
		for (int j = areas[i].x; j < areas[i].room.x; j++) {
			field.field[areas[i].y + areas[i].room.h / 2][j] = CELL_TYPE_NONE;
		}
		for (int j = areas[i].room.x + areas[i].room.w; j < areas[i].x + areas[i].w; j++) {
			field.field[areas[i].y + areas[i].room.h / 2][j] = CELL_TYPE_NONE;
		}
		
	
	}
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			if (field.field[y][x] == CELL_TYPE_WALL) {
				continue;
			}
			
			int v[][2] = {
				{0,-1},
				{-1,0},
				{0,1},
				{1,0},
			};
			int n = 0;
			for (int i = 0; i < 4; i++) {
				int x2 = x + v[i][0];
				int y2 = y + v[i][1];
				if ((x2 < 0) || (x2 >= FIELD_WIDTH) || (y2 < 0) || (y2 >= FIELD_WIDTH)) {
					n++;
				}
				else if (field.field[y2][x2] == CELL_TYPE_WALL) {
					n++;
				}
				if (n >= 3) {
					field.field[y][x] = CELL_TYPE_WALL;
				}
			}
		}
	}
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		field.field[y][FIELD_WIDTH - 1] = CELL_TYPE_WALL;
	}
	for (int x = 0; x < FIELD_WIDTH; x++) {

		field.field[FIELD_HEIGHT - 1][x] = CELL_TYPE_WALL;
	}
}

void Display_Field() {
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			if (field.field[y][x] == CELL_TYPE_WALL) {
				DrawGraph(x * 32, y * 32, wallImage, TRUE);
			}
			else {
				DrawGraph(x * 32, y * 32, floorImage, TRUE);
			}
		}
	}
}

//エリアを表示
void Display_Area(int Key[256]) {

	if (Key[KEY_INPUT_0] == 1) {
		Field_Initialize();
		srand((unsigned int)time(NULL));
		Sprite_Area(0);
		Generate_Field();
		Player_Initialize();
	}
	int buffer[FIELD_HEIGHT][FIELD_WIDTH] = {};
	for (int i = 0; i < areaCount; i++) {
		for (int y = areas[i].y; y < areas[i].y + areas[i].h; y++) {
			for (int x = areas[i].x; x < areas[i].x + areas[i].w; x++) {
				buffer[y][x] = i;
			}
		}
	}
	for (int i = 0; i < FIELD_WIDTH * MAP_SIZE; i += 32) {
		for (int j = 0; j < FIELD_HEIGHT * MAP_SIZE; j += 32) {
			DrawFormatString(i, j, GetColor(0, 255, 0), "%d", buffer[j/32][i/32]);
		}
	}
}

//Field描画(デバッグ用)
/*void Display_Field() {
	for (int i = 0; i < FIELD_WIDTH * MAP_SIZE; i+=32) {
		for (int j = 0; j < FIELD_HEIGHT * MAP_SIZE; j += 32) {
			DrawGraph(i, j, wallImage, TRUE);

		}
	}
}
*/

//エリアを分割
void Sprite_Area(int areaIndex) {

	int newAreaIndex = areaCount;
	int w = areas[areaIndex].w;
	int h = areas[areaIndex].h;

	if(rand() % 2)
	{
		if (rand() % 3 == 0) {
			areas[areaIndex].w /= 2;
		}
		else if (rand() % 3 == 1) {
			areas[areaIndex].w /= 4;
		}
		else {
			areas[areaIndex].w /= 8;
		}
		areas[newAreaIndex].x = areas[areaIndex].x + areas[areaIndex].w;
		areas[newAreaIndex].y = areas[areaIndex].y;
		areas[newAreaIndex].w = w - areas[areaIndex].w;
		areas[newAreaIndex].h = areas[areaIndex].h;
	}
	else
	{
		if (rand() % 3 == 0) {
			areas[areaIndex].h /= 4;
		}
		else {
			areas[areaIndex].h /= 2;
		}

		areas[newAreaIndex].x = areas[areaIndex].x;
		areas[newAreaIndex].y = areas[areaIndex].y + areas[areaIndex].h;
		areas[newAreaIndex].w = areas[areaIndex].w;
		areas[newAreaIndex].h = h - areas[areaIndex].h;
	}

	//areasizeminより小さくなったら
	if ((areas[areaIndex].w < AREA_SIZE_MIN) || (areas[areaIndex].h < AREA_SIZE_MIN)
		|| (areas[newAreaIndex].w < AREA_SIZE_MIN) || (areas[newAreaIndex].h < AREA_SIZE_MIN)) {
		areas[areaIndex].w = w;
		areas[areaIndex].h = h;	//もとに戻す
		return;
	}

	areaCount++;

	Sprite_Area(areaIndex);
	Sprite_Area(newAreaIndex);

}