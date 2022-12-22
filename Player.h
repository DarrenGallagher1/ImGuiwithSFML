#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include <queue>

class Player
{
private:
	float posx;
	float posy;
	float height;
	float width;
	float velx;
	float vely;
	float indirVelX = 0.f;
	float gravity = 0.8;
	float upGravity = -0.8;
	float downGravity = 0.8;
	float groundHeight = 720.f;
	bool lift = true;
	bool onLedge = false;
	bool anchored;
	sf::Color colour;
	sf::RectangleShape rect;
	

public:

	float distancex;
	float distancey;
	float bulletdistancex;
	float bulletdistancey;
	float ndistancex;
	float ndistancey;
	float inverseDistance;
	float bulletInverseDistance;
	float accelx, accely;
	sf::RectangleShape bullet;
	std::vector<sf::RectangleShape> bullets;
	std::vector<float> bulletsVelX;
	std::vector<float> bulletsVelY;


	void setPosition(float x, float y);
	float getPositionX();
	float getPositionY();

	void setSize(float w, float h);
	float getWidth();
	float getHeight();
	float getGroundHeight();
	void setAnchor(bool anchor);
	bool getAnchor();
	void setColour(sf::Color colour);
	void setShape();
	void setGroundHeight(float height);
	void setVelX();
	void setGrappleX(float velx);
	float getVelX();
	void setVelY(float vely);
	float getVelY();
	void setGrappleVelocity(float velx, float vely);
	void jump();
	void draw(sf::RenderWindow& window);
	void movePlayer();
	sf::FloatRect getBounds();
	sf::RectangleShape getShape();
	void setIndirVelX(float vel);
	bool getOnLedge();
	void setOnLedge(bool onLedge);
	void anchor();
	void setShapeColour(sf::Color colour);

	Player(float posx, float posy, float width, float height, sf::Color colour) {
		setPosition(posx, posy);
		setSize(width, height);
		setColour(colour);
		setShape();
	}
};

