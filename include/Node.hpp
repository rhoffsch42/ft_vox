#pragma once

class Node
{
public:
	static unsigned int amount;
	Node(int v = 0);
	int	contain(int v) const;
	void	insert(int v);

	Node *	left;
	Node *	right;
	int		value;
};

