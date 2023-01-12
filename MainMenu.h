#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Player.h"
#include <iostream>
#define Max_Main_Menu 3
#define Min_Main_Menu 0
class MainMenu
{
public:
	MainMenu(float width, float height);

	void draw(sf::RenderWindow& window);
	void Down();
	void Up();
	void clear();
	int optionSelectedMenu;
	int pageNum = 0;
	bool inventory = false;
	sf::RectangleShape Square1;
	sf::RectangleShape Square2;
	sf::RectangleShape Square3;
	sf::RectangleShape Square4;
	sf::RectangleShape Square5;
	sf::RectangleShape Square6;

	//Game Over Screen
	sf::RectangleShape Square7;
	sf::RectangleShape Square8;

	sf::Sprite mainMenuScreen;
	sf::Sprite inventoryScreen;
	sf::Sprite controlsScreen;
	sf::Sprite gameOverScreen;
	sf::Sprite pickaxe;
	sf::Sprite bow;
	sf::Sprite axe;
	sf::Sprite grappleHook;

	sf::Texture textureScreen, texturePickaxe, textureBow, textureAxe, textureGrappleHook, textureControlMenu, textureMainMenu;
	sf::Texture textureGameOverScreen;

	int keyPressed()
	{
		return optionSelectedMenu;
	}

	void drawShape(sf::RenderWindow& window, sf::RectangleShape shape);

	void setInventoryMenu(sf::RenderWindow& window);

	void changeEquipment(Player& player, sf::Vector2f tracker);

	void mainMenuNavigation(sf::RenderWindow& window);

	void setControlsMenu(sf::RenderWindow& window);

	void setMainMenu(sf::RenderWindow& window);

	void mainMenuControls(sf::RenderWindow& window);

	void setGameOverScreen(sf::RenderWindow& window, Player &player);

	void triggerGameOver(Player player);

	MainMenu()
	{

		Square1.setSize({ 211, 118 });
		Square2.setSize({ 211, 118 });
		Square3.setSize({ 211, 118 });
		Square4.setSize({ 211, 118 });
		Square5.setSize({ 211, 118 });
		Square6.setSize({ 160, 155 });

		//Game Over
		Square7.setSize({ 211, 118 });
		Square8.setSize({ 211, 118 });

		Square1.setFillColor(sf::Color::Transparent);
		Square2.setFillColor(sf::Color::Transparent);
		Square3.setFillColor(sf::Color::Transparent);
		Square4.setFillColor(sf::Color::Transparent);
		Square5.setFillColor(sf::Color::Transparent);
		Square6.setFillColor(sf::Color::Transparent);

		//Game Over
		Square7.setFillColor(sf::Color::White);
		Square8.setFillColor(sf::Color::White);

		//Game Over
		Square7.setPosition({ 200, 500 });
		Square8.setPosition({ 700, 500 });



		if (!font.loadFromFile("assets/blacknorthfont.otf")) {}

		textureScreen.loadFromFile("assets/Inventory.png");
		texturePickaxe.loadFromFile("assets/PickAxe.png");
		textureBow.loadFromFile("assets/Bow.png");
		textureAxe.loadFromFile("assets/axe.png");
		textureGrappleHook.loadFromFile("assets/grappling_hook.png");
		textureControlMenu.loadFromFile("assets/Controlls.png");
		textureMainMenu.loadFromFile("assets/Menu.png");
		textureGameOverScreen.loadFromFile("assets/gameoverimgmain.jpg");


		// play 
		mainMenu[0].setFont(font);
		mainMenu[0].setFillColor(sf::Color::Red);
		mainMenu[0].setString("Start");
		mainMenu[0].setCharacterSize(50);
		mainMenu[0].setPosition(sf::Vector2f(1800 / 2 - 50, 1013 / (Max_Main_Menu + 1) + 150));
		// Controls 
		mainMenu[1].setFont(font);
		mainMenu[1].setFillColor(sf::Color::Black);
		mainMenu[1].setString("Controls");
		mainMenu[1].setCharacterSize(50);
		mainMenu[1].setPosition(sf::Vector2f(1800 / 2 - 50, 1013 / (Max_Main_Menu + 1) * 2));
		// Exit 
		mainMenu[2].setFont(font);
		mainMenu[2].setFillColor(sf::Color::Black);
		mainMenu[2].setString("Exit");
		mainMenu[2].setCharacterSize(50);
		mainMenu[2].setPosition(sf::Vector2f(1800 / 2 - 50, 1013 / (Max_Main_Menu + 1) * 2.5));
		optionSelectedMenu = 0;
		std::cout << optionSelectedMenu;
	}

	//~MainMenu();
private:

	sf::Font font;
	sf::Text mainMenu[Max_Main_Menu];
};
