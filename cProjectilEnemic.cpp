#include "cProjectilEnemic.h"


cProjectilEnemic::cProjectilEnemic(void)
{
	active = false;
	delay = 0;
	state = 0;
	seqCount = 0;
}

void cProjectilEnemic::setDimensions(int w, int h) {
	this->w = w;
	this->h = h;

}

void cProjectilEnemic::GetArea(cRect *rc)
{
	(*rc).left = x;
	(*rc).right = x + w;
	(*rc).bottom = y;
	(*rc).top = y + h;
}

bool cProjectilEnemic::canMove() {
	if (delay == 2) {
		delay = 0;
		return true;
	}
	++delay;
	return false;
}

bool cProjectilEnemic::Collapsed(int x, int y) {

	cRect Rect;
	GetArea(&Rect);
	if (Rect.left <= x && Rect.right >= x) {
		return true;
	}
	return false;

}




cProjectilEnemic::~cProjectilEnemic(void)
{
}

bool cProjectilEnemic::getActive()
{
	return active;
}

void cProjectilEnemic::setActive(bool act)
{
	active = act;
	out_map = false;
}

int cProjectilEnemic::getDirection()
{
	return direction;
}

void cProjectilEnemic::setDirection(int dir)
{
	direction = dir;
}

void cProjectilEnemic::setDamage(int damage)
{
	this->damage = damage;
}

int cProjectilEnemic::getDamage()
{
	return damage;
}

int cProjectilEnemic::getType()
{
	return type;
}

void cProjectilEnemic::setType(int type)
{

	this->type = type;
}

void cProjectilEnemic::getPosition(int *posx, int *posy)
{
	*posx = x;
	*posy = y;
}

void cProjectilEnemic::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void cProjectilEnemic::DrawRect(int tex_id)
{
	//x + WIDTH PLAYER
	int posx = this->x;
	int posy = this->y;


	int screen_x, screen_y;

	float xo = float(1) / IMG_WIDTH;
	float xf = float(32) / IMG_WIDTH;

	float yo = float(1) / IMG_HEIGHT;
	float yf = float(32) / IMG_HEIGHT;


	screen_x = posx;
	screen_y = posy + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y + h);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y + h);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y);


	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void cProjectilEnemic::DrawRectBoss1(int tex_id)
{
	//x + WIDTH PLAYER
	int posx = this->x;
	int posy = this->y;

	float xo, xf, yo, yf;

	float screen_x, screen_y;


	switch (type) {
	case 1:
		xo = (float(0) + state * 36) / IMG_WIDTH_BOSS1;
		xf = (float(36) + state * 36) / IMG_WIDTH_BOSS1;

		yo = float(0) / IMG_HEIGHT_BOSS1;
		yf = float(22) / IMG_HEIGHT_BOSS1;

		if (seqCount == 10) {
			state += 1;
			seqCount = 0;
		}

		++seqCount;

		if (state == 5) state = 0;

		break;
	case 2:
		xo = (float(64) + state * 16) / IMG_WIDTH_BOSS1;
		xf = (float(82) + state * 16) / IMG_WIDTH_BOSS1;

		yo = float(48) / IMG_HEIGHT_BOSS1;
		yf = float(57) / IMG_HEIGHT_BOSS1;

		if (seqCount == 10) {
			state += 1;
			seqCount = 0;
		}

		++seqCount;

		if (state == 5) state = 0;

		break;
	case 3:
		xo = (float(0) + state * 36) / IMG_WIDTH_BOSS1;
		xf = (float(36) + state * 36) / IMG_WIDTH_BOSS1;

		yo = float(58) / IMG_HEIGHT_BOSS1;
		yf = float(79) / IMG_HEIGHT_BOSS1;

		if (seqCount == 10) {
			state += 1;
			seqCount = 0;
		}

		++seqCount;

		if (state == 5) state = 0;

		break;
	case 4:
		xo = (float(63) + state * 16) / IMG_WIDTH_BOSS1;
		xf = (float(82) + state * 16) / IMG_WIDTH_BOSS1;

		yo = float(104) / IMG_HEIGHT_BOSS1;
		yf = float(113) / IMG_HEIGHT_BOSS1;

		if (seqCount == 10) {
			state += 1;
			seqCount = 0;
		}

		++seqCount;

		if (state == 5) state = 0;

		break;


	}



	screen_x = posx;
	screen_y = posy;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y + h);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y + h);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y);


	glEnd();

	glDisable(GL_TEXTURE_2D);
}



void cProjectilEnemic::DrawRectBoss2(int tex_id)
{
	//x + WIDTH PLAYER
	int posx = this->x;
	int posy = this->y;


	int screen_x, screen_y;

	float xo = (float(0) + state * 162) / IMG_WIDTH_BOSS2;
	float xf = (float(162) + state * 162) / IMG_WIDTH_BOSS2;

	float yo = float(14) / IMG_HEIGHT_BOSS2;
	float yf = float(68) / IMG_HEIGHT_BOSS2;

	if (seqCount == 10) {
		state += 1;
		seqCount = 0;
	}

	++seqCount;

	if (state == 4) state = 0;


	screen_x = posx;
	screen_y = posy + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y + h);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y + h);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y);


	glEnd();

	glDisable(GL_TEXTURE_2D);
}



bool cProjectilEnemic::isCollision(int(*map)[SCENE_HEIGHT][SCENE_WIDTH]) {
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;


	tile_x = (x - 32) / TILE_SIZE;
	if (tile_x % TILE_SIZE != 0) tile_x -= 1;
	tile_y = y / TILE_SIZE;
	width_tiles = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;
	if (width_tiles == 0 && tile_x % TILE_SIZE != 0) tile_x -= 1;
	if (height_tiles == 0) height_tiles = 1;


	for (j = 0; j < height_tiles; j++)
	{
		if ((*map)[tile_y + j][tile_x] != 0)	return true;
	}

	return false;

}