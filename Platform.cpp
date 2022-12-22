#include "Platform.h"

void Platform::setPosition(float x, float y) {
	posx = x;
	posy = y;
}

float Platform::getPositionX() {
    return posx;
}

float Platform::getPositionY() {
	return posy;
}

void Platform::setSize(float w, float h) {
	width = w;
	height = h;
}

void Platform::setShape() {
	platform.setFillColor(colour);
	platform.setSize({ height, width });
	platform.setPosition({ posx, posy });
}

void Platform::setColour(sf::Color colour) {
    this->colour = colour;
}

void Platform::draw(sf::RenderWindow& window) {
	window.draw(platform);
}

void Platform::setDirection(float pointA, float pointB) {

        if (platform.getPosition().x == pointA) {
            direction = true;
        }

        if (platform.getPosition().x == pointB) {
            direction = false;
        }
}

void Platform::setXVelocity() {
	if (direction) {
		velx = 2.f;
	}
	else {
		velx = -2.f;
	}
}

float Platform::getXVelocity() {
	return velx;
}

void Platform::movePlatformX(float pointA, float pointB) {
	setDirection(pointA, pointB);
	setXVelocity();
	posx += velx;
	platform.setPosition(posx, posy);
}

sf::FloatRect Platform::getBounds() {
	return platform.getGlobalBounds();
}

bool Platform::getDirection() {
	return direction;
}

