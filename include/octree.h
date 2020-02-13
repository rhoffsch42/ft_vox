#pragma once

#include <iostream>

enum status {
	empty,
	full,
	both
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
	QuadNode();

	QuadNode *	a;
	QuadNode *	b;
	QuadNode *	c;
	QuadNode *	d;
	status		status;
	char		data;
	/*
		Obj3d *	cube;
		sera en fait un descriptif du cube et pas un ptr:
			texture
			is breakable
			...
	*/
private:
};
