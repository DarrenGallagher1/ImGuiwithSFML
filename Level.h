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
	std::vector<sf::Sprite> grapplePoints;
	float winWidth = 1800.f;
	float winHeight = 1013.f;
	sf::Sprite lever;
	sf::Sprite door;
	sf::Sprite background;
	std::string leverFileName;
	std::string doorFileName;
	std::string grappleFileName;
	sf::Texture leverTexture;
	sf::Texture doorTexture;
	sf::Texture grappleStone;
	sf::Texture backgroundTexture;
	bool leverPulled;
	

	void buildLevelOnePlatforms();
	void buildLevelTwoPlatforms();
	void destroyLevel();
	void draw(sf::RenderWindow& window);
	void setFileName(std::string fileName);
	void setLever(float posx, float posy);
	void checkLever();
	void setDoor(float posx, float posy);
	void setGrapplePoints();
	void setBackground(std::string fileName);
};

