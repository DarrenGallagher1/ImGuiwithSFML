#pragma once
class Enemy;
class Player;
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include <vector>

class Level {

private:
	Enemy* enemy;
	Player* player;
	
public:
	std::vector<Platform> platforms;
	std::vector<Platform> deathZone;
	std::vector<sf::Sprite> grapplePoints;
	std::vector<Enemy> enemies;
	float winWidth = 1800.f;
	float winHeight = 1013.f;
	std::string musicFileName;
	sf::Music music;
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
	bool leverPulled = false;
	bool levelSwitch = true;
	bool levelOneComplete = false;
	bool levelTwoComplete = false;
	bool levelThreeComplete = false;
	
	void buildLevelOne();
	void buildLevelTwo();
	void buildLevelThree(Enemy &enemy);
	void destroyLevel();
	void draw(sf::RenderWindow& window, Player &player);
	void setFileName(std::string fileName);
	void setLever(float posx, float posy);
	void checkLever();
	void setDoor(float posx, float posy);
	void setGrapplePoints();
	void setBackground(std::string fileName);
	void setMusic(std::string fileName);
};

