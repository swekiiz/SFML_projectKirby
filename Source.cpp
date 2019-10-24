#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<algorithm>
/*
	rightleft 0 = left
	rightleft 1 = right
	color 0 = pink
	color 1 = orange
	color 2 = blue
	color 3 = green
*/
const double PI = 3.141592653589793;
bool KBP(sf::Keyboard::Key x) {
	return sf::Keyboard::isKeyPressed(x);
}
int absi(int a) {
	return a < 0 ? -a : a;
}
float absf(float a) {
	return a < 0 ? -a : a;
}
int mpow(int a, int b) {
	if (!b) return 1;
	if (b & 1) return mpow(a, b - 1) * a;
	int temp = mpow(a, b >> 1);
	return temp * temp;
}
float mpow(float a, int b) {
	if (!b) return 1;
	if (b & 1) return mpow(a, b - 1) * a;
	float temp = mpow(a, b >> 1);
	return temp * temp;
}
int mrand(int l, int r) {
	srand(time(NULL));
	return (rand() % (r - l + 1)) + l;
}
int stageOfMenu = 0;
bool isSetUp = false;
class Player {
private:
	int jumpCount = 0;
	int jumpCountMax = 1;
	int step = 0;
	int myColor = 0;
	int tickOfTimeOfColor = 1000;
	int tickOfNextOfAnimateTime = 500;
	float mySize = 35.0;
	float mypoX;
	float mypoY;
	float speed = 0;
	float velocity = 3;
	float baseSpeedJump = 4.5;
	float baseSpeedFall = 0.1;
	float acceleration = 0.1;
	bool rightleft = 1;
	bool unstable = 0;
	bool air = false;
	bool stateJump = false;
	bool Fall = false;
	bool stateCover = false;
	bool canChangeColor = false;
	bool reverseX = false;
	bool reverseY = false;
	bool doubleJump = false;
	std::string tempOfColor = "kirby_pink";
	sf::CircleShape myBody;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Clock timeOfUnstable;
	sf::Clock timeOfColor;
	sf::Clock animateTime;
	sf::Clock timeOfJump;
	sf::Clock timeOfCover;
	sf::Clock timeOfDoubleJump;
public:
	Player() {
		this->texture.loadFromFile("images/" + this->tempOfColor + "kirbynormal.png");
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->sprite.setScale(35.0 * 2 / 24.0, 35.0 * 2 / 22.0);
		this->sprite.setOrigin(12.0, 11.0);
		this->sprite.setPosition(700.0, 700.0 - this->mySize);
		this->myBody.setOrigin(this->mySize, this->mySize);
		this->myBody.setPosition(700.0, 700.0 - this->mySize);
		this->myBody.setRadius(this->mySize);
		this->myBody.setFillColor(sf::Color::White);
		this->mypoX = 700.0;
		this->mypoY = 700.0 - this->mySize;
		this->myColor = 0;
		this->acceleration = 0.1;
		this->canChangeColor = false;
		this->timeOfColor.restart();
		this->animateTime.restart();
		this->timeOfJump.restart();
		this->timeOfCover.restart();
		this->timeOfUnstable.restart();
		this->timeOfDoubleJump.restart();
	}
	Player(int a, std::string s, float w, float h) {
		this->mySize = a;
		this->texture.loadFromFile(s);
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->sprite.setScale(a * 2 / w, a * 2 / h);
		this->sprite.setOrigin(w / 2, h / 2);
		this->sprite.setPosition(700.0, 700.0 - a);
		this->myBody.setOrigin(a, a);
		this->myBody.setPosition(700.0, 700.0 - a);
		this->myBody.setRadius(a);
		this->myBody.setFillColor(sf::Color::White);
		this->mypoX = 700.0;
		this->mypoY = 700.0 - a;
		this->myColor = 0;
		this->acceleration = 0.1;
		this->canChangeColor = false;
		this->timeOfColor.restart();
		this->animateTime.restart();
		this->timeOfJump.restart();
		this->timeOfCover.restart();
		this->timeOfUnstable.restart();
		this->timeOfDoubleJump.restart();
	}
	Player(int a, std::string s, float w, float h, int c) {
		this->mySize = a;
		this->texture.loadFromFile(s);
		this->jumpCountMax = c;
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->sprite.setScale(a * 2 / w, a * 2 / h);
		this->sprite.setOrigin(w / 2, h / 2);
		this->sprite.setPosition(700.0, 700.0 - a);
		this->myBody.setOrigin(a, a);
		this->myBody.setPosition(700.0, 700.0 - a);
		this->myBody.setRadius(a);
		this->myBody.setFillColor(sf::Color::White);
		this->mypoX = 700.0;
		this->mypoY = 700.0 - a;
		this->myColor = 0;
		this->acceleration = 0.1;
		this->canChangeColor = false;
		this->timeOfColor.restart();
		this->animateTime.restart();
		this->timeOfJump.restart();
		this->timeOfCover.restart();
		this->timeOfUnstable.restart();
		this->timeOfDoubleJump.restart();
	}
	Player(int a, std::string s, float w, float h, float v, int c) {
		this->mySize = a;
		this->texture.loadFromFile(s);
		this->jumpCountMax = c;
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->sprite.setScale(a * 2 / w, a * 2 / h);
		this->sprite.setOrigin(w / 2, h / 2);
		this->sprite.setPosition(700.0, 700.0 - a);
		this->myBody.setOrigin(a, a);
		this->myBody.setPosition(700.0, 700.0 - a);
		this->myBody.setRadius(a);
		this->myBody.setFillColor(sf::Color::White);
		this->velocity = v;
		this->mypoX = 700.0;
		this->mypoY = 700.0 - a;
		this->myColor = 0;
		this->acceleration = 0.1;
		this->canChangeColor = false;
		this->timeOfColor.restart();
		this->animateTime.restart();
		this->timeOfJump.restart();
		this->timeOfCover.restart();
		this->timeOfUnstable.restart();
		this->timeOfDoubleJump.restart();
	}
	Player(int a, std::string s, float w, float h, float v, int c, int tick) {
		this->mySize = a;
		this->texture.loadFromFile(s);
		this->jumpCountMax = c;
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->sprite.setScale(a * 2 / w, a * 2 / h);
		this->sprite.setOrigin(w / 2, h / 2);
		this->sprite.setPosition(700.0, 700.0 - a);
		this->myBody.setOrigin(a, a);
		this->myBody.setPosition(700.0, 700.0 - a);
		this->myBody.setRadius(a);
		this->myBody.setFillColor(sf::Color::White);
		this->velocity = v;
		this->mypoX = 700.0;
		this->mypoY = 700.0 - a;
		this->myColor = 0;
		this->acceleration = 0.1;
		this->canChangeColor = false;
		this->tickOfTimeOfColor = tick;
		this->timeOfColor.restart();
		this->animateTime.restart();
		this->timeOfJump.restart();
		this->timeOfCover.restart();
		this->timeOfUnstable.restart();
		this->timeOfDoubleJump.restart();
	}
	//  Player player(35.0, "images/kirby_pink/kirbynormal.png", 24.0, 22.0, 3.5, 2, 350);
	sf::CircleShape drawCir();
	sf::Sprite draw();
	void left();
	void right();
	void up();
	void down();
	void jump();
	void cover();
;	float getX();
	float getY();
	float getSize();
	float getSpeed();
	float getAcceleration();
	int getjumpCount();
	int getjumpCountMax();
	int getColor();
	bool getLR();
	bool getUnstable();
	bool isAir();
	bool isJump();
	bool isFall();
	bool isCover();
	bool isCanChangeColor();
	void setJump();
	void setFall();
	void setCover();
	void setOnGround();
	void setSpeed(float);
	void setLR(bool);
	void setUnstable(bool);
	void setBaseSpeedJump(float);
	void setBaseSpeedFall(float);
	void setAcceleration(float);
	void setJumpCountMax(int);
	void setLeftRight(bool);
	void setColor(sf::Color);
	void setPink();
	void setOrange();
	void setBlue();
	void setGreen();
	void setStateCanChangeColor(bool);
	void setTexture(std::string, float, float);
	void setReveserX(bool);
	void setReveserY(bool);
	void wrap(float,float);
	void respawn();
	void increaceSpeed();
	void decreaceSpeed();
	void aniUnstable();
	void aniRight();
	void aniLeft();
	void _debugY();
	void _fall();
	void _jump();
	void _unstable();
	void _cover();
	void _doubleJumpCheck();
	void _ALL_OF_UNSTABLE();
};
sf::CircleShape Player::drawCir() {
	return this->myBody;
}
sf::Sprite Player::draw() {
	return this->sprite;
}
void Player::left() {
	int count = 0;
	if (this->reverseX) {
		this->rightleft = 1;
		while (this->mypoX < 1300 - this->mySize && count < this->velocity) {
			this->mypoX += 1;
			this->myBody.setPosition(this->mypoX, this->mypoY);
			this->sprite.setPosition(this->mypoX, this->mypoY);
			count++;
		}
		if (this->tickOfNextOfAnimateTime < this->animateTime.getElapsedTime().asMilliseconds() && !this->air && !KBP(sf::Keyboard::Key::D)) {
			this->animateTime.restart();
			if (this->stateCover)
				this->tickOfNextOfAnimateTime = 150;
			else
				this->tickOfNextOfAnimateTime = 50;
			this->aniRight();
			this->rightleft = true;
		}
		if (this->air) {
			this->setLR(1);
		}
	}
	else {
		this->rightleft = 0;
		while (this->mypoX > 100 + this->mySize && count < this->velocity) {
			this->mypoX -= 1;
			this->myBody.setPosition(this->mypoX, this->mypoY);
			this->sprite.setPosition(this->mypoX, this->mypoY);
			count++;
		}
		if (this->tickOfNextOfAnimateTime < this->animateTime.getElapsedTime().asMilliseconds() && !this->air && !KBP(sf::Keyboard::Key::D)) {
			this->animateTime.restart();
			if (this->stateCover)
				this->tickOfNextOfAnimateTime = 150;
			else
				this->tickOfNextOfAnimateTime = 50;
			this->aniLeft();
			this->rightleft = false;
		}
		if (this->air) {
			this->setLR(0);
		}
	}
}
void Player::right() {
	int count = 0;
	if (this->reverseX) {
		this->rightleft = 0;
		while (this->mypoX > 100 + this->mySize && count < this->velocity) {
			this->mypoX -= 1;
			this->myBody.setPosition(this->mypoX, this->mypoY);
			this->sprite.setPosition(this->mypoX, this->mypoY);
			count++;
		}
		if (this->tickOfNextOfAnimateTime < this->animateTime.getElapsedTime().asMilliseconds() && !this->air && !KBP(sf::Keyboard::Key::A)) {
			this->animateTime.restart();
			if (this->stateCover)
				this->tickOfNextOfAnimateTime = 150;
			else
				this->tickOfNextOfAnimateTime = 50;
			this->aniLeft();
			this->rightleft = false;
		}
		if (this->air) {
			this->setLR(0);
		}
	}
	else {
		this->rightleft = 1;
		while (this->mypoX < 1300 - this->mySize && count < this->velocity) {
			this->mypoX += 1;
			this->myBody.setPosition(this->mypoX, this->mypoY);
			this->sprite.setPosition(this->mypoX, this->mypoY);
			count++;
		}
		if (this->tickOfNextOfAnimateTime < this->animateTime.getElapsedTime().asMilliseconds() && !this->air && !KBP(sf::Keyboard::Key::A)) {
			this->animateTime.restart();
			if (this->stateCover)
				this->tickOfNextOfAnimateTime = 150;
			else
				this->tickOfNextOfAnimateTime = 50;
			this->aniRight();
			this->rightleft = true;
		}
		if (this->air) {
			this->setLR(1);
		}
	}
}
void Player::up() {
	this->mypoY -= this->speed;
	this->myBody.setPosition(this->mypoX, this->mypoY);
	this->sprite.setPosition(this->mypoX, this->mypoY);
}
void Player::down() {
	this->mypoY += this->speed;
	this->myBody.setPosition(this->mypoX, this->mypoY);
	this->sprite.setPosition(this->mypoX, this->mypoY);
}
void Player::jump() {
	if (this->mypoY > 50 + this->mySize && this->timeOfJump.getElapsedTime().asMilliseconds() > 100 && !this->stateCover) {
		this->timeOfJump.restart();
		if (!this->air) {
			this->setBaseSpeedJump(5.0);
			this->setJump();
		}
		else if (this->getjumpCountMax() > this->getjumpCount()) {
			if (this->stateJump) {
				if (this->rightleft)
					this->setTexture("images/" + this->tempOfColor + "/kirbydjump.png", 21.0, 29.0);
				else
					this->setTexture("images/" + this->tempOfColor + "/kirbydjump_left.png", 21.0, 29.0);
				this->doubleJump = true;
				this->timeOfDoubleJump.restart();
			}
			this->setBaseSpeedJump(4.5);
			this->setJump();
		}
	}
}
void Player::cover() {
	if (!this->isCover()) {
		if (this->air) {
			this->setAcceleration(0.275);
			if (this->isJump()) {
				this->setBaseSpeedFall(1.0);
				this->setFall();
				this->setBaseSpeedFall(0.1);
			}
		}
		else if (!this->isCover()) {
			this->setCover();
		}
	}
}
float Player::getX() {
	return this->mypoX;
}
float Player::getY() {
	return this->mypoY;
}
float Player::getSize() {
	return this->mySize;
}
float Player::getSpeed() {
	return this->speed;
}
float Player::getAcceleration() {
	return this->acceleration;
}
int Player::getjumpCount() {
	return this->jumpCount;
}
int Player::getjumpCountMax() {
	return this->jumpCountMax;
}
int Player::getColor() {
	return this->myColor;
}
bool Player::getLR() {
	return this->rightleft;
}
bool Player::getUnstable() {
	return this->unstable;
}
bool Player::isAir() {
	return this->air;
}
bool Player::isJump() {
	return this->stateJump;
}
bool Player::isFall() {
	return this->Fall;
}
bool Player::isCover() {
	return this->stateCover;
}
bool Player::isCanChangeColor() {
	return this->canChangeColor;
}
void Player::setJump() {
	this->air = true;
	this->stateJump = true;
	this->Fall = false;
	this->speed = this->baseSpeedJump;
	(this->jumpCount)++;
	this->setLR(this->rightleft);
}
void Player::setFall() {
	this->stateJump = false;
	this->Fall = true;
	this->speed = this->baseSpeedFall;
	this->setLR(this->rightleft);
}
void Player::setCover() {
	this->stateCover = true;
	this->mypoY = this->mypoY + this->mySize;
	this->myBody.setPosition(sf::Vector2f(this->mypoX, this->mypoY));
	if (this->rightleft)
		this->setTexture("images/" + this->tempOfColor + "/kirbycover.png", 32.0, 35.0);
	else
		this->setTexture("images/" + this->tempOfColor + "/kirbycover_left.png", 32.0, 35.0);
}
void Player::setOnGround() {
	this->air = false;
	this->stateJump = false;
	this->Fall = false;
	this->speed = 0;
	this->jumpCount = 0;
	this->setAcceleration(0.1);
	if (this->stateCover) {
		this->stateCover = false;
		this->mypoY = this->mypoY - this->mySize;
		this->myBody.setPosition(sf::Vector2f(this->mypoX, this->mypoY));
		if (this->rightleft)
			this->setTexture("images/" + this->tempOfColor + "/kirbynormal.png", 24.0, 22.0);
		else
			this->setTexture("images/" + this->tempOfColor + "/kirbynormal_left.png", 24.0, 22.0);
	}
	this->setLR(this->rightleft);
}
void Player::setSpeed(float a) {
	this->speed = a;
}
void Player::setLR(bool a) {
	if (!this->doubleJump) {
		this->rightleft = a;
		if (this->rightleft && this->isCover())
			this->setTexture("images/" + this->tempOfColor + "/kirbycover.png", 32.0, 35.0);
		else if (!this->rightleft && this->isCover())
			this->setTexture("images/" + this->tempOfColor + "/kirbycover_left.png", 32.0, 35.0);
		else if (this->rightleft && this->isAir() && this->isJump())
			this->setTexture("images/" + this->tempOfColor + "/kirbyjump.png", 21.0, 29.0);
		else if (!this->rightleft && this->isAir() && this->isJump())
			this->setTexture("images/" + this->tempOfColor + "/kirbyjump_left.png", 21.0, 29.0);
		else if (this->rightleft && this->isAir() && this->isFall())
			this->setTexture("images/" + this->tempOfColor + "/kirbyfall.png", 21.0, 24.0);
		else if (!this->rightleft && this->isAir() && this->isFall())
			this->setTexture("images/" + this->tempOfColor + "/kirbyfall_left.png", 21.0, 24.0);
		else if (this->rightleft)
			this->setTexture("images/" + this->tempOfColor + "/kirbynormal.png", 24.0, 22.0);
		else
			this->setTexture("images/" + this->tempOfColor + "/kirbynormal_left.png", 24.0, 22.0);
	}
}
void Player::setUnstable(bool a) {
	this->unstable = a;
}
void Player::setBaseSpeedJump(float a) {
	this->baseSpeedJump = a;
}
void Player::setBaseSpeedFall(float a) {
	this->baseSpeedFall = a;
}
void Player::setAcceleration(float a) {
	this->acceleration = a;
}
void Player::setJumpCountMax(int a) {
	this->jumpCountMax = a;
}
void Player::setLeftRight(bool a) {
	this->rightleft = a;
}
void Player::setColor(sf::Color a) {
	this->myBody.setFillColor(a);
	this->myColor = 0;
	this->tempOfColor = "kirby_pink";
}
void Player::setPink() {
	if (this->myColor != 0 && this->tickOfTimeOfColor < this->timeOfColor.getElapsedTime().asMilliseconds() && this->canChangeColor) {
		this->timeOfColor.restart();
		this->myBody.setFillColor(sf::Color(255, 192, 204));
		this->myColor = 0;
		this->tempOfColor = "kirby_pink";
	}
}
void Player::setOrange() {
	if (this->myColor != 1 && this->tickOfTimeOfColor < this->timeOfColor.getElapsedTime().asMilliseconds() && this->canChangeColor) {
		this->timeOfColor.restart();
		this->myBody.setFillColor(sf::Color(255, 142, 5));
		this->myColor = 1;
		this->tempOfColor = "kirby_orange";
	}
}
void Player::setBlue() {
	if (this->myColor != 2 && this->tickOfTimeOfColor < this->timeOfColor.getElapsedTime().asMilliseconds() && this->canChangeColor) {
		this->timeOfColor.restart();
		this->myBody.setFillColor(sf::Color(30, 30, 255));
		this->myColor = 2;
		this->tempOfColor = "kirby_blue";
	}
}
void Player::setGreen() {
	if (this->myColor != 3 && this->tickOfTimeOfColor < this->timeOfColor.getElapsedTime().asMilliseconds() && this->canChangeColor) {
		this->timeOfColor.restart();
		this->myBody.setFillColor(sf::Color(120, 246, 2));
		this->myColor = 3;
		this->tempOfColor = "kirby_green";
	}
}
void Player::setStateCanChangeColor(bool a) {
	this->canChangeColor = a;
}
void Player::setTexture(std::string s, float w, float h) {
	this->texture.loadFromFile(s);
	sf::Sprite temp(this->texture);
	this->sprite = temp;
	this->sprite.setScale(this->mySize * 2 / w, this->mySize * 2 / h);
	this->sprite.setOrigin(w / 2, h / 2);
	this->sprite.setPosition(this->mypoX, this->mypoY);
}
void Player::respawn() { 
	this->mypoX = 700.0;
	this->mypoY = 700.0 - this->mySize;
	this->air = false;
	this->stateJump = false;
	this->Fall = false;
	this->stateCover = false;
	this->speed = 0;
	this->jumpCount = 0;
	this->rightleft = 1;
	this->myBody.setPosition(this->mypoX, this->mypoY);
	this->sprite.setPosition(this->mypoX, this->mypoY);
	this->setAcceleration(0.1);
	this->setTexture("images/" + this->tempOfColor + "/kirbynormal.png", 24.0, 22.0);
}
void Player::setReveserX(bool a) {
	this->reverseX = a;
}
void Player::setReveserY(bool a) {
	this->reverseY = a;
}
void Player::wrap(float a, float b) {
	if (a > 100 && a < 1300 - this->mySize && b > 50 +this->mySize && b < 700 - this->mySize) {
		this->mypoX = a;
		this->mypoY = b;
		this->air = true;
		this->stateCover = false;
		this->jumpCount = 0;
		this->myBody.setPosition(this->mypoX, this->mypoY);
		this->sprite.setPosition(this->mypoX, this->mypoY);
		this->acceleration = 0.1;
		this->setFall();
	}
}
void Player::increaceSpeed() {
	this->speed = this->speed + this->acceleration;
}
void Player::decreaceSpeed() {
	this->speed = this->speed - this->acceleration;
}
void Player::aniUnstable() {
	if (!this->air && !this->stateCover) {
		if (this->unstable) {
			if (this->rightleft)
				this->setTexture("images/" + this->tempOfColor + "/kirbynormal_unstable.png", 28.0, 22.0);
			else
				this->setTexture("images/" + this->tempOfColor + "/kirbynormal_unstable_left.png", 28.0, 22.0);
			this->unstable = false;
		}
		else {
			if (this->rightleft)
				this->setTexture("images/" + this->tempOfColor + "/kirbynormal.png", 24.0, 22.0);
			else
				this->setTexture("images/" + this->tempOfColor + "/kirbynormal_left.png", 24.0, 22.0);
			this->unstable = true;
		}
	}
}
void Player::aniLeft() {
	if (this->stateCover) {
		if ((this->step & 1) == 1) {
			this->setTexture("images/" + this->tempOfColor + "/kirbycover_left.png", 32.0, 35.0);
		}
		else {
			this->setTexture("images/" + this->tempOfColor + "/kirbycover_walk_left.png", 29.0, 35.0);
		}
	}
	else {
		switch (this->step) {
		case 0: this->setTexture("images/" + this->tempOfColor + "/L01.png", 26.0, 23.0); break;
		case 1: this->setTexture("images/" + this->tempOfColor + "/L02.png", 24.0, 22.0); break;
		case 2: this->setTexture("images/" + this->tempOfColor + "/L03.png", 23.0, 20.0); break;
		case 3: this->setTexture("images/" + this->tempOfColor + "/L04.png", 23.0, 21.0); break;
		case 4: this->setTexture("images/" + this->tempOfColor + "/L05.png", 24.0, 22.0); break;
		case 5: this->setTexture("images/" + this->tempOfColor + "/L06.png", 26.0, 23.0); break;
		case 6: this->setTexture("images/" + this->tempOfColor + "/L07.png", 24.0, 22.0); break;
		case 7: this->setTexture("images/" + this->tempOfColor + "/L08.png", 23.0, 20.0); break;
		case 8: this->setTexture("images/" + this->tempOfColor + "/L09.png", 21.0, 21.0); break;
		case 9: this->setTexture("images/" + this->tempOfColor + "/L10.png", 22.0, 22.0); break;
		}
	}
	this->step++;
	if (this->step >= 10)
		this->step = 0;
}
void Player::aniRight() {
	if (this->stateCover) {
		if ((this->step & 1) == 1) {
			this->setTexture("images/" + this->tempOfColor + "/kirbycover.png", 32.0, 35.0);
		}
		else {
			this->setTexture("images/" + this->tempOfColor + "/kirbycover_walk.png", 29.0, 35.0);
		}
	}
	else {
		switch (this->step) {
		case 0: this->setTexture("images/" + this->tempOfColor + "/01.png", 26.0, 23.0); break;
		case 1: this->setTexture("images/" + this->tempOfColor + "/02.png", 24.0, 22.0); break;
		case 2: this->setTexture("images/" + this->tempOfColor + "/03.png", 23.0, 20.0); break;
		case 3: this->setTexture("images/" + this->tempOfColor + "/04.png", 23.0, 21.0); break;
		case 4: this->setTexture("images/" + this->tempOfColor + "/05.png", 24.0, 22.0); break;
		case 5: this->setTexture("images/" + this->tempOfColor + "/06.png", 26.0, 23.0); break;
		case 6: this->setTexture("images/" + this->tempOfColor + "/07.png", 24.0, 22.0); break;
		case 7: this->setTexture("images/" + this->tempOfColor + "/08.png", 23.0, 20.0); break;
		case 8: this->setTexture("images/" + this->tempOfColor + "/09.png", 21.0, 21.0); break;
		case 9: this->setTexture("images/" + this->tempOfColor + "/10.png", 22.0, 22.0); break;
		}
	}
	this->step++;
	if (this->step >= 10)
		this->step = 0;
}
void Player::_debugY() {
	if (this->mypoY > 700 - this->mySize && !this->stateCover) {
		this->myBody.setPosition(this->mypoX, 699.99 - this->mySize);
		this->sprite.setPosition(this->mypoX, 699.99 - this->mySize);
	}
	else if (this->mypoY > 700 && this->stateCover) {
		this->myBody.setPosition(this->mypoX, 699.99);
		this->sprite.setPosition(this->mypoX, 699.99);
	}
}
void Player::_fall() {
	if (this->Fall) {
		if (this->mypoY < 700 - this->mySize) {
			this->down();
			this->increaceSpeed();
		}
		else {
			this->setOnGround();
			this->_debugY();
		}
	}
}
void Player::_jump() {
	if (this->stateJump) {
		if (this->speed < 0) {
			this->setFall();
			this->setAcceleration(0.1);
		}
		if (this->mypoY > 50 + this->mySize) {
			this->up();
		}
		else {
			this->setSpeed(0);
		}
		this->decreaceSpeed();
	}
}
void Player::_unstable() {
	if (300 < this->timeOfUnstable.getElapsedTime().asMilliseconds() && !KBP(sf::Keyboard::Key::A) && !KBP(sf::Keyboard::Key::D)) {
		this->timeOfUnstable.restart();
		this->aniUnstable();
	}
}
void Player::_cover() {
	if (10 < this->timeOfCover.getElapsedTime().asMilliseconds() && !this->air && this->stateCover) {
		this->timeOfCover.restart();
		if (!KBP(sf::Keyboard::Key::S)) {
			this->setOnGround();
		}
	}
}
void Player::_doubleJumpCheck() {
	if (this->doubleJump) {
		if (this->timeOfDoubleJump.getElapsedTime().asMilliseconds() > 100) {
			this->timeOfDoubleJump.restart();
			this->doubleJump = false;
			this->setLR(this->rightleft);
		}
	}
}
void Player::_ALL_OF_UNSTABLE() {
	this->_jump();
	this->_fall();
	this->_debugY();
	this->_unstable();
	this->_cover();
	this->_doubleJumpCheck();
}
class Bullet {
private:
	int color = -1;
	float mySize = 10.0;
	float startX;
	float startY;
	float mypoX;
	float mypoY;
	float speedX = 0.1;
	float speedY = 0.1;
	float angel = 315.0;
	bool bulletStep = 0;
	sf::CircleShape myBody;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock timeOfAnimate;
	std::string tempOfColor = "original";
public:
	Bullet() {
		this->startX = 100.0;
		this->startY = 50.0;
		this->mypoX = 100.0;
		this->mypoY = 50.0;
		this->myBody.setOrigin(this->mySize, this->mySize);
		this->myBody.setPosition(this->startX, this->startY);
		this->myBody.setRadius(this->mySize);
		this->myBody.setFillColor(sf::Color::White);
		this->timeOfAnimate.restart();
	}
	Bullet(float stx, float sty, float size, float ang, float speed, int clr) {
		this->startX = stx;
		this->startY = sty;
		this->mypoX = stx;
		this->mypoY = sty;
		this->mySize = size;
		this->color = clr;
		while (ang < 0) {
			ang += 360.0;
		}
		while (ang > 360) {
			ang -= 360.0;
		}
		this->angel = ang;
		bool check_speed_set = false;
		if ((int)ceil(ang) == (int)floor(ang)) {
			if ((int)ang == 0 || (int)ang == 360) {
				this->speedX = speed;
				this->speedY = 0;
				check_speed_set = true;
			}
			else if ((int)ang == 90) {
				this->speedX = 0;
				this->speedY = -speed;
				check_speed_set = true;
			}
			else if ((int)ang == 180) {
				this->speedX = -speed;
				this->speedY = 0;
				check_speed_set = true;
			}
			else if ((int)ang == 270) {
				this->speedX = 0;
				this->speedY = speed;
				check_speed_set = true;
			}
		}
		if (!check_speed_set) {
			if (ang < 90.0) {
				this->speedX = cos(ang / 180.0 * PI) * speed;
				this->speedY = -1.0 * sin(ang / 180.0 * PI) * speed;
			}
			else if (ang < 180.0) {
				this->speedX = -1.0 * sin((ang - 90.0) / 180.0 * PI) * speed;
				this->speedY = -1.0 * cos((ang - 90.0) / 180.0 * PI) * speed;
			}
			else if (ang < 270.0) {
				this->speedX = -1.0 * cos((ang - 180.0) / 180.0 * PI) * speed;
				this->speedY = sin((ang - 180.0) / 180.0 * PI) * speed;
			}
			else {
				this->speedX = sin((ang - 270.0) / 180.0 * PI) * speed;
				this->speedY = cos((ang - 270.0) / 180.0 * PI) * speed;
			}
		}
		if (clr == -1) {
			this->myBody.setFillColor(sf::Color::White);
			this->tempOfColor = "original";
		}
		else if (clr == 0) {
			this->myBody.setFillColor(sf::Color(255, 192, 204));
			this->tempOfColor = "pink";
		}
		else if (clr == 1) {
			this->myBody.setFillColor(sf::Color(255, 142, 5));
			this->tempOfColor = "orange";
		}
		else if (clr == 2) {
			this->myBody.setFillColor(sf::Color(30, 30, 255));
			this->tempOfColor = "blue";
		}
		else if (clr == 3) {
			this->myBody.setFillColor(sf::Color(120, 246, 2));
			this->tempOfColor = "green";
		}
		this->myBody.setOrigin(this->mySize, this->mySize);
		this->myBody.setPosition(this->startX, this->startY);
		this->myBody.setRadius(this->mySize);
		this->texture.loadFromFile("images/bullet/" + this->tempOfColor + "/bullet.png");
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->sprite.setScale(this->mySize * 4.4 / 112, this->mySize * 2.4 / 45);
		this->sprite.setOrigin(112.0 / 2.0, 45.0 / 2.0);
		this->sprite.setPosition(this->startX, this->startY);
		this->sprite.setRotation(360 - ang);
		this->timeOfAnimate.restart();
	}
	void move();
	void setSpeed(float);
	void animate();
	float getX();
	float getY();
	float getSize();
	int getColor();
	sf::CircleShape drawCir();
	sf::Sprite draw();
};
void Bullet::move() {
	this->mypoX = this->mypoX + this->speedX;
	this->mypoY = this->mypoY + this->speedY;
	this->myBody.setPosition(this->mypoX, this->mypoY);
	this->sprite.setPosition(this->mypoX, this->mypoY);
}
void Bullet::animate() {
	if (175 < this->timeOfAnimate.getElapsedTime().asMilliseconds()) {
		this->timeOfAnimate.restart();
		if (this->bulletStep) {
			this->bulletStep = false;
			this->texture.loadFromFile("images/bullet/" + this->tempOfColor + "/bullet.png");
			sf::Sprite temp(this->texture);
			this->sprite = temp;
			this->sprite.setScale(this->mySize * 4.4 / 112, this->mySize * 2.4 / 45);
			this->sprite.setOrigin(112.0 / 2.0, 45.0 / 2.0);
			this->sprite.setPosition(this->mypoX, this->mypoY);
			this->sprite.setRotation(360 - this->angel);
		}
		else {
			this->bulletStep = true;
			this->texture.loadFromFile("images/bullet/" + this->tempOfColor + "/bullet_unstable.png");
			sf::Sprite temp(this->texture);
			this->sprite = temp;
			this->sprite.setScale(this->mySize * 4.4 / 102, this->mySize * 2.4 / 41);
			this->sprite.setOrigin(102.0 / 2.0, 41.0 / 2.0);
			this->sprite.setPosition(this->mypoX, this->mypoY);
			this->sprite.setRotation(360 - this->angel);
		}
	}
}
void Bullet::setSpeed(float a) {
	if (this->angel < 90.0) {
		this->speedX = cos(this->angel / 180.0 * PI) * a;
		this->speedY = -1.0 * sin(this->angel / 180.0 * PI) * a;
	}
	else if (this->angel < 180.0) {
		this->speedX = -1.0 * sin((this->angel - 90.0) / 180.0 * PI) * a;
		this->speedY = -1.0 * cos((this->angel - 90.0) / 180.0 * PI) * a;
	}
	else if (this->angel < 270.0) {
		this->speedX = -1.0 * cos((this->angel - 180.0) / 180.0 * PI) * a;
		this->speedY = sin((this->angel - 180.0) / 180.0 * PI) * a;
	}
	else {
		this->speedX = sin((this->angel - 270.0) / 180.0 * PI) * a;
		this->speedY = cos((this->angel - 270.0) / 180.0 * PI) * a;
	}
}
float Bullet::getX() {
	return this->mypoX;
}
float Bullet::getY() {
	return this->mypoY;
}
float Bullet::getSize() {
	return this->mySize;
}
int Bullet::getColor() {
	return this->color;
}
sf::CircleShape Bullet::drawCir() {
	return this->myBody;
}
sf::Sprite Bullet::draw() {
	return this->sprite;
}
struct NodeBullet {
	Bullet bullet;
	NodeBullet* next = NULL;
};
class LinkListOfBullet {
private:
	int mySize;
	NodeBullet* head;
	NodeBullet* tail;
public:
	LinkListOfBullet() {
		this->mySize = 0;
		this->head = NULL;
		this->tail = NULL;
	}
	~LinkListOfBullet() {
		delete this->head;
		delete this->tail;
	}
	void append(Bullet);
	void append(float, float, float, float, float, int);
	void move();
	void draw(sf::RenderWindow*);
	bool clashCheck(Player);
	int size();
};
void LinkListOfBullet::append(Bullet bullet) {
	if (this->mySize == 0) {
		NodeBullet* temp = new NodeBullet;
		temp->bullet = bullet;
		temp->next = NULL;
		this->head = temp;
		this->tail = temp;
		this->mySize = this->mySize + 1;
	}
	else {
		NodeBullet* temp = new NodeBullet;
		temp->bullet = bullet;
		temp->next = NULL;
		this->tail->next = temp;
		this->tail = temp;
		this->mySize = this->mySize + 1;
	}
}
void LinkListOfBullet::append(float stx, float sty, float size, float ang, float speed, int clr) {
	//like  ==>   listBullet.append(400, 50, 15.0, 264.5, 5.5, -1);
	Bullet* b = new Bullet(stx, sty, size, ang, speed, clr);
	if (this->mySize == 0) {
		NodeBullet* temp = new NodeBullet;
		temp->bullet = *b;
		temp->next = NULL;
		this->head = temp;
		this->tail = temp;
		this->mySize = this->mySize + 1;
	}
	else {
		NodeBullet* temp = new NodeBullet;
		temp->bullet = *b;
		temp->next = NULL;
		this->tail->next = temp;
		this->tail = temp;
		this->mySize = this->mySize + 1;
	}
}
void LinkListOfBullet::move() {
	if (this->mySize > 0) {
		NodeBullet* cur = this->head;
		NodeBullet* pre = this->head;
		while (cur == this->head && cur != NULL) {
			cur->bullet.move();
			cur->bullet.animate();
			if (cur->bullet.getX() > 1300 || cur->bullet.getX() < 100 || cur->bullet.getY() < 50 || cur->bullet.getY() > 700) {
				if (this->mySize == 1) {
					this->head = NULL;
					this->tail = NULL;
				}
				else {
					this->head = cur->next;
					cur = this->head;
				}
				this->mySize = this->mySize - 1;
			}
			else {
				pre = cur;
				cur = cur->next;
			}
		}
		while (cur != NULL && this->mySize > 0) {
			cur->bullet.move();
			cur->bullet.animate();
			if (cur->bullet.getX() > 1300 || cur->bullet.getX() < 100 || cur->bullet.getY() < 50 || cur->bullet.getY() > 700) {
				if (this->mySize == 1) {
					this->head = NULL;
					this->tail = NULL;
				}
				else {
					pre->next = cur->next;
					if (cur == this->tail)
						this->tail = pre;
				}
				this->mySize = this->mySize - 1;
			}
			else
				pre = cur;
			cur = cur->next;
		}
	}
}

