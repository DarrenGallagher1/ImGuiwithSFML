// ImGuiwithSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Player.h"
#include "Level.h"
#include "Enemy.h"
#include "Animation.h"
#include "MainMenu.h"
#include <array>
#include <iostream>

const float winWidth = 1800.f;
const float winHeight = 1013.f;

int main() {
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Game");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::Sprite grapplePoint, nullGrapplePoint;
    MainMenu menu;
    Level level;
    level.setBackground("assets/lvl1.png");
    level.setMusic("assets/assets_intro.ogg");
    Player dwarf(355.f, 800.f, 100.f, 80.f, "dwarves.png");
    Enemy enemy(2000, 2880, 48, 64, "assets/monster.png", 48, 92);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::I) {
                menu.inventory = !menu.inventory;
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
                level.levelSwitch = true;
            }

            menu.mainMenuControls(window);
            dwarf.setShot(event, window);
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        window.clear();

        if (!menu.inventory) {

            if (menu.pageNum == 0) {
                menu.setMainMenu(window);
            }

            else if (menu.pageNum == 3) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && menu.pageNum == 3)
                {
                    menu.pageNum = 0;
                }

                dwarf.checkDoor(level);

                if (!level.levelOneComplete && !level.levelTwoComplete && !level.levelThreeComplete) {
                    level.buildLevelOnePlatforms();
                }
                else if (level.levelOneComplete && !level.levelTwoComplete) {
                    level.buildLevelTwoPlatforms();
                }
                else if (level.levelOneComplete && level.levelTwoComplete) {
                    level.buildLevelThreePlatforms(enemy);
                }

                
                window.draw(level.background);

                dwarf.setVelX();

                level.draw(window, dwarf);

                dwarf.initiateGrapple(level.grapplePoints, level.platforms, window);

                dwarf.checkBounds(level.platforms);
                dwarf.update(level.platforms, level.deathZone, window);
                window.draw(dwarf.bullet);
                window.draw(dwarf.healthBar);

                if (dwarf.cangrapple) {
                    dwarf.grapple();
                }

                if (dwarf.rect.getGlobalBounds().intersects(level.lever.getGlobalBounds())) {
                    level.leverPulled = true;
                }

                if (dwarf.grapplePoint != nullptr) {
                    dwarf.setRope();
                    if (dwarf.grappletopoint) {
                        dwarf.drawRope(window);
                    }
                }

                menu.triggerGameOver(dwarf, level);
                menu.triggerGameFinished(level);

                sf::Vector2i position = sf::Mouse::getPosition(window);
                sf::Vector2f tracker = window.mapPixelToCoords(position);

                std::cout << tracker.x << " " << tracker.y << std::endl;
                window.display();
            }

            else if (menu.pageNum == 1) {
                menu.setControlsMenu(window);
            }

            else if (menu.pageNum == 4) {
                menu.setGameOverScreen(window, dwarf, level);
            }

            else if (menu.pageNum == 5) {
                menu.setVictoryScreen(window, enemy, dwarf, level);
            }
        }

        if (menu.inventory) {
            window.clear();

            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f tracker = window.mapPixelToCoords(position);
            menu.setInventoryMenu(window);
            menu.changeEquipment(dwarf, tracker);

            if (menu.cheatsEnabled) {
                ImGui::SetNextWindowSize(ImVec2(200, 300));
                ImGui::Begin("CHEAT MENU", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

                if (ImGui::Button("Teleport to Level 1", ImVec2(150, 50))) {
                    level.levelOneComplete = false;
                    level.levelTwoComplete = false;
                    level.levelThreeComplete = false;

                    level.levelSwitch = true;

                    dwarf.setPosition(200, 800);
                }

                if (ImGui::Button("Teleport to Level 2", ImVec2(150, 50))) {
                    level.levelOneComplete = true;
                    level.levelTwoComplete = false;
                    level.levelThreeComplete = false;

                    level.levelSwitch = true;

                    dwarf.setPosition(100, 50);
                }

                if (ImGui::Button("Teleport to Level 3", ImVec2(150, 50))) {
                    level.levelOneComplete = true;
                    level.levelTwoComplete = true;
                    level.levelThreeComplete = false;

                    level.levelSwitch = true;

                    dwarf.setPosition(300, 250);
                }

                if (ImGui::Button("Infinite Health", ImVec2(150, 50))) {
                    dwarf.decreaseHealth = 0.f;
                }

                if (ImGui::Button("Drawf must Die", ImVec2(150, 50))) {
                    dwarf.dwarfMustDieMode();

                    for (int i = 0; i < level.enemies.size(); i++) {
                        level.enemies[i].dwarfMustDieMode = true;
                    }
                }

                ImGui::End;

                ImGui::SFML::Render(window);
            }

            window.display();
        }
    }
    ImGui::SFML::Shutdown();
}