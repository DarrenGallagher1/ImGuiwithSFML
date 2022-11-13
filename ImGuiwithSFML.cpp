// ImGuiwithSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

bool testMenu = false;
bool move = false;

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);


    sf::Texture texture;
    texture.loadFromFile("Santa1.png");
    sf::Sprite img;
    img.setTexture(texture);
    img.setScale(0.15, 0.15);
    
    

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

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

        ImGui::ImageButton(img, 10, sf::Color::White);

        if (ImGui::Button("Look at this pretty button")) {
            shape.setRadius(10.f);
        }
        

        if (ImGui::Button("Test Button")) {
            testMenu = !testMenu;
        }

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

        if (testMenu) {
            shape.setFillColor(sf::Color::Blue);
        }
        else {
            shape.setFillColor(sf::Color::Green);
        }

        if (move) {
            shape.move(0.f, 1.f);
        }

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

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
