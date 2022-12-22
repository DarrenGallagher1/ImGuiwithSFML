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
bool cangrapple;
bool grappletopoint;
bool anchor = false;
bool shot = false;
bool pause = false;
bool yellow = false;
int blueColour = 0, greenColour = 0, redColour = 0;
float radius = 0.f;
float groundHeight = SCREENHEIGHT - 20.f;
float posx = SCREENWIDTH / 2;
float posy = SCREENHEIGHT - 20.f;
float velx;
float vely;
float direction;
float grappleTime = 0.f;
float accelx;
float accely;
float rectHeight = 20.f;
float gravity = 0.8;

void checkAnchor(Player& knight, Platform &platform, bool &anchor) {
    if (platform.getBounds().intersects(knight.getShape().getGlobalBounds()) && knight.getVelY() >= 0) {
        anchor = true;
    }
    else {
        anchor = false;
    }
}

//grapple physics. need to take a snapshot of the hypotenuse and then pass into method. A seperate method might be needed
void grapple(Platform& grapplePoint, Player& knight, bool &canGrapple, bool &grappletopoint, float direction) {

    knight.distancex = grapplePoint.getPositionX() - knight.getPositionX();
    knight.distancey = grapplePoint.getPositionY() - knight.getPositionY();
    float distance = sqrt((knight.distancex * knight.distancex) + (knight.distancey * knight.distancey));
    knight.inverseDistance = 1.f / distance;

    float normalisedDistanceX = knight.distancex * knight.inverseDistance;
    float normalisedDistanceY = knight.distancey * knight.inverseDistance;
    float dropoff;

    if (knight.getBounds().intersects(grapplePoint.getBounds())) {
        grappletopoint = false;
        dropoff = normalisedDistanceX;
    }

    if (dropoff < 0) {
        dropoff = dropoff * -1;
    }

    if (grappletopoint) {
        knight.setIndirVelX(normalisedDistanceX * 8.f);
        knight.setVelY(normalisedDistanceY * 8.f);
    }
    
    if (grappletopoint == false && canGrapple == true){
        knight.setIndirVelX(8.f * direction * dropoff);
    }

    if (knight.getPositionY() >= knight.getGroundHeight() - 1.f) {
        canGrapple = false;
        knight.setIndirVelX(0.f);
    }

    knight.setPosition((knight.getPositionX() + knight.getVelX()), (knight.getPositionY() + knight.getVelY()));
}

//void shoot(Player &knight, Platform grapplePoint, bool &shot, sf::RenderWindow &window) {
//
//    if (shot) {
//        knight.bullet.setPosition((knight.getPositionX() + knight.getBounds().width), (knight.getPositionY() + (knight.getBounds().height / 2)));
//        knight.bullet.setSize({ 4.f, 4.f });
//        knight.bullet.setFillColor(sf::Color::White);
//
//        knight.bullets.insert(knight.bullets.end(), knight.bullet);
//
//        knight.bulletdistancex = sf::Mouse::getPosition(window).x - (knight.bullet.getPosition().x);
//        knight.bulletdistancey = sf::Mouse::getPosition(window).y - (knight.bullet.getPosition().y);
//
//        shot = false;
//    }
//
//    
//    float distance = sqrt((knight.bulletdistancex * knight.bulletdistancex) + (knight.bulletdistancey * knight.bulletdistancey));
//    knight.bulletInverseDistance = 1.f / distance;
//
//    float normalisedDistanceX = knight.bulletdistancex * knight.bulletInverseDistance;
//    float normalisedDistanceY = knight.bulletdistancey * knight.bulletInverseDistance;
//    
//    for (int i = 0; i < knight.bullets.size(); i++) {
//        knight.bullets[i].move({(normalisedDistanceX * 10.f), (normalisedDistanceY * 10.f)});
//
//        if (knight.bullets[i].getGlobalBounds().intersects(grapplePoint.getBounds())) {
//            knight.bullets[i].setFillColor(sf::Color::Transparent);
//        }
//    }
//}

void shoot(Player& knight, Platform grapplePoint, bool& shot, float xvel, float yvel) {

    if (shot) {
        knight.bullet.setPosition((knight.getPositionX() + knight.getBounds().width), (knight.getPositionY() + (knight.getBounds().height / 2)));
        knight.bullet.setSize({ 4.f, 4.f });
        knight.bullet.setFillColor(sf::Color::White);

        knight.bullets.insert(knight.bullets.end(), knight.bullet);
        knight.bulletsVelX.insert(knight.bulletsVelX.end(), xvel);
        knight.bulletsVelY.insert(knight.bulletsVelY.end(), yvel);

        shot = false;
    }

    for (int i = 0; i < knight.bullets.size(); i++) {
        knight.bullets[i].move(knight.bulletsVelX[i], knight.bulletsVelY[i]);

        if (knight.bullets[i].getGlobalBounds().intersects(grapplePoint.getBounds())) {
            knight.bullets[i].setFillColor(sf::Color::Transparent);
        }
    }
}

