#include "DxLib.h"
#include "DungeonMake.h"
#include <time.h>
#include <stdlib.h>

static int wallImage;
static const int MAP_SIZE = 32;
static const int FIELD_WIDTH = 64;
static const int FIELD_HEIGHT = 48;
static const int AREA_MAX = 48;
static const int AREA_SIZE_MIN = 8;

typedef struct {
	int x, y, h, w;
}AREA;

static AREA areas[AREA_MAX];
static int areaCount;

void Field_Initialize() {
	areaCount = 0;
	wallImage = LoadGraph("source/image/Wall.png");
	areas[0].x = 0;
	areas[0].y = 0;
	areas[0].w = FIELD_WIDTH;
	areas[0].h = FIELD_HEIGHT;
	areaCount++;
}

void Display_Area(int Key[256]) {

	if (Key[KEY_INPUT_0] == 1) {
		Field_Initialize();
		srand((unsigned int)time(NULL));
		Sprite_Area(0);
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

void Display_Field() {
	for (int i = 0; i < FIELD_WIDTH * MAP_SIZE; i+=32) {
		for (int j = 0; j < FIELD_HEIGHT * MAP_SIZE; j += 32) {
			DrawGraph(i, j, wallImage, TRUE);

		}
	}
}

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

	//areasizemin‚æ‚è¬‚³‚­‚È‚Á‚½‚ç
	if ((areas[areaIndex].w < AREA_SIZE_MIN) || (areas[areaIndex].h < AREA_SIZE_MIN)
		|| (areas[newAreaIndex].w < AREA_SIZE_MIN) || (areas[newAreaIndex].h < AREA_SIZE_MIN)) {
		areas[areaIndex].w = w;
		areas[areaIndex].h = h;	//‚à‚Æ‚É–ß‚·
		return;
	}

	areaCount++;

	Sprite_Area(areaIndex);
	Sprite_Area(newAreaIndex);
}