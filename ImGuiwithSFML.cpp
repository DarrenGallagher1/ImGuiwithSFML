// ImGuiwithSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Player.h"
#include "Level.h"
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
    Platform grapplePoint2(540.f, 860.f, 5.f, 5.f);

    Level level;
    level.setBackground("assets/lvl1.png");
    Player dwarf(355.f, 800.f, 100.f, 80.f, "dwarves.png");

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

            ImGui::SFML::Update(window, deltaClock.restart());
            level.destroyLevel();
            level.buildLevelOnePlatforms();

            window.clear();
            window.draw(level.background);

            /*ledges[0].movePlatformX(300.f, 600.f);*/

            dwarf.setVelX();

            ImGui::SFML::Render(window);

            /*for (int i = 0; i < 5; i++) {
                ledges[i].draw(window);
            }*/

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
                

                /*if (!dwarf.checkGrapplePath(ledges, 5, grapplePoint)) {
                    dwarf.cangrapple = false;
                    dwarf.grappletopoint = false;
                }*/

                if (dwarf.getPositionX() > grapplePoint.getPosition().x) {
                    direction = -1.f;
                    dwarf.animation.flipped = false;
                }
                else {
                    direction = 1.f;
                    dwarf.animation.flipped = true;
                }
                
            }

            dwarf.shoot(level.platforms, window);
            
            dwarf.checkBounds(level.platforms);
            dwarf.update(window);
            window.draw(dwarf.bullet);

            if (dwarf.cangrapple) {
                dwarf.grapple(grapplePoint, direction);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                level.leverPulled = true;
            } else {
                level.leverPulled = false;
            }

            if (dwarf.grappletopoint) {
                dwarf.setRope(grapplePoint);
                dwarf.drawRope(window);
            }

            std::cout << dwarf.bullet.getPosition().x << " " << dwarf.bullet.getPosition().y << std::endl;
            window.display();
        }

        if (pause) {

            window.clear();
            level.destroyLevel();
            level.buildLevelTwoPlatforms();
            window.draw(level.background);

            /*target.setPosition(250.f, 250.f);
            target.setFillColor(sf::Color::Cyan);*/

            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f tracker = window.mapPixelToCoords(position);

            
            dwarf.setVelX();
            dwarf.checkBounds(level.platforms);
            dwarf.update(window);
            level.draw(window);

            window.display();
        }
    }

    ImGui::SFML::Shutdown();
}