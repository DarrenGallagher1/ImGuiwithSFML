#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Animation.h"
#include "Level.h"
#include <vector>
#include <iostream>

class Player
{
private:
	
	const float SCREENWIDTH = 1800.f;
	const float SCREENHEIGHT = 1013.f;
	float posy;
	float height;
	float width;
	float vely;
	float indirVelX = 0.f;
	float gravity = 0.7;
	float groundHeight = 930.f;
	bool lift = false;
	bool onLedge = false;
	bool anchored;
	sf::Texture texture;
	sf::Color borderColor;
	sf::Color colour;

public:

	bool cangrapple = false;
	bool grappletopoint = false;
	bool shot = false;
	bool ropeGrow = false;
	float distancex;
	float distancey;
	float distance;
	float bulletdistancex;
	float bulletdistancey;
	float ndistancex;
	float ndistancey;
	float inverseDistance;
	float bulletInverseDistance;
	float accelx, accely;
	sf::RectangleShape bullet;
	float bulletsVelX;
	float bulletsVelY;
	sf::RectangleShape topBound;
	sf::RectangleShape leftBound;
	sf::RectangleShape rightBound;
	sf::RectangleShape bottomBound;
	sf::RectangleShape hurtBox;
	float velx;
	float posx;
	Animation animation;
	sf::RectangleShape rect;
	sf::Vertex rope[5];
	sf::Sprite grapplePoint;

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
	void setTexture();
	void setGroundHeight(float height);
	void setVelX();
	float getVelX();
	void setVelY(float vely);
	float getVelY();
	void setGrappleVelocity(float velx, float vely);
	void jump();
	void update(sf::RenderWindow& window);
	void movePlayer();
	sf::FloatRect getBounds();
	sf::RectangleShape getShape();
	void setIndirVelX(float vel);
	void grapple(sf::Sprite grapplePoint, float direction);
	bool getOnLedge();
	void setOnLedge(bool onLedge);
	void anchor(Platform platform);
	void setShapeColour(sf::Color colour);
	void shoot(std::vector<Platform> ledges, sf::RenderWindow& window);
	void checkBounds(std::vector<Platform> platforms);
	void setRope(sf::Sprite grapplePoint);
	void drawRope(sf::RenderWindow& window);
	/*void assignGrapplePoint(std::vector<sf::Sprite> grapplePoints);*/
	bool checkGrapplePath(Platform ledges[], int arraysize, Platform grapplePoint);

	Player(float posx, float posy, float width, float height, std::string fileName) {
		setPosition(posx, posy);
		setSize(width, height);
		setGroundHeight(1013.f);
		animation.setFileName(fileName);
		animation.setAnimation(0, 0, width, height, 300);
		setTexture();
		rect.setTexture(&texture);
		setShape();
		rect.setOrigin({ rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2 });
		topBound.setSize({ rect.getGlobalBounds().width / 2 - 2.f, 5.f });
		bottomBound.setSize({ rect.getGlobalBounds().width / 2 - 10.f, 5.f });
		leftBound.setSize({ 10.f, rect.getGlobalBounds().height / 2 });
		rightBound.setSize({ 10.f, rect.getGlobalBounds().height / 2 });
		hurtBox.setSize({ 10.f, 30.f });
		hurtBox.setOrigin({ 25.f, 20.f });
		hurtBox.setFillColor(sf::Color::White);
		topBound.setFillColor(sf::Color::Transparent);
		leftBound.setFillColor(sf::Color::Transparent);
		rightBound.setFillColor(sf::Color::White);
		bottomBound.setFillColor(sf::Color::White);
		bullet.setFillColor(sf::Color::Transparent);
	}
};

