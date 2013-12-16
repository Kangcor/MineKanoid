#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG	13

//Image identifiers
#define IMG_BRICK	0
#define IMG_PUMPKIN	1
#define IMG_IRON	2
#define IMG_STONE	3
#define IMG_TNT_SIDE	4
#define IMG_GRASS_SIDE	5
#define IMG_GRASS_TOP	6
#define IMG_PUMPKIN_TOP	7
#define IMG_PUMPKIN_FACE	8
#define IMG_TNT_TOP	9

#define IMG_WALL	10
#define IMG_FLOOR	11
#define IMG_ROOF	12

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
