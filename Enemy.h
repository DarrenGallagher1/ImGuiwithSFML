#pragma once
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Player.h"
#include <vector>

class Enemy{
private:
	float positionX;
	float positionY;

	float width;
	float height;

	bool direction;
	float velx;

	bool death = false;

	float scaleX;
	float scaleY;

	sf::Texture texture;
	sf::Vector2f rectScale = sf::Vector2f(5.f, 5.f);

	float enemyHealth = 100.f;
	float decreaseHealth = 25.f;

public:
	Animation animation;

	sf::RectangleShape enemyRect;

	float getPositionX();
	float getPositionY();
	void setPosition(float x, float y);

	float getWidth();
	float getHeight();
	void setRectSize(float w, float h);


	void flippedRect();
	sf::Vector2f getRectScale();

	void setEnemyShape();
	void setTexture();

	void setDirection(float pointA, float pointB);
	bool getDirection();

	void setXVelocity();
	float getXVelocity();
	void moveEnemyX(float pointA, float pointB);
	sf::Texture getTexture();

	float getDecreaseHealth();
	float getEnemyHealth();
	void setEnemyHealth();

	void enemyCollision(Player &player);

	void setScaleValues(float x, float y);


	void update(sf::RenderWindow& window);

	Enemy(float positionX, float positionY, float width, float height, std::string fileName, int incrementFrame, int endPoint);
};

