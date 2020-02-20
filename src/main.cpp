#include <iostream>
#include <string>
#include "Node.hpp"
#include "QuadTree.hpp"

void		test_binaryTree() {
	int arr[] = { 25,20,36,10,22,30,40,5,12,28,38,48,1,8,15,45,50 };//17
	Node* head = new Node(arr[0]);
	for (size_t i = 1; i < 17; i++) {
		head->insert(arr[i]);
	}

	std::cout << "The tree has " << Node::amount << " nodes" << std::endl;

	for (size_t i = 0; i < 17; i++) {
		std::cout << "searched " << arr[i] << "\t" << head->contain(arr[i]) << " turns" << std::endl;
	}
	int nn = 99;
	std::cout << "searched " << nn << "\t" << head->contain(nn) << " turns" << std::endl;
}

void		fillScreen(char*** screen, int len, QuadNode * node, int * leafAmount) {
	if (!node)
		return ;
	if (node->isLeaf()) {
		(*leafAmount)++;
		std::cout << "leaf: " << node->width << "x" << node->height << " at " << node->x << ":" << node->y << std::endl;
		char color;
		if (node->pixel.r == 255) {			color = 0;}
		else if (node->pixel.g == 255) {	color = 1; }
		else if (node->pixel.b == 255) {	color = 2; }
		else {
			std::cout << "error with the pixel\n";
			std::cout << node->pixel.r << " " << node->pixel.g << " " << node->pixel.b << std::endl;
			exit(1);
		}
		if (node->width == 0 || node->height == 0 || node->width > len || node->height > len) {
			std::cout << "error with tree data\n"; exit(2);
		}

		if (0) {
			char** t = *screen;
			for (int j = 0; j < node->height; j++) {
				for (int i = 0; i < node->width; i++) {
					t[node->y + j][node->x + i] = color;
				}
			}
		}
	} else {
		fillScreen(screen, len, node->children[0], leafAmount);
		fillScreen(screen, len, node->children[1], leafAmount);
		fillScreen(screen, len, node->children[2], leafAmount);
		fillScreen(screen, len, node->children[3], leafAmount);
	}
}
void		test_quad() {
	Pixel	red(255, 0, 0);
	Pixel	green(0, 255, 0);
	Pixel	blue(0, 0, 255);

	int len = 7;
	Pixel** dataPixel = (Pixel**)malloc(sizeof(Pixel*) * len);
	for (int j = 0; j < len; j++) {
		dataPixel[j] = (Pixel*)malloc(sizeof(Pixel) * len);
		for (int i = 0; i < len; i++) {
			dataPixel[j][i].r = 0;
			dataPixel[j][i].g = 0;
			dataPixel[j][i].b = 0;
			if (1) {
				int r = std::abs(rand()) % 2;
				if (r == 0)
					dataPixel[j][i].r = red.r;
				else if (r == 1)
					dataPixel[j][i].g = green.g;
				else if (r == 2)
					dataPixel[j][i].b = blue.b;
			}
			else {
				if (j < len / 2) {
					if (i < len / 2) {
						dataPixel[j][i].r = red.r; // upper left
					} else {
						dataPixel[j][i].g = green.g; // upper right
					}
				} else {
					if (i < len / 2) {
						dataPixel[j][i].b = blue.b; // bottom left
					}
					else {
						dataPixel[j][i].r = red.r; // bottom right
					}
				}
			}
		}
	}

	QuadNode* root = new QuadNode(dataPixel, 0, 0, len, len, 50);
	std::cout << (root->isLeaf() ? "true" : "false") << std::endl;

	int	leafAmount = 0;
	char** screen = (char**)malloc(sizeof(char*) * len);
	for (int i = 0; i < len; i++) {
		screen[i] = (char*)malloc(sizeof(char) * len);
		for (int m = 0; m < len; m++) {
			std::cout << (int)screen[i][m] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	fillScreen(&screen, len, root, &leafAmount);
	string color[] = { "\033[31m", "\033[32m", "\033[34m" };
	for (int j = 0; j < len; j++) {
		for (int i = 0; i < len; i++) {
			//std::cout << j << "_" << i << "_" << (int)(screen[j][i]);
			std::cout << color[(int)(screen[j][i])] << "X ";
		}
		std::cout << std::endl;
	}
	std::cout << "\033[0m" << "leafs: " << leafAmount << std::endl;
}
#include <ctime>
int main() {
	std::srand(std::time(nullptr));
	test_quad();
	return (EXIT_SUCCESS);
}

