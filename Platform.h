#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Player.h"

class Platform
{
private:
	float posx;
	float posy;
	bool direction;
	float height;
	float width;
	float velx;
	float vely;
	sf::Color colour;
	sf::RectangleShape platform;

public:

	void setPosition (float x, float y);
	float getPositionX();
	float getPositionY();
	void setSize(float w, float h);
	void setShape();
	void setColour(sf::Color colour);
	void draw(sf::RenderWindow& window);
	void setDirection(float pointA, float pointB);
	void setXVelocity();
	float getXVelocity();
	void movePlatformX(float pointA, float pointB);
	sf::FloatRect getBounds();
	bool getDirection();
	void anchorPlayer(Player& knight);

	Platform(float posx, float posy, float height, float width, sf::Color colour) {
		setSize(width, height);
		setPosition(posx, posy);
		setColour(colour);
		setShape();
	}
};

