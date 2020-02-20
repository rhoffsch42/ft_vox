#pragma once

#include <cstdlib>
#include <iostream>
#include <stdlib.h>

class Pixel
{
public:
	Pixel() {
		r = 0;
		g = 0;
		b = 0;
	}
	Pixel(int red, int green, int blue) {
		r = red;
		g = green;
		b = blue;
	}
	int	r;
	int	g;
	int	b;
};

/*
_________
| A | B |
|---|---|
| C | D |
`````````
*/

class QuadNode
{
public:
	QuadNode(Pixel** tab, int x, int y, int width, int height, int threshold);
	bool		isLeaf() const;

	QuadNode **	children;
	Pixel		pixel;
	int			x;
	int			y;
	int			width;
	int			height;
	/*
		Obj3d *	cube;
		sera en fait un descriptif du cube et pas un ptr:
			texture
			is breakable
			...
	*/
private:
};