void anchorPlayer(Player& knight, Platform& platform) {

    knight.setIndirVelX(0.f);

    if (knight.getOnLedge()) {
        knight.setGroundHeight(platform.getPositionY() - knight.getHeight() + 1.f);
        knight.setIndirVelX(platform.getXVelocity());
    } else {
        knight.setGroundHeight(720.f - knight.getHeight() + 1.f);
        knight.setIndirVelX(0.f);
    }
}

void grow(float &radius, bool allowgrow) {
    if (radius < 200.f) {
        radius++;
    } else {
        allowgrow = false;
    }
}

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
    Player knight(500.f, 600.f, 30.f, 60.f, sf::Color::Red);
    
    Platform ledge(400.f, 550.f, 100.f, 10.f, sf::Color::White);
    Platform ledge2(300.f, 600.f, 100.f, 10.f, sf::Color::White);
    Platform ledge3(700.f, 400.f, 100.f, 10.f, sf::Color::White);
    Platform grapplePoint(540.f, 360.f, 10.f, 10.f, sf::Color::Yellow);

    Platform ledges[3] = { ledge, ledge2, ledge3 };

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

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    shot = true;
                }
            }

            if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
                pause = !pause;
            }

        }

        if (!pause) {

            ImGui::SFML::Update(window, deltaClock.restart());


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                velx = -5.f;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                velx = 5.f;
            }

            window.clear();

            if (cangrapple && grappletopoint) {
                knight.setShapeColour(sf::Color::Green);
            }
            else if (cangrapple && !grappletopoint) {
                knight.setShapeColour(sf::Color::Blue);
            }
            else {
                knight.setShapeColour(sf::Color::Red);
            }

            if (yellow) {
                knight.setShapeColour(sf::Color::Yellow);
            }

            knight.setOnLedge(false);

            ledges[0].movePlatformX(300.f, 600.f);
            //ledge.draw(window);


            knight.jump();
            //ledge.anchorPlayer(knight);
            knight.setVelX();
            knight.movePlayer();

            /*window.draw(platform);*/
            ImGui::SFML::Render(window);

            grapplePoint.draw(window);

            if (knight.getBounds().intersects(ledges[0].getBounds()) && knight.getVelY() > 0) {
                knight.setOnLedge(true);
                anchorPlayer(knight, ledges[0]);
            }
            else if (knight.getBounds().intersects(ledges[1].getBounds()) && knight.getVelY() > 0) {
                knight.setOnLedge(true);
                anchorPlayer(knight, ledges[1]);
            }
            else if (knight.getBounds().intersects(ledges[2].getBounds()) && knight.getVelY() > 0) {
                knight.setOnLedge(true);
                anchorPlayer(knight, ledges[2]);
            }
            else {
                knight.setOnLedge(false);
                knight.setGroundHeight(720.f - knight.getHeight());
            }

            if (knight.getPositionY() >= 720.f - knight.getHeight()) {
                knight.setIndirVelX(0.f);
            }

            ledges[0].draw(window);
            ledges[1].draw(window);
            ledges[2].draw(window);
            knight.draw(window);

            target.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            //window.draw(target);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !cangrapple) {
                cangrapple = true;
                grappletopoint = true;

                if (knight.getPositionX() > grapplePoint.getPositionX()) {
                    direction = -1.f;
                }
                else {
                    direction = 1.f;
                }
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                shoot(knight, grapplePoint, shot, 5.f, -5.f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                shoot(knight, grapplePoint, shot, -5.f, -5.f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                shoot(knight, grapplePoint, shot, 0.f, -5.f);
            }

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                shoot(knight, grapplePoint, shot, 5.f, 0.f);
            }



            for (int i = 0; i < knight.bullets.size(); i++) {
                window.draw(knight.bullets[i]);
            }

            if (cangrapple) {
                grapple(grapplePoint, knight, cangrapple, grappletopoint, direction);
            }

            window.display();
        }

        if (pause) {
            sf::RenderWindow window2(sf::VideoMode(500.f, 500.f), "Menu");

            while (window2.isOpen()) {
                sf::Event event;

                while (window2.pollEvent(event)) {
                    ImGui::SFML::ProcessEvent(window, event);

                    if (event.type == sf::Event::Closed) {
                        window2.close();
                    }

                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            shot = true;
                        }
                    }

                    if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
                        window2.close();
                        pause = !pause;
                    }

                }

                window2.clear();

                target.setPosition(250.f, 250.f);
                target.setFillColor(sf::Color::Cyan);

                sf::Vector2i position = sf::Mouse::getPosition(window2);
                sf::Vector2f tracker = window2.mapPixelToCoords(position);

                if (target.getGlobalBounds().contains(tracker) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    yellow = true;
                }
                window2.draw(target);
                window2.display();
            }
        }
    }
    
    
    ImGui::SFML::Shutdown();
}
