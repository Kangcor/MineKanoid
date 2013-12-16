#include "cPlayer.h"
#include "Globals.h"

cPlayer::cPlayer(void) {
	position = 0.0f;
}
cPlayer::~cPlayer(void){}

void cPlayer::setPosition(float position)
{
	this->position = position;
}

float cPlayer::getPosition()
{
	return position;
}

void cPlayer::Draw(cData *Data)
{
	if (position > (SCENE_WIDTH / 2) - 1) position = (SCENE_WIDTH / 2) - 1;
	if (position < (-SCENE_WIDTH / 2) + 1) position = (-SCENE_WIDTH / 2) + 1;
	float sd = SCENE_DEPTH / 2.0f,
		sw = SCENE_WIDTH / 2.0f,
		sh = SCENE_HEIGHT / 2.0f;

	float d = PLAYER_DEPTH / 2.0f,
		w = PLAYER_WIDTH / 2.0f,
		h = PLAYER_HEIGHT / 2.0f,
		//Tiling
		td = PLAYER_DEPTH / 4.0f,
		tw = PLAYER_WIDTH / 4.0f,
		th = PLAYER_HEIGHT / 4.0f;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_WALL));

	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-w + position, -sh, 2*d + sd);
	glTexCoord2f(tw, 0.0f); glVertex3f(w + position, -sh, 2*d + sd);
	glTexCoord2f(tw, th); glVertex3f(w + position, 2*h - sh, 2*d + sd);
	glTexCoord2f(0.0f, th); glVertex3f(-w + position, 2*h - sh, 2*d + sd);
	// Back Face
	glTexCoord2f(tw, 0.0f); glVertex3f(-w + position, -sh, sd);
	glTexCoord2f(tw, th); glVertex3f(-w + position, 2*h - sh, sd);
	glTexCoord2f(0.0f, th); glVertex3f(w + position, 2*h - sh, sd);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(w + position, -sh, sd);
	// Right face
	glTexCoord2f(td, 0.0f); glVertex3f(w + position, -sh, sd);
	glTexCoord2f(td, th); glVertex3f(w + position, 2*h - sh, sd);
	glTexCoord2f(0.0f, th); glVertex3f(w + position, 2*h - sh, 2*d + sd);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(w + position, -sh, 2*d + sd);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-w + position, -sh, sd);
	glTexCoord2f(td, 0.0f); glVertex3f(-w + position, -sh, 2*d + sd);
	glTexCoord2f(td, th); glVertex3f(-w + position, 2*h - sh, 2*d + sd);
	glTexCoord2f(0.0f, th); glVertex3f(-w + position, 2*h - sh, sd);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_FLOOR));
	glBegin(GL_QUADS);
	// Bottom Face
	glTexCoord2f(tw, td); glVertex3f(-w + position, -sh, sd);
	glTexCoord2f(0.0f, td); glVertex3f(w + position, -sh, sd);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(w + position, -sh, 2*d + sd);
	glTexCoord2f(tw, 0.0f); glVertex3f(-w + position, -sh, 2*d + sd);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_ROOF));
	glBegin(GL_QUADS);
	// Top Face
	glTexCoord2f(0.0f, td); glVertex3f(-w + position, 2*h - sh, sd);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-w + position, 2*h - sh, 2*d + sd);
	glTexCoord2f(tw, 0.0f); glVertex3f(w + position, 2*h - sh, 2*d + sd);
	glTexCoord2f(tw, td); glVertex3f(w + position, 2*h - sh, sd);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}