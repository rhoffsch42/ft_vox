#include "QuadTree.hpp"

Pixel   getAverage(Pixel** tab, int x, int y, int width, int height) {
	std::cout << "__getA.. " << width << "x" << height << " at " << x << ":" << y << std::endl;
	Pixel	average;
	//Adds the color values for each channel.
	for (int j = y; j < y + height; j++) {
		for (int i = x; i < x + width; i++) {
			std::cout << tab[j][i].r << "_" << tab[j][i].g << "_" << tab[j][i].b << std::endl;
			average.r += tab[j][i].r;
			average.g += tab[j][i].g;
			average.b += tab[j][i].b;
		}
	}

	//number of pixels evaluated
	int area = width * height;
	average.r /= area;
	average.g /= area;
	average.b /= area;

	// Returns the color that represent the average.
	return average;
}

int	measureDetail(Pixel** tab, int x, int y, int width, int height) {
	Pixel	average = getAverage(tab, x, y, width, height);
	int		colorSum = 0;

	// Calculates the distance between every pixel in the region
	// and the average color. The Manhattan distance is used, and
	// all the distances are added.
	for (int j = y; j < y + height; j++) {
		for (int i = x; i < x + width; i++) {
			colorSum += std::abs(average.r - tab[j][i].r);
			colorSum += std::abs(average.g - tab[j][i].g);
			colorSum += std::abs(average.b - tab[j][i].b);
		}
	}

	// Calculates the average distance, and returns the result.
	// We divide by three, because we are averaging over 3 channels.
	return (colorSum / (3 * width * height));
}

QuadNode::QuadNode(Pixel** tab, int x, int y, int w, int h, int threshold) {
	std::cout << "__ QuadNode::QuadNode(...)" << std::endl;
	this->children = nullptr;
	this->pixel.r = -1;
	this->pixel.g = -1;
	this->pixel.b = -1;
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	if (measureDetail(tab, x, y, w, h) < threshold) {//too little detail
		this->pixel = getAverage(tab, x, y, w, h);
		std::cout << this->pixel.r << " " << this->pixel.g << " " << this->pixel.b << std::endl;
	} else {
		//enough detail to split
		this->children = (QuadNode**)malloc(sizeof(QuadNode*) * 4);
		if (!this->children) {
			std::cout << "malloc failed\n"; exit(5);
		}
		this->children[0] = nullptr;
		this->children[1] = nullptr;
		this->children[2] = nullptr;
		this->children[3] = nullptr;

		/*
			Le probleme vient des maps impaires (width et/ou height)
				+ ratio initial 1000x100 => 100x10 => 10x1 => 5x1
				+ division qui donnent des carre impaire (2,6,10,14,18,...  ie: 2x 1,3,5,7,9,11,13,...)
			separation des nodes child, certaines deviennent donc inexistentes
				-> 1122
				-> 112
		*/
		int	halfWidth = this->width / 2;
		int	halfHeight = this->height / 2;

		//upper left quadrant
		this->children[0] = new QuadNode(tab, x, y, halfWidth, halfHeight, threshold);

		//upper right quadrant
		if (halfWidth > 0)
			this->children[1] = new QuadNode(tab, x + halfWidth, y, this->width - halfWidth, halfHeight, threshold);

		//lower left quadrant
		if (halfHeight > 0)
			this->children[2] = new QuadNode(tab, x, y + halfHeight, halfWidth, this->height - halfHeight, threshold);

		//lower right corner
		if (halfWidth > 0 && halfHeight > 0)
			this->children[3] = new QuadNode(tab, x + halfWidth, y + halfHeight, this->width - halfWidth, this->height - halfHeight, threshold);
	}
}

bool		QuadNode::isLeaf() const {
	return (this->children == nullptr);
}
