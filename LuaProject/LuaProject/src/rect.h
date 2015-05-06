#ifndef RECT_H
#define RECT_H

class Rect
{
private:
	float halfSize;
	float x1, x2, y1, y2;

public:
	Rect(){};
	Rect(float x, float y, float halfsizes)
	{
		//code goes here
		halfSize = halfsizes;
		update(x, y);
	}

	void update(float x, float y)
	{
		x1 = x - halfSize;
		y1 = y - halfSize;
		x2 = x + halfSize;
		y2 = y + halfSize;
	}
	void updatePlayerRekt(float x, float y)
	{
		x1 = (x / 50) - halfSize;
		y1 = ((y - 800) / 50) - halfSize;
		x2 = x1 + halfSize * 2;
		y2 = y1 + halfSize * 2;
	}
	
	~Rect(){};
	bool intersects(Rect* test)
	{
		if (y2 < test->y1)
			return false; //ouside top
		if (x2 < test->x1)
			return false; //outside left
		if (x1 > test->x2)
			return false; //outside right
		if (y1 > test->y2)
			return false; //outside botom

		return true;
	}

	void fetchData(float* _x1, float* _y1, float* _halfsize)
	{
		*_x1 = x1;
		*_y1 = y1;
		*_halfsize = halfSize;
	}
};

#endif