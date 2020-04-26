#pragma once

#define DEF_FIELD_H

enum {
	CELL_TYPE_NONE,
	CELL_TYPE_WALL,
	CELL_TYPE_STAIRS,
};

typedef struct {
	int field[48][64];
	int goalX;
	int goalY;
}FIELD;

typedef struct {
	int x, y, h, w;
} ROOM;

typedef struct {
	int x, y, h, w;
	ROOM room;
}AREA;

//他ファイルで使うための返すだけの関数
FIELD Return_Field();
AREA* Return_Areas();
int Return_areaCount();
int Return_wallImage();
int Return_floorImage();

//Fieldを初期化
void Field_Initialize();

//Fieldを表示(デバック用)
void Display_Field();

//エリアを表示(デバック用)
void Display_Area(int Key[256]);

//エリアを分割する
void Sprite_Area(int areaIndex);

//fieldを生成する
void Generate_Field();

//goalを設定
void Goal_Initialize();

//goal到達時にダンジョンを再生成
void Dungeon_Rebuild();