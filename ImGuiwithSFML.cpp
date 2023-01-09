// ImGuiwithSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "Platform.h"
#include "Player.h"
#include <array>

const float SCREENWIDTH = 1080.f;
const float SCREENHEIGHT = 720.f;
bool testMenu = false;
bool move = true;
bool pause = false;
bool yellow = false;
float direction;

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "ImGui + SFML");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);


    sf::Texture texture;
    texture.loadFromFile("Santa1.png");
    sf::Sprite img;
    img.setTexture(texture);
    img.setScale(0.15, 0.15);

    //represents player
    Player dwarf(500.f, 700.f, 100.f, 80.f, "dwarves.png");

    Platform ledge(400.f, 550.f, 100.f, 400.f, sf::Color::White);
    Platform ledge2(300.f, 600.f, 100.f, 400.f, sf::Color::White);
    Platform ledge3(700.f, 550.f, 100.f, 400.f, sf::Color::White);
    Platform ledge4(0.f, 720.f - 40.f, 1080.f, 40.f, sf::Color::White);
    Platform ledge5(1000.f, 0.f, 40.f, 720.f, sf::Color::White);
    Platform grapplePoint(540.f, 360.f, 5.f, 5.f, sf::Color::Yellow);

    Platform ledges[5] = { ledge, ledge2, ledge3, ledge4, ledge5 };

    

    sf::CircleShape target;
    target.setRadius(150.f);
    target.setOrigin(target.getGlobalBounds().width / 2, target.getGlobalBounds().height / 2);
    target.setFillColor(sf::Color::Transparent);

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

            window.clear();

            ledges[0].movePlatformX(300.f, 600.f);

            dwarf.setVelX();

            dwarf.checkBounds(ledges, 5);

            ImGui::SFML::Render(window);

            grapplePoint.draw(window);

            for (int i = 0; i < 5; i++) {
                ledges[i].draw(window);
            }

            target.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

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

            window.draw(dwarf.bullet);

            if (dwarf.cangrapple) {
                dwarf.grapple(grapplePoint, direction);
            }

            dwarf.update(window);

            if (dwarf.grappletopoint) {
                dwarf.setRope(grapplePoint);
                dwarf.drawRope(window);
            }

            window.display();
        }

        if (pause) {

            window.clear();

            target.setPosition(250.f, 250.f);
            target.setFillColor(sf::Color::Cyan);

            sf::Vector2i position = sf::Mouse::getPosition(window);
            sf::Vector2f tracker = window.mapPixelToCoords(position);

            if (target.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                dwarf.animation.coordinates.top = 160.f;
            }

            if (target.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                yellow = false;
            }

            window.draw(target);
            window.display();
        }
    }

    
    ImGui::SFML::Shutdown();
}