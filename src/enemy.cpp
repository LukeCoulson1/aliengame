#include "enemy.hpp"
#include <cstdlib> // For rand()

Enemy::Enemy(int x, int y, char type) 
    : positionX(x), positionY(y), enemyType(type), directionX(1), directionY(1), moveCounter(0) {
    speed = rand() % 5 + 1; // Random speed between 1 and 5
    directionChangeInterval = rand() % 20 + 10; // Random interval between 10 and 30
    shootInterval = rand() % 50 + 50; // Random interval between 50 and 100
}

void Enemy::move() {
    moveCounter++;
    if (moveCounter % speed == 0) { // Move based on the speed
        positionX += directionX; // Move the enemy horizontally
        positionY += directionY; // Move the enemy vertically

        // Change direction at screen edges
        if (positionX <= minX || positionX >= maxX) {
            directionX = -directionX;
        }
        if (positionY <= minY || positionY >= maxY) {
            directionY = -directionY;
        }

        // Randomly change direction at intervals
        if (moveCounter % directionChangeInterval == 0) {
            directionX = (rand() % 3) - 1; // Random direction: -1, 0, or 1
            directionY = (rand() % 3) - 1; // Random direction: -1, 0, or 1
            speed = rand() % 5 + 1; // Random speed between 1 and 5
            directionChangeInterval = rand() % 20 + 10; // Random interval between 10 and 30
        }
    }
}

void Enemy::shoot(std::vector<Bullet>& bullets) {
    if (rand() % shootInterval == 0) { // Randomly decide to shoot
        bullets.push_back(Bullet(positionX, positionY + 1, 1)); // Shoot a bullet downward
    }
}

int Enemy::getX() const {
    return positionX;
}

int Enemy::getY() const {
    return positionY;
}

bool Enemy::checkCollision(int playerX, int playerY) const {
    // Simple collision detection logic
    return (playerX == positionX && playerY == positionY);
}

bool Enemy::isOffScreen() const {
    return positionY > maxY; // Check if the enemy is off the bottom of the screen
}