void LinkListOfBullet::draw(sf::RenderWindow* a) {
	if (this->mySize > 0) {
		NodeBullet* cur;
		cur = this->head;
		while (cur != NULL) {
			a->draw(cur->bullet.draw());
			//a->draw(cur->bullet.drawCir());
			cur = cur->next;
		}
	}
}
bool LinkListOfBullet::clashCheck(Player a) {
	if (this->mySize > 0) {
		float p,q;
		NodeBullet* cur = this->head;
		NodeBullet* pre = this->head;
		while (cur != NULL) {
			p = cur->bullet.getX() - a.getX();
			q = cur->bullet.getY() - a.getY();
			if (cur->bullet.getSize() + a.getSize() > sqrt(p * p + q * q) && cur->bullet.getColor() != a.getColor()) {
				if (this->mySize == 1) {
					this->head = NULL;
					this->tail = NULL;
				}
				else if (cur == this->head) {
					this->head = cur->next;
				}
				else {
					pre->next = cur->next;
					if (cur == this->tail)
						this->tail = pre;
				}
				this->mySize = this->mySize - 1;
				return true;
			}
			pre = cur;
			cur = cur->next;
		}
	}
	return false;
}
int LinkListOfBullet::size() {
	return this->mySize;
}
class Laser {
private:
	float mySize = 25.0;
	float myLong = 1200.0;
	float angel = 0;
	float mypoX = 700;
	float mypoY = 375;
	float pointX1 = 100;
	float pointY1 = 375;
	float pointX2 = 1300;
	float pointY2 = 375;
	float speedX = 0;
	float speedY = 0;
	float accelerationX = 0;
	float accelerationY = 0;
	sf::RectangleShape myBody;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Laser () {
		this->myBody.setFillColor(sf::Color::Red);
		this->texture.loadFromFile("images/laser/laser2.png");
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->update();
	}
	Laser(float a,float b,float size,float ang) {
		this->mypoX = a;
		this->mypoY = b;
		this->angel = ang;
		this->mySize = size;
		this->myBody.setFillColor(sf::Color::Red);
		this->texture.loadFromFile("images/laser/laser2.png");
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->update();
		this->sprite.rotate(360.0 - this->angel);
	}
	Laser(float a, float b, float size, float ang,float spX,float spY) {
		this->mypoX = a;
		this->mypoY = b;
		this->angel = ang;
		this->mySize = size;
		this->speedX = spX;
		this->speedY = spY;
		this->myBody.setFillColor(sf::Color::Red);
		this->texture.loadFromFile("images/laser/laser2.png");
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->update();
		this->sprite.rotate(360.0 - this->angel);
	}
	Laser(float a, float b, float size, float ang, float spX, float spY, float acX, float acY) {
		this->mypoX = a;
		this->mypoY = b;
		this->angel = ang;
		this->mySize = size;
		this->speedX = spX;
		this->speedY = spY;
		this->accelerationX = acX;
		this->accelerationY = acY;
		this->myBody.setFillColor(sf::Color::Red);
		this->texture.loadFromFile("images/laser/laser2.png");
		sf::Sprite temp(this->texture);
		this->sprite = temp;
		this->update();
		this->sprite.rotate(360.0 - this->angel);
	}
	void setSpeedXY(float, float);
	void setaccelerationXY(float, float);
	void move();
	void update();
	float getX();
	float getY();
	sf::RectangleShape drawRec();
	sf::Sprite draw();
};
void Laser::setSpeedXY(float a, float b) {
	this->speedX = a;
	this->speedY = b;
}
void Laser::setaccelerationXY(float a, float b) {
	this->accelerationX = a;
	this->accelerationX = b;
}
void Laser::move() {
	this->mypoX = this->mypoX + this->speedX;
	this->mypoY = this->mypoY + this->speedY;
	this->speedX = this->speedX + this->accelerationX;
	this->speedY = this->speedY + this->accelerationY;
	this->update();
}
void Laser::update() {
	float tx1, tx2, ty1, ty2, ang90, D, X, Y, a, b, ang;
	bool check_point_set = false;
	a = this->mypoX, b = 750 - this->mypoY;
	ang = this->angel;
	while (ang < 0)
		ang += 360.0;
	while (ang > 360) 
		ang -= 360.0;
	if (ang > 90 && ang < 180) {
		ang90 = 180 - ang;
	}
	else if (ang > 180 && ang < 270) {
		ang90 = ang - 180;
	}
	else if (ang > 270 && ang < 360) {
		ang90 = 360 - ang;
	}
	else {
		ang90 = ang;
	}
	if ((int)ceil(ang) == (int)floor(ang)) {
		if ((int)ang == 0 || (int)ang == 180 || (int)ang == 360) {
			this->pointX1 = 100;
			this->pointY1 = 750 - b;
			this->pointX2 = 1300;
			this->pointY2 = 750 - b;
			check_point_set = true;
		}
		else if ((int)ang == 90 || (int)ang == 270) {
			this->pointX1 = a;
			this->pointY1 = 700;
			this->pointX2 = a;
			this->pointY2 = 50;
			check_point_set = true;
		}
	}
	if (!check_point_set) {
		tx1 = (50.0 - b) / tan(ang / 180.0 * PI) + a;
		ty1 = 700.0;
		tx2 = (700.0 - b) / tan(ang / 180.0 * PI) + a;
		ty2 = 50.0;
		if (tx1 > 100 && tx1 < 1300 && tx2 >100 && tx2 < 1300) {
			this->pointX1 = tx1;
			this->pointY1 = ty1;
			this->pointX2 = tx2;
			this->pointY2 = ty2;
		}
		else if (tx2 > 100 && tx2 < 1300 && tx1 < 100) {
			this->pointX1 = 100;
			this->pointY1 = 750 - (tan(ang / 180.0 * PI) * (100.0 - a) + b);
			this->pointX2 = tx2;
			this->pointY2 = ty2;
		}
		else if (tx2 > 100 && tx2 < 1300 && tx1 > 1300) {
			this->pointX1 = 1300;
			this->pointY1 = 750 - (tan(ang / 180.0 * PI) * (1300.0 - a) + b);
			this->pointX2 = tx2;
			this->pointY2 = ty2;
		}
		else if (tx1 > 100 && tx1 < 1300 && tx2 > 1300) {
			this->pointX1 = tx1;
			this->pointY1 = ty1;
			this->pointX2 = 1300;
			this->pointY2 = 750 - (tan(ang / 180.0 * PI) * (1300.0 - a) + b);
		}
		else if (tx1 > 100 && tx1 < 1300 && tx2 < 100) {
			this->pointX1 = tx1;
			this->pointY1 = ty1;
			this->pointX2 = 100;
			this->pointY2 = 750 - (tan(ang / 180.0 * PI) * (100.0 - a) + b);
		}
		else {
			this->pointX1 = 100;
			this->pointY1 = 750 - (tan(ang / 180.0 * PI) * (100.0 - a) + b);
			this->pointX2 = 1300;
			this->pointY2 = 750 - (tan(ang / 180.0 * PI) * (1300.0 - a) + b);
		}
		check_point_set = true;
	}
	X = (this->pointX1 - this->pointX2) * (this->pointX1 - this->pointX2);
	Y = (this->pointY1 - this->pointY2) * (this->pointY1 - this->pointY2);
	this->myLong = sqrt(X + Y);
	this->mypoX = (this->pointX1 + this->pointX2) / 2;
	this->mypoY = (this->pointY1 + this->pointY2) / 2;
	this->myBody.setSize(sf::Vector2f(this->myLong, this->mySize));
	this->myBody.setOrigin(this->myLong / 2, this->mySize / 2);
	this->myBody.setPosition(this->mypoX, this->mypoY);
	this->sprite.setScale(this->myLong / 1400.0, this->mySize / 130.0);
	this->sprite.setOrigin(1400 / 2.0, 130 / 2.0);
	this->sprite.setPosition(this->mypoX, this->mypoY);
}
float Laser::getX() {
	return this->mypoX;
}
float Laser::getY() {
	return this->mypoY;
}
sf::RectangleShape Laser::drawRec() {
	return this->myBody;
}
sf::Sprite Laser::draw() {
	return this->sprite;
}
struct NodeLaser {
	Laser laser;
	NodeLaser* next = NULL;
};
class LinkListOfLaser {
private:
	int mySize;
	NodeLaser* head;
	NodeLaser* tail;
public:
	LinkListOfLaser() {
		this->mySize = 0;
		this->head = NULL;
		this->tail = NULL;
	}
	~LinkListOfLaser() {
		delete this->head;
		delete this->tail;
	}
	void append(Laser);
	void append(float, float, float, float, float, float);
	void append(float, float, float, float, float, float, float, float);
	void move();
	void draw(sf::RenderWindow*);
	//bool clashCheck(Player);
	int size();
};
void LinkListOfLaser::append(Laser laser) {
	NodeLaser* temp = new NodeLaser;
	temp->laser = laser;
	temp->next = NULL;
	if (this->mySize == 0) {
		this->head = temp;
		this->tail = temp;
	}
	else {
		this->tail->next = temp;
		this->tail = temp;
	}
	this->mySize = this->mySize + 1;
}
void LinkListOfLaser::append(float a, float b, float size, float ang, float spX, float spY){
	Laser* laser = new Laser(a, b, size, ang, spX, spY);
	NodeLaser* temp = new NodeLaser;
	temp->laser = *laser;
	temp->next = NULL;
	if (this->mySize == 0) {
		this->head = temp;
		this->tail = temp;
	}
	else {
		this->tail->next = temp;
		this->tail = temp;
	}
	this->mySize = this->mySize + 1;
}
void LinkListOfLaser::append(float a, float b, float size, float ang, float spX, float spY, float acX, float acY) {
	//list  ==>  listLaser.append(200, 650, 25, 135, 0, 0, 0.1, 0);
	Laser* laser = new Laser(a, b, size, ang, spX, spY, acX, acY);
	NodeLaser* temp = new NodeLaser;
	temp->laser = *laser;
	temp->next = NULL;
	if (this->mySize == 0) {
		this->head = temp;
		this->tail = temp;
	}
	else {
		this->tail->next = temp;
		this->tail = temp;
	}
	this->mySize = this->mySize + 1;
}
void LinkListOfLaser::move() {
	if (this->mySize > 0) {
		NodeLaser* cur = this->head;
		NodeLaser* pre = this->head;
		while (cur == this->head && cur != NULL) {
			cur->laser.move();
			if (cur->laser.getX() > 1301 || cur->laser.getX() < 99 || cur->laser.getY() < 49 || cur->laser.getY() > 701) {
				if (this->mySize == 1) {
					this->head = NULL;
					this->tail = NULL;
				}
				else {
					this->head = cur->next;
					cur = this->head;
				}
				this->mySize = this->mySize - 1;
			}
			else {
				pre = cur;
				cur = cur->next;
			}
		}
		while (cur != NULL && this->mySize > 0) {
			cur->laser.move();
			if (cur->laser.getX() > 1301 || cur->laser.getX() < 99 || cur->laser.getY() < 49 || cur->laser.getY() > 701) {
				if (this->mySize == 1) {
					this->head = NULL;
					this->tail = NULL;
				}
				else {
					pre->next = cur->next;
					if (cur == this->tail)
						this->tail = pre;
				}
				this->mySize = this->mySize - 1;
			}
			else
				pre = cur;
			cur = cur->next;
		}
	}
}
void LinkListOfLaser::draw(sf::RenderWindow* a) {
	if (this->mySize > 0) {
		NodeLaser* cur;
		cur = this->head;
		while (cur != NULL) {
			a->draw(cur->laser.draw());
			//a->draw(cur->laser.drawRec());
			cur = cur->next;
		}
	}
}

