#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include <vector>

class Level
{
public:
	std::vector<Platform> platforms;
	std::vector<Platform> deathZone;
	float winWidth = 1800.f;
	float winHeight = 1013.f;
	sf::Sprite lever;
	sf::Sprite door;
	std::string leverFileName;
	std::string doorFileName;
	sf::Texture leverTexture;
	sf::Texture doorTexture;
	bool leverPulled;
	

	void buildLevelOnePlatforms();
	void buildLevelTwoPlatforms();
	void destroyLevel();
	void draw(sf::RenderWindow& window);
	void setFileName(std::string fileName);
	void setLever(float posx, float posy);
	void checkLever();
	void setDoor(float posx, float posy);
};

