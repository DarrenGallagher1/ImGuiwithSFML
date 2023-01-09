// ImGuiwithSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Player.h"
#include "Level.h"
#include <array>

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


    sf::Texture texture;
    texture.loadFromFile("Santa1.png");
    sf::Sprite img;
    img.setTexture(texture);
    img.setScale(0.15, 0.15);

    //represents player


    Platform ledge(400.f, 550.f, 100.f, 400.f);
    Platform ledge2(300.f, 600.f, 100.f, 400.f);
    Platform ledge3(700.f, 550.f, 100.f, 400.f);
    Platform ledge4(0.f, 720.f - 40.f, 1080.f, 40.f);
    Platform ledge5(1000.f, 0.f, 40.f, 720.f);
    Platform grapplePoint(540.f, 360.f, 5.f, 5.f);

    Platform ledges[5] = { ledge, ledge2, ledge3, ledge4, ledge5 };

    Level levelOne;
    Player dwarf(100.f, 842.f, 100.f, 80.f, "dwarves.png");

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

            ledges[0].movePlatformX(300.f, 600.f);

            dwarf.setVelX();

            ImGui::SFML::Render(window);

            grapplePoint.draw(window);

            /*for (int i = 0; i < 5; i++) {
                ledges[i].draw(window);
            }*/

            levelOne.draw(window);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !dwarf.cangrapple && dwarf.getPositionY() > grapplePoint.getPositionY()) {

                dwarf.cangrapple = true;
                dwarf.grappletopoint = true;

                if (!dwarf.checkGrapplePath(ledges, 5, grapplePoint)) {
                    dwarf.cangrapple = false;
                    dwarf.grappletopoint = false;
                }

                if (dwarf.getPositionX() > grapplePoint.getPositionX()) {
                    direction = -1.f;
                    dwarf.animation.flipped = false;
                }
                else {
                    direction = 1.f;
                    dwarf.animation.flipped = true;
                }
                
            }

            dwarf.shoot(ledges, 5, window);
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

            window.display();
        }

        if (pause) {

            window.clear();
            levelOne.destroyLevel();

            /*target.setPosition(250.f, 250.f);
            target.setFillColor(sf::Color::Cyan);*/

            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f tracker = window.mapPixelToCoords(position);

            levelOne.buildLevelTwoPlatforms();
            levelOne.draw(window);

            window.display();
        }
    }

    
    ImGui::SFML::Shutdown();
}