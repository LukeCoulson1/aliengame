#include "bullet.hpp"
#include "enemy.hpp"
#include "player.hpp"

Bullet::Bullet(int startX, int startY, int directionY) 
    : positionX(startX), positionY(startY), directionY(directionY) {}

void Bullet::move() {
    positionY += directionY; // Move the bullet in the specified direction
}

int Bullet::getX() const {
    return positionX;
}

int Bullet::getY() const {
    return positionY;
}

bool Bullet::isOffScreen() const {
    return positionY < 0 || positionY > 49; // Adjust based on game space height
}

bool Bullet::checkCollision(const Enemy& enemy) const {
    return positionX == enemy.getX() && positionY == enemy.getY();
}

bool Bullet::checkCollision(const Player& player) const {
    return positionX == player.getX() && positionY == player.getY();
}