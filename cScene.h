#pragma once

#include "cData.h"

#define SCENE_WIDTH		16
#define SCENE_DEPTH		32
#define SCENE_HEIGHT	 4

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool Init();
	void Draw(cData *Data);
};
