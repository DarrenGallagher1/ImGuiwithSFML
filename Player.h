#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Animation.h"

class Player
{
private:
	
	const float SCREENWIDTH = 1080.f;
	const float SCREENHEIGHT = 720.f;
	float posy;
	float height;
	float width;
	float vely;
	float indirVelX = 0.f;
	float gravity = 0.5;
	float upGravity = -0.7;
	float downGravity = 0.7;
	float groundHeight;
	bool lift = true;
	bool onLedge = false;
	bool anchored;
	bool walking;
	sf::Texture texture;
	sf::Color borderColor;
	sf::Color colour;
	

public:

	bool cangrapple;
	bool grappletopoint;
	bool shot;
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
	float velx;
	float posx;
	Animation animation;
	sf::RectangleShape rect;

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
	void anchor(Platform platform);
	void setShapeColour(sf::Color colour);
	void grapple(Platform &grapplePoint, float direction);
	void shoot(Platform ledges[], int arraysize, sf::RenderWindow& window);
	void checkBounds(Platform ledges[], int arraysize);

	Player(float posx, float posy, float width, float height, std::string fileName) {
		setPosition(posx, posy);
		setSize(width, height);
		animation.setFileName(fileName);
		animation.setAnimation(0, 0, width, height, 300);
		setTexture();
		rect.setTexture(&texture);
		setShape();
		rect.setOrigin({ rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2 });
		topBound.setSize({ rect.getGlobalBounds().width / 2 - 2.f, 5.f });
		bottomBound.setSize({ rect.getGlobalBounds().width / 2 - 10.f, 5.f });
		leftBound.setSize({ 5.f, rect.getGlobalBounds().height / 2 });
		rightBound.setSize({ 5.f, rect.getGlobalBounds().height / 2 });
		topBound.setFillColor(sf::Color::White);
		leftBound.setFillColor(sf::Color::White);
		rightBound.setFillColor(sf::Color::White);
		bottomBound.setFillColor(sf::Color::White);
		bullet.setFillColor(sf::Color::Transparent);
	}
};

