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
bool anchor = false;
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
float gravity = 0.5;

void checkAnchor(Player& knight, Platform &platform, bool &anchor) {
    if (platform.getBounds().intersects(knight.getShape().getGlobalBounds()) && knight.getVelY() >= 0) {
        anchor = true;
    }
    else {
        anchor = false;
    }
}

//grapple physics. need to take a snapshot of the hypotenuse and then pass into method. A seperate method might be needed
void grapple(Platform& grapplePoint, Player& knight, bool &canGrapple, float dirction) {

    knight.distancex = grapplePoint.getPositionX() - knight.getPositionX();
    knight.distancey = grapplePoint.getPositionY() - knight.getPositionY();
    float distance = sqrt((knight.distancex * knight.distancex) + (knight.distancey * knight.distancey));
    knight.inverseDistance = 1.f / distance;

    float normalisedDistanceX = knight.distancex * knight.inverseDistance;
    float normalisedDistanceY = knight.distancey * knight.inverseDistance;

    if (knight.getBounds().intersects(grapplePoint.getBounds())) {
        canGrapple = false;
        knight.setIndirVelX(normalisedDistanceX * 10.f + 10.f);
    }

    if (canGrapple) {
        knight.setIndirVelX(normalisedDistanceX * 10.f);
        knight.setVelY(normalisedDistanceY * 10.f);
    }
    
    /*if (!canGrapple && knight.getPositionY() < 600.f){
        knight.setIndirVelX(10.f * direction);
    }*/

    knight.setPosition((knight.getPositionX() + knight.getVelX()), (knight.getPositionY() + knight.getVelY()));
}

void anchorPlayer(Player& knight, Platform& platform, bool anchor) {
    if (anchor) {
        knight.setGroundHeight(posy - knight.getHeight() + 1.f);
        knight.setIndirVelX(velx);
    }
    else {
        knight.setGroundHeight(720.f - knight.getHeight());
        knight.setIndirVelX(0.f);
    }
}


//maybe split the jump function and the attach to ground function so that attach to ground can constantly operate
void jump(float& posy, float& vely, float& accely, float& gravity, bool &move) {

        if (posy < (groundHeight)) {
            vely += gravity;
        }
        else if (posy > (groundHeight)) {
            posy = groundHeight;
            vely = 0;
            move = true;
        }

        vely += accely;
        posy += vely;
}

//standard left/right movement
void movement(float& posx, float& velx) {
    posx += velx;
}

void grow(float &radius, bool allowgrow) {
    if (radius < 100.f) {
        radius++;
    }
    else {
        allowgrow = false;
    }
}

//void platformMoveX(sf::RectangleShape& platform, sf::RectangleShape &rect, float velX, float pointA, float pointB) {
//
//    bool direction;
//
//    if (platform.getPosition().x == pointA) {
//        direction = true;
//    }
//
//    if (platform.getPosition().x == pointB) {
//        direction = false;
//    }
//
//    if (direction) {
//        platform.move(2.f, 0.f);
//    }
//    else if (!direction) {
//        platform.move(-2.f, 0.f);
//    }
//
//    if ((direction) && (platform.getGlobalBounds().intersects(rect.getGlobalBounds()) && vely == 0)) {
//        velx = 2.f;
//    }
//    else if ((!direction) && (platform.getGlobalBounds().intersects(rect.getGlobalBounds()) && vely == 0)) {
//        velx = -2.f;
//    }
//}

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
    Player knight(500.f, 1020.f, 30.f, 60.f, sf::Color::Red);

    ////static platform
    //sf::RectangleShape platform;
    //platform.setSize(sf::Vector2f(100.f, 10.f));
    //platform.setFillColor(sf::Color::White);
    //platform.setPosition(sf::Vector2f(0.f, 600.f));

    
    Platform ledge(300.f, 600.f, 100.f, 10.f, sf::Color::White);
    Platform ledge2(300.f, 600.f, 100.f, 10.f, sf::Color::White);
    Platform grapplePoint(540.f, 360.f, 10.f, 10.f, sf::Color::Yellow);

    Platform ledges[2] = { ledge, ledge2 };

    
    sf::CircleShape shape(100.f);

    sf::Clock deltaClock;


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");

        ImGui::ImageButton(img, 10, sf::Color::Blue);

        if (ImGui::Button("Jump")) {
            vely = -15.f;
        }
        

        if (ImGui::Button("Test Button")) {
            testMenu = !testMenu;
        }

        ImGui::SliderInt("Blue Slider", &blueColour, 0, 255);
        ImGui::SliderInt("Red Slder", &redColour, 0, 255);
        ImGui::SliderInt("Green Slider", &greenColour, 0, 255);
        shape.setFillColor(sf::Color::Color(redColour, greenColour, blueColour, 255));

        ImGui::SliderFloat("Size slider", &radius, 5.f, 255.f);
        shape.setRadius(radius);

        ImGui::SliderFloat("Horizontal Slider", &posx, 0.f, (SCREENWIDTH - radius));
        ImGui::SliderFloat("Vertical Slider", &posy, 0.f, (SCREENHEIGHT - radius));
        shape.setPosition(posx, posy);

        if (testMenu) {
            ImGui::Begin("Test Menu");
            if (ImGui::Button("Appears on test")) {
                move = !move;
            }

            if (ImGui::Button("Close")) {
                window.close();
            }
        }
        else {
            ImGui::End();
        }

        ImGui::End();

        /*if (testMenu) {
            shape.setFillColor(sf::Color::Blue);
        }
        else {
            shape.setFillColor(sf::Color::Green);
        }*/

        if (move) {
            shape.move(0.f, 1.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velx = -5.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velx = 5.f;
        }

        window.clear();

        ledges[0].movePlatformX(300.f, 600.f);
        //ledge.draw(window);

        knight.jump();
        //ledge.anchorPlayer(knight);
        knight.setVelX();
        knight.movePlayer();
        knight.draw(window);
        /*window.draw(platform);*/
        ImGui::SFML::Render(window);
        
        ledges[0].anchorPlayer(knight);
        ledges[0].draw(window);
        grapplePoint.draw(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            cangrapple = true;

            if (knight.getPositionX() > grapplePoint.getPositionX()) {
                direction =  -1.f;
            }
            else {
                direction =  1.f;
            }
        }

        grapple(grapplePoint, knight, cangrapple, direction);
        

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && vely == 0 && move == true) {
            vely = -15.f;
            move = false;
        }

    }

    /*rectB = rect.getGlobalBounds();
    platformB = platform.getGlobalBounds();*/

    ImGui::SFML::Shutdown();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
