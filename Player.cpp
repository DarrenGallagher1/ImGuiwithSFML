#include "Player.h"

void Player::setPosition(float x, float y) {
	this->posx = x;
	this->posy = y;
}

float Player::getPositionX() {
	return posx;
}

float Player::getPositionY() {
	return posy;
}

void Player::setSize(float w, float h) {
	this->width = w;
	this->height = h;
}

float Player::getWidth() {
	return width;
}

float Player::getHeight() {
	return height;
}

void Player::setColour(sf::Color colour) {
	this->colour = colour;
}

void Player::setShape() {
	rect.setSize({ width, height });
	rect.setPosition({ posx, posy });
	rect.setFillColor(colour);
}

void Player::setGroundHeight(float height) {
	groundHeight = height;
}

void Player::setVelX() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velx = -5.f + indirVelX;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velx = 5.f + indirVelX;
	}
	else {
		velx = indirVelX;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		gravity = upGravity;
	}
	else {
		gravity = downGravity;
	}
}

void Player::setGrappleVelocity(float velx, float vely) {
	this->velx = velx;
	this->vely = vely;
}

void Player::jump() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && vely == 0 && lift == true) {
		vely = -20.f;
		lift = false;
	}

	if (posy < (groundHeight)) {
		vely += gravity;
	}
	else if (posy > (groundHeight)) {
		posy = groundHeight;
		vely = 0;
		lift = true;
	}
}

void Player::movePlayer() {
	posx += velx;
	posy += vely;
	rect.setPosition({ posx, posy });
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(rect);
}

sf::FloatRect Player::getBounds() {
	return rect.getGlobalBounds();
}

float Player::getVelY() {
	return vely;
}

sf::RectangleShape Player::getShape() {
	return rect;
}

void Player::setIndirVelX(float vel) {
	indirVelX = vel;
}

void Player::setAnchor(bool anchor) {
	anchored = anchor;
}

bool Player::getAnchor() {
	return this->anchored;
}

void Player::setGrappleX(float velx) {
	this->velx = velx;
}

void Player::setVelY(float vely) {
	this->vely = vely;
}

float Player::getVelX() {
	return velx;
}