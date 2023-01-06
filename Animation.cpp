#include "Animation.h"
#include <string>

void Animation::setFileName(std::string fileName){
	this->fileName = fileName;
	}

void Animation::setAnimation(int startX, int startY, int width, int height, int endPoint) {
	coordinates.left = startX;
	coordinates.top = startY;
	coordinates.width = width;
	coordinates.height = height;
	this->endPoint = endPoint;
	this->startX = startX;
	incrementFrame = coordinates.width;
}

void Animation::Animate(sf::RectangleShape &rect, float switchTime) {

	this->switchTime = switchTime;

	totalTime += time;
	if (coordinates.left >= endPoint) {
		coordinates.left = startX;
	}

	if (coordinates.left <= startX) {
		coordinates.left = startX;
	}

	if (totalTime > switchTime) {
		coordinates.left += incrementFrame;
		totalTime -= switchTime;
	}

	rect.setTextureRect(coordinates);

	if (flipped) {
		rect.setScale(-1.f, 1.f);
	} else {
		rect.setScale(1.f, 1.f);
	}
}
