#pragma once

#define DEF_FIELD_H

enum {
	CELL_TYPE_NONE,
	CELL_TYPE_WALL,
};

typedef struct {
	int field[48][64];
}FIELD;

typedef struct {
	int x, y, h, w;
} ROOM;

typedef struct {
	int x, y, h, w;
	ROOM room;
}AREA;

//���t�@�C���Ŏg�����߂̕Ԃ������̊֐�
FIELD Return_Field();
AREA* Return_Areas();
int Return_areaCount();
int Return_wallImage();
int Return_floorImage();

//Field��������
void Field_Initialize();

//Field��\��(�f�o�b�N�p)
void Display_Field();

//�G���A��\��(�f�o�b�N�p)
void Display_Area(int Key[256]);

//�G���A�𕪊�����
void Sprite_Area(int areaIndex);

//field�𐶐�����
void Generate_Field();