int LinkListOfLaser::size() {
	return this->mySize;
}

class Explode {
private:


public:
	Explode() {

	}
};

class Wallbomb {
private:


public:
	Wallbomb() {

	}
};
class Menu {
private:
	sf::Texture tbackground;
	sf::Texture tfrontground;
	sf::Texture tEmini;

	sf::Sprite spbackground;
	sf::Sprite spfrontground;
	sf::Sprite spEmini;
public:
	Menu() {
		this->tbackground.loadFromFile("images/menu/background.png");
		this->spbackground.setTexture(tbackground);
		this->spbackground.setOrigin(sf::Vector2f(800.5, 400.5));
		this->spbackground.setPosition(sf::Vector2f(800.5, 400.5));
		this->tfrontground.loadFromFile("images/menu/frontground.png");
		this->spfrontground.setTexture(tfrontground);
		this->spfrontground.setOrigin(sf::Vector2f(800.5, 400.5));
		this->spfrontground.setPosition(sf::Vector2f(800.5, 400.5));
		this->tEmini.loadFromFile("images/menu/particlemini.png");
		this->spEmini.setTexture(tEmini);
		this->spEmini.setOrigin(sf::Vector2f(500, 150));
		this->spEmini.setPosition(sf::Vector2f(650, 200));
		/*this->logo.loadFromFile("images/menu/logo.png");
		this->splogo.setTexture(logo);
		this->splogo.setOrigin(300, 100);
		this->splogo.setPosition(800, 200);*/
	}
	void draw(sf::RenderWindow* window) {
		window->draw(this->spbackground);
		window->draw(this->spEmini);
		
		window->draw(this->spfrontground);

		//window->draw(this->splogo);
	}
};
class Game {
private:
	sf::Texture texture;
	sf::Texture textureFrame;
	sf::Sprite sprite;
	sf::Sprite spframe;
	Player* player;
	bool W_CHECK = 0;
	bool PRE_W_CHECK = 0;
public:
	Game() {
		this->texture.loadFromFile("images/background/backg.jpg");
		this->sprite.setTexture(texture);
		this->sprite.setOrigin(sf::Vector2f(800.5, 400.5));
		this->sprite.setPosition(sf::Vector2f(800.5, 400.5));
		this->textureFrame.loadFromFile("images/background/black_frame.png");
		this->spframe.setTexture(textureFrame);
		this->spframe.setOrigin(sf::Vector2f(700, 400));
		this->spframe.setPosition(sf::Vector2f(700, 400));
		this->player = new Player(35.0, "images/kirby_pink/kirbynormal.png", 24.0, 22.0, 3.5, 2, 350);
	}
	~Game() {
		delete this->player;
	}
	void draw(sf::RenderWindow* window) {
		window->draw(this->sprite);
		window->draw(this->player->draw());
		window->draw(this->spframe);
	}
	void play() {
		if (KBP(sf::Keyboard::A)) {
			this->player->left();
		}
		if (KBP(sf::Keyboard::D)) {
			this->player->right();
		}
		if (KBP(sf::Keyboard::S)) {
			this->player->cover();
		}
		W_CHECK = false;
		if (KBP(sf::Keyboard::W)) {
			W_CHECK = true;
		}
		if (!PRE_W_CHECK && W_CHECK) {
			this->player->jump();
		}
		PRE_W_CHECK = W_CHECK;
		this->player->_ALL_OF_UNSTABLE();
		
	}
};

