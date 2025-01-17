#ifndef BULLET_HPP
#define BULLET_HPP

class Enemy; // Forward declaration
class Player; // Forward declaration

class Bullet {
public:
    Bullet(int startX, int startY, int directionY);
    void move();
    int getX() const;
    int getY() const;
    bool isOffScreen() const;
    bool checkCollision(const Enemy& enemy) const;
    bool checkCollision(const Player& player) const;

private:
    int positionX;
    int positionY;
    int directionY; // Direction of the bullet: -1 for up, 1 for down
};

#endif // BULLET_HPP