#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void)
{
	seq=0;
	delay=0;

	stopDown = false;
	stopUp = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}
bool cBicho::Collides(cRect *rc)
{

	int top, bottom, left, right;
	top = y + h;
	left = x;
	right = x + w;
	bottom = y;

	return (rc->left < right) && (left < rc->right) && (rc->bottom < top) && (bottom < rc->top);
}
bool cBicho::CollidesMapWall(int (*map)[SCENE_HEIGHT][SCENE_WIDTH], bool right)
{
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if (right)	tile_x += width_tiles;

	for (j = 0; j<height_tiles; j++)
	{
		if ((*map)[tile_y + j][tile_x] != 0) return true;
	}

	return false;
}

bool cBicho::CollidesMapFloor(int (*map)[SCENE_HEIGHT][SCENE_WIDTH], bool up)
{
	int tile_x, tile_y;
	int width_tiles, height_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;
	if ((x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i = 0;
	int desc = 0;
	if (up) desc = +1;
	while ((i<width_tiles) && !on_base)
	{
		if ((y % TILE_SIZE) == 0)
		{
			if ((*map)[(tile_y + desc)][(tile_x + i)] != 0)
				on_base = true;
		}
		else
		{
			if ((*map)[(tile_y) + desc][(tile_x + i)] != 0)
			{
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}
void cBicho::GetArea(cRect *rc)
{
	(*rc).left  = x;
	(*rc).right  = x+w;
	(*rc).bottom = y;
	(*rc).top    = y+h;
}
void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;


	screen_x = x;
	screen_y = y + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y+h);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y);
		
		
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

bool cBicho::MoveLeft(int (*map)[SCENE_HEIGHT][SCENE_WIDTH])
{
	cScene cScene;
	int limit = cScene.velocitat;
	if ((x - STEP_LENGTH) > limit) {
		int xaux = x;
		x -= STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
			return true;
		}
		
	}
	return false;
}
bool cBicho::MoveRight(int (*map)[SCENE_HEIGHT][SCENE_WIDTH])
{
	cScene Scene;
	int limit = Scene.velocitat + 640 - w;

	if ((x + STEP_LENGTH) < limit) {
		int xaux = x;
		x += STEP_LENGTH;

		if (CollidesMapWall(map, true))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
			return true;
		}
		
	}

	return false;
}


bool cBicho::MoveDown(int (*map)[SCENE_HEIGHT][SCENE_WIDTH])
{
	int yaux;

	//Whats next tile?
	if ((y % TILE_SIZE) == 0)
	{
		yaux = y;
		y -= STEP_LENGTH;

		if (CollidesMapFloor(map, false))
		{
			
			y = yaux;
			state = STATE_LOOKRIGHT;
			return true;
		}
	}
	//Advance, no problem
	else
	{
		y -= STEP_LENGTH;
		if (state != STATE_WALKDOWN)
		{
			state = STATE_WALKDOWN;
			seq = 0;
			delay = 0;
		}
	}

	return false;
}
void cBicho::Stop()
{
	switch(state)
	{
	case STATE_WALKUP:	state = STATE_LOOKRIGHT; stopUp = true;		break;
	case STATE_WALKDOWN:	state = STATE_LOOKRIGHT; stopDown = true;	break;
	}

//	if (CollidesMapWall(c))
}
bool cBicho::MoveUp(int (*map)[SCENE_HEIGHT][SCENE_WIDTH])
{

	int yaux;

	//Whats next tile?
	if ((y % TILE_SIZE) == 0)
	{
		yaux = y;
		y += STEP_LENGTH;

		if (CollidesMapFloor(map, true))
		{
			y = yaux;
			state = STATE_LOOKRIGHT;
			return true;
		}
	}
	//Advance, no problem
	else
	{
		y += STEP_LENGTH;

		if (state != STATE_WALKUP)
		{
			state = STATE_WALKUP;
			seq = 0;
			delay = 0;
		}
	}

	return false;
	
}

/*
void cBicho::Logic(int *map)
{
	float alfa;

	if(jumping)
	{
		jump_alfa += JUMP_STEP;
		
		if(jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else
	{
		//Over floor?
		if(!CollidesMapFloor(map))
			y -= (2*STEP_LENGTH);
	}
}*/
void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}

void cBicho::Shoot() {
	
}