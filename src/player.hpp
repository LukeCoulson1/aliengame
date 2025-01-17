#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "bullet.hpp"

class Player {
public:
    Player(int startX, int startY);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void shoot(std::vector<Bullet>& bullets);
    int getX() const;
    int getY() const;

private:
    int positionX;
    int positionY;
    static const int minX = 0;
    static const int maxX = 99; // Adjust based on game space width
    static const int minY = 0;
    static const int maxY = 49; // Adjust based on game space height
};

#endif // PLAYER_HPP