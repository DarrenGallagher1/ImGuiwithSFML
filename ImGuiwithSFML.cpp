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
#include <array>
#include <iostream>

const float winWidth = 1800.f;
const float winHeight = 1013.f;
bool testMenu = false;
bool move = true;
bool pause = false;
bool yellow = false;
float direction;


int main() {
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "ImGui + SFML");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::Sprite grapplePoint;
    Level level;
    level.setBackground("assets/lvl1.png");
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

            if (event.type == sf::Event::MouseButtonPressed && dwarf.bullet.getFillColor() == sf::Color::Transparent) {

                if (!dwarf.animation.flipped) {
                    if (event.mouseButton.button == sf::Mouse::Right && sf::Mouse::getPosition(window).x < dwarf.getPositionX()) {
                        dwarf.shot = true;
                    }
                }

                if (dwarf.animation.flipped) {
                    if (event.mouseButton.button == sf::Mouse::Right && sf::Mouse::getPosition(window).x > dwarf.getPositionX()) {
                        dwarf.shot = true;
                    }
                }
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
                pause = !pause;
                level.levelSwitch = true;
            }

        }

        if (!pause) {

            dwarf.checkDoor(level);

            if (!level.levelOneComplete && !level.levelTwoComplete && !level.levelThreeComplete) {

                ImGui::SFML::Update(window, deltaClock.restart());
                level.destroyLevel();
                
                level.buildLevelOnePlatforms();
            }

            else if (level.levelOneComplete && !level.levelTwoComplete) {

                ImGui::SFML::Update(window, deltaClock.restart());
                level.destroyLevel();
                level.buildLevelTwoPlatforms();
            }

            else if (level.levelOneComplete && level.levelTwoComplete) {
                ImGui::SFML::Update(window, deltaClock.restart());
                level.destroyLevel();
                level.buildLevelThreePlatforms(enemy);
            }

            window.clear();
            window.draw(level.background);

            dwarf.setVelX();

            ImGui::SFML::Render(window);

            level.draw(window);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dwarf.cangrapple && dwarf.getPositionY() > grapplePoint.getPosition().y) {

                for (int i = 0; i < level.grapplePoints.size(); i++) {
                    sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
                    sf::Vector2f tracker = window.mapPixelToCoords(clickPosition);

                    if (level.grapplePoints[i].getGlobalBounds().contains(tracker)) {
                        dwarf.cangrapple = true;
                        dwarf.grappletopoint = true;
                        grapplePoint = level.grapplePoints[i];
                        break;
                    }
                }

                if (!dwarf.checkGrapplePath(level.platforms, grapplePoint)) {
                    dwarf.cangrapple = false;
                    dwarf.grappletopoint = false;
                }

                if (dwarf.getPositionX() > grapplePoint.getPosition().x) {
                    direction = -1.f;
                    dwarf.animation.flipped = false;
                }
                else {
                    direction = 1.f;
                    dwarf.animation.flipped = true;
                }

            }

            enemy.moveEnemyX(100.f, winWidth - 100.f);
            enemy.enemyCollision(dwarf);
            enemy.update(window);

            dwarf.shoot(level.platforms, window);
            dwarf.checkBounds(level.platforms);
            dwarf.update(window);
            window.draw(dwarf.bullet);

            if (dwarf.cangrapple) {
                dwarf.grapple(grapplePoint, direction);
            }

            if (dwarf.rect.getGlobalBounds().intersects(level.lever.getGlobalBounds())) {
                level.leverPulled = true;
            }

            if (dwarf.grappletopoint) {
                dwarf.setRope(grapplePoint);
                dwarf.drawRope(window);
            }

            std::cout << level.levelOneComplete << " " << level.levelTwoComplete << std::endl;
            window.display();
        }
    } 
    ImGui::SFML::Shutdown();
}