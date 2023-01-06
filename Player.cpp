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

float Player::getGroundHeight() {
	return this->groundHeight;
}

void Player::setColour(sf::Color colour) {
	this->colour = colour;
}

void Player::setShapeColour(sf::Color colour) {
	rect.setFillColor(colour);
}

void Player::setShape() {
	rect.setSize({ width, height });
	rect.setPosition({ posx, posy });
}

void Player::setGroundHeight(float height) {
	groundHeight = height;
}

void Player::setVelX() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !cangrapple) {
		velx = -5.f + indirVelX;
		animation.startX = 400;
		animation.endPoint = 900;
		animation.flipped = false;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !cangrapple) {
		velx = 5.f + indirVelX;
		animation.startX = 400;
		animation.endPoint = 900;
		animation.flipped = true;
	} else {
		animation.startX = 0;
		animation.endPoint = 300;
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
		vely = -15.f;
		lift = false;
		onLedge = false;
		indirVelX = 0.f;
	}

	else if (posy > (this->groundHeight)) {
		posy = this->groundHeight;
		vely = 0;
		lift = true;
		animation.switchTime = 1.0;
	}

	if (posy < (this->groundHeight)) {
		if (vely < 13.f) {
			vely += gravity;
			animation.switchTime = 0.3;
		}
	}
}

void Player::movePlayer() {
	posx += velx;
	posy += vely;
	rect.setPosition({ posx, posy });
	topBound.setPosition({ posx - rect.getGlobalBounds().width / 2 + 1.f, posy - rect.getGlobalBounds().height / 2});
	leftBound.setPosition({ posx - rect.getGlobalBounds().width / 2 - leftBound.getGlobalBounds().width, posy - rect.getGlobalBounds().height / 2 + 10.f});
	rightBound.setPosition({ posx + rect.getGlobalBounds().width / 2, posy - rect.getGlobalBounds().height / 2 + 10.f});
	bottomBound.setPosition({ posx - rect.getGlobalBounds(). width / 2 + 5.f, posy + rect.getGlobalBounds().height / 2 + 1.f});
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(rect);
	window.draw(topBound);
	window.draw(leftBound);
	window.draw(bottomBound);
	window.draw(rightBound);
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

bool Player::getOnLedge() {
	return this->onLedge;
}

void Player::setOnLedge(bool onLedge) {
	this->onLedge = onLedge;
}

void Player::anchor(Platform platform) {
	setIndirVelX(0.f);

		if (getOnLedge()) {
			setGroundHeight(platform.getPositionY() - rect.getGlobalBounds().height / 2 + 1.f);
			setIndirVelX(platform.getXVelocity());
		}
		else {
			setIndirVelX(0.f);
		}
}

//grapple physics. need to take a snapshot of the hypotenuse and then pass into method. A seperate method might be needed
void Player::grapple(Platform& grapplePoint, float direction) {

	distancex = grapplePoint.getPositionX() - posx;
	distancey = grapplePoint.getPositionY() - posy;
	distance = sqrt((distancex * distancex) + (distancey * distancey));
	inverseDistance = 1.f / distance;

	float normalisedDistanceX = distancex * inverseDistance;
	float normalisedDistanceY = distancey * inverseDistance;
	float dropoff;
	float dropoffY;

	if (rect.getGlobalBounds().intersects(grapplePoint.getBounds()) && grappletopoint == true) {
		grappletopoint = false;
		dropoff = normalisedDistanceX;
		setVelY(10.f * normalisedDistanceY);

	}

	if (dropoff < 0) {
		dropoff = dropoff * -1;
	}

	if (grappletopoint) {
		setIndirVelX(normalisedDistanceX * 10.f);
		setVelY(normalisedDistanceY * 10.f);
	}

	if (grappletopoint == false && cangrapple == true) {
		setIndirVelX(10.f * direction * dropoff);
	}

	if (getPositionY() >= getGroundHeight() - 1.f) {
		cangrapple = false;
		setIndirVelX(0.f);
	}

	if (vely > 13.f) {
		gravity = 0.f;
	}

	setPosition((posx + velx), (posy + vely));
}

void Player::shoot(Platform ledges[], int arraysize, sf::RenderWindow& window) {

	if (shot) {
		bullet.setPosition((posx + rect.getGlobalBounds().width / 2), posy);
		bullet.setSize({ 4.f, 4.f });
		bullet.setFillColor(sf::Color::White);

		bulletdistancex = sf::Mouse::getPosition(window).x - (bullet.getPosition().x);
		bulletdistancey = sf::Mouse::getPosition(window).y - (bullet.getPosition().y);

		float distance = sqrt((bulletdistancex * bulletdistancex) + (bulletdistancey * bulletdistancey));
		bulletInverseDistance = 1.f / distance;

		float normalisedDistanceX = bulletdistancex * bulletInverseDistance;
		float normalisedDistanceY = bulletdistancey * bulletInverseDistance;

		bulletsVelX = normalisedDistanceX * 10.f;
		bulletsVelY = normalisedDistanceY * 10.f;

		shot = false;
	}

	bullet.move({ bulletsVelX, bulletsVelY });

	for (int i = 0; i < arraysize; i++) {


		if (bullet.getGlobalBounds().intersects(ledges[i].getBounds())) {
			bullet.setFillColor(sf::Color::Transparent);
			break;
		}

		if (bullet.getPosition().x > 1080.f ||
			bullet.getPosition().x < 0.f ||
			bullet.getPosition().y < 0.f) {
			bullet.setFillColor(sf::Color::Transparent);
			break;
		}
	}
}

void Player::checkBounds(Platform ledges[], int arraysize) {
	for (int i = 0; i < 5; i++) {
		if (bottomBound.getGlobalBounds().intersects(ledges[i].getBounds())) {

			setOnLedge(true);
			anchor(ledges[i]);
			break;

		}
		else {
			setGroundHeight(SCREENHEIGHT);
		}
	}

	for (int i = 0; i < 5; i++) {

		if (rightBound.getGlobalBounds().intersects(ledges[i].getBounds())) {
			if (getVelX() > 0.f) {
				velx = 0.f;
				break;
			}
		}
	}

	for (int i = 0; i < 5; i++) {

		if (leftBound.getGlobalBounds().intersects(ledges[i].getBounds())) {
			if (getVelX() < 0.f) {
				velx = 0.f;
				break;
			}
		}
	}
}

void Player::setTexture() {
	texture.loadFromFile(animation.fileName);
}