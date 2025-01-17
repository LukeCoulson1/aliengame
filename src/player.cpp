#include "player.hpp"

Player::Player(int startX, int startY) : positionX(startX), positionY(startY) {}

void Player::moveUp() {
    if (positionY > minY) {
        positionY--;
    }
}

void Player::moveDown() {
    if (positionY < maxY) {
        positionY++;
    }
}

void Player::moveLeft() {
    if (positionX > minX) {
        positionX--;
    }
}

void Player::moveRight() {
    if (positionX < maxX) {
        positionX++;
    }
}

void Player::shoot(std::vector<Bullet>& bullets) {
    bullets.push_back(Bullet(positionX, positionY - 1, -1)); // Shoot a bullet upward
}

int Player::getX() const {
    return positionX;
}

int Player::getY() const {
    return positionY;
}