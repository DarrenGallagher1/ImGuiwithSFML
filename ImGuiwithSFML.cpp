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

    Platform grapplePoint(340.f, 860.f, 5.f, 5.f);
    Platform grapplePoint2(540.f, 860.f, 5.f, 5.f);

    Level levelOne;
    levelOne.setBackground("assets/lvl1.png");
    Level levelTwo;
    levelTwo.setBackground("assets/lvl2.png");
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
            }

        }

        if (!pause) {

            ImGui::SFML::Update(window, deltaClock.restart());
            levelOne.destroyLevel();
            levelOne.buildLevelOnePlatforms();

            window.clear();
            window.draw(levelOne.background);

            /*ledges[0].movePlatformX(300.f, 600.f);*/

            dwarf.setVelX();

            ImGui::SFML::Render(window);

            grapplePoint.draw(window);
            grapplePoint2.draw(window);

            /*for (int i = 0; i < 5; i++) {
                ledges[i].draw(window);
            }*/

            levelOne.draw(window);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dwarf.cangrapple && dwarf.getPositionY() > grapplePoint.getPositionY()) {

                dwarf.cangrapple = true;
                dwarf.grappletopoint = true;

                /*if (!dwarf.checkGrapplePath(ledges, 5, grapplePoint)) {
                    dwarf.cangrapple = false;
                    dwarf.grappletopoint = false;
                }*/

                if (dwarf.getPositionX() > grapplePoint.getPositionX()) {
                    direction = -1.f;
                    dwarf.animation.flipped = false;
                }
                else {
                    direction = 1.f;
                    dwarf.animation.flipped = true;
                }
                
            }

            dwarf.shoot(levelOne.platforms, window);
            
            dwarf.checkBounds(levelOne.platforms);
            dwarf.update(window);
            window.draw(dwarf.bullet);

            if (dwarf.cangrapple) {
                dwarf.grapple(grapplePoint, direction);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                levelOne.leverPulled = true;
            } else {
                levelOne.leverPulled = false;
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
            levelOne.destroyLevel();
            window.draw(levelTwo.background);

            /*target.setPosition(250.f, 250.f);
            target.setFillColor(sf::Color::Cyan);*/

            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f tracker = window.mapPixelToCoords(position);

            levelOne.buildLevelTwoPlatforms();
            dwarf.setVelX();
            dwarf.checkBounds(levelOne.platforms);
            dwarf.update(window);
            levelOne.draw(window);

            window.display();
        }
    }

    ImGui::SFML::Shutdown();
}