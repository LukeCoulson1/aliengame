#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include "bullet.hpp"

class Enemy {
public:
    Enemy(int x, int y, char type);
    void move();
    void shoot(std::vector<Bullet>& bullets);
    int getX() const;
    int getY() const;
    bool checkCollision(int playerX, int playerY) const;
    bool isOffScreen() const; // Add this method to check if the enemy is off-screen

private:
    int positionX;
    int positionY;
    char enemyType;
    int directionX; // 1 for right, -1 for left
    int directionY; // 1 for down, -1 for up
    int moveCounter; // Counter to control the speed of movement
    int speed; // Speed of the enemy
    int directionChangeInterval; // Interval to change direction
    int shootInterval; // Interval to shoot bullets
    static const int minX = 0;
    static const int maxX = 99; // Adjust based on game space width
    static const int minY = 0;
    static const int maxY = 24; // Adjust based on half game space height
};

#endif // ENEMY_HPP