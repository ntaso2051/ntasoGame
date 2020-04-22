#include "DxLib.h"
#include "DungeonMake.h"
#include <time.h>
#include <stdlib.h>

enum {
	CELL_TYPE_NONE,
	CELL_TYPE_WALL
};

static int wallImage;
static int floorImage;
static const int MAP_SIZE = 32;
static const int FIELD_WIDTH = 64;
static const int FIELD_HEIGHT = 48;
static const int AREA_MAX = 48;
static const int AREA_SIZE_MIN = 8;

int field[FIELD_HEIGHT][FIELD_WIDTH];

typedef struct {
	int x, y, h, w;
} ROOM;

typedef struct {
	int x, y, h, w;
	ROOM room;
}AREA;

static AREA areas[AREA_MAX];
static int areaCount;

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

void Generate_Field() {

	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			field[y][x] = 0;
		}
	}

	for (int i = 0; i < areaCount; i++) {
		areas[i].room.x = areas[i].x + 2;
		areas[i].room.y = areas[i].y + 2;
		areas[i].room.h = areas[i].h - 4;
		areas[i].room.w = areas[i].w - 4;

		for (int y = areas[i].room.y; y < areas[i].room.y + areas[i].room.h; y++){
			for (int x = areas[i].room.x; x< areas[i].room.x + areas[i].room.w; x++) {
				field[y][x] = 1;
			}
		}
	}
}

void Display_Field() {
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			if (field[y][x] == 0) {
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

//Field描画
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
		areas[areaIndex].w /= 2;

		areas[newAreaIndex].x = areas[areaIndex].x + areas[areaIndex].w;
		areas[newAreaIndex].y = areas[areaIndex].y;
		areas[newAreaIndex].w = w - areas[areaIndex].w;
		areas[newAreaIndex].h = areas[areaIndex].h;
	}
	else
	{
		areas[areaIndex].h /= 2;

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