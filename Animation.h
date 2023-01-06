#pragma once
#include <string>
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

class Animation
{
public:
	std::string fileName = "";
	sf::IntRect coordinates;
	int coordinateWidth, coordinateHeight;
	int startX, startY, endPoint, incrementFrame, row;
	float time = 0.1;
	float switchTime = 1.0;
	float totalTime;
	bool flipped;

	void setFileName(std::string fileName);
	void setAnimation(int startX, int startY, int width, int height, int endPoint);
	void Animate(sf::RectangleShape &rect, float switchTime);
};