void menu(sf::RenderWindow* window,Menu** menuptr) {
	if (!isSetUp) {
		*menuptr = new Menu();
		isSetUp = true;
	}

	(*menuptr)->draw(window);
}
void inGame(sf::RenderWindow* window, Game** gameptr) {
	if (!isSetUp) {
		*gameptr = new Game();
		isSetUp = true;
	}

	(*gameptr)->play();
	(*gameptr)->draw(window);
}
int main() {
	sf::RenderWindow window(sf::VideoMode(1600, 800), "KIRBY :)", sf::Style::Close);
	sf::Event me;
	window.setFramerateLimit(120);
	stageOfMenu = 1;
	Menu* menu_ptr;
	Game* inGame_ptr;

	sf::RectangleShape r(sf::Vector2f(400,100));
	r.setOrigin(200,50);
	r.setPosition(800,450);

	sf::RectangleShape rr(sf::Vector2f(400, 100));
	rr.setOrigin(200, 50);
	rr.setPosition(800, 650);

	

	while (window.isOpen()) {
		while (window.pollEvent(me)) {
			if (me.type == sf::Event::Closed) {
				window.close();
			}
			else if (me.type == sf::Event::TextEntered) {
				if (me.text.unicode < 128) {
					//std::cout << (char)me.text.unicode;
				}
			}
		}

		window.clear();


		if (stageOfMenu == 0) {
			menu(&window, &menu_ptr);
		}
		else if(stageOfMenu == 1) {
			inGame(&window, &inGame_ptr);
		}
		
		
		
		
		//window.draw(r);
		//window.draw(rr);
	


		window.display();
		if (KBP(sf::Keyboard::Key::LControl) && KBP(sf::Keyboard::Key::P)) {
			window.close();
		}
	}
	return 0;
}