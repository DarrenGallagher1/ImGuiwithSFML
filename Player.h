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
	sf::Vector2f playerPosition;
	sf::Vector2f playerVelocity;
	sf::Vector2f distanceBetween;

	float distance;
	float height;
	float width;
	float indirVelX = 0.f;
	float gravity = 0.7f;
	float groundHeight = 930.f;
	float bulletdistancex;
	float bulletdistancey;
	float bulletVelocityX;
	float bulletVelocityY;
	float ndistancex;
	float ndistancey;
	float inverseDistance;
	float bulletInverseDistance;
	bool lift = false;
	bool onLedge = false;
	bool anchored;
	sf::Texture texture;
	sf::Color borderColor;
	sf::Color colour;
	float healthBarX = 20.f;
	float healthBarY = 20.f;

	sf::Vector2f playerHealth = sf::Vector2f(100.f, 20.f);

	float decreaseHealth = 10.f;

public:
	sf::RectangleShape healthBar;
	bool cangrapple = false;
	bool grappletopoint = false;
	bool shot = false;
	bool ropeGrow = false;
	sf::RectangleShape bullet;
	
	sf::RectangleShape topBound;
	sf::RectangleShape leftBound;
	sf::RectangleShape rightBound;
	sf::RectangleShape bottomBound;
	sf::RectangleShape hurtBox;
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
	bool isLeftOf(float currentPositionX,float targetPositionX);
	void setColour(sf::Color colour);
	void setShape();
	void setTexture();
	void setGroundHeight(float height);
	void setVelX();
	float getVelX();
	void setVelY(float vely);
	float getVelY();
	void setGrappleVelocity(float velx, float vely);
	void setDistanceBetween(sf::Vector2f targetPosition);
	sf::Vector2f getDistanceBetween();
	float getInversedDistance();

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
	bool checkGrapplePath(std::vector<Platform> ledges, sf::Sprite grapplePoint);
	void checkDoor(Level& level);
	void attack();

	float getHealthBarPositionX();
	float getHealthBarPositionY();
	void setHealthBarPosition(float x, float y);
	float getDecreaseHealth();
	sf::Vector2f getPlayerHealth();
	void setPlayerHealth();

	void setHealthBarShape();

	Player(float posx, float posy, float width, float height, std::string fileName) {
		setPosition(posx, posy);
		setSize(width, height);
		animation.setFileName(fileName);
		animation.setAnimation(0.f, 0.f, width, height, 300.f);
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

