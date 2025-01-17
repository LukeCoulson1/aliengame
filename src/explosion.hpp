#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <chrono>

class Explosion {
public:
    Explosion(int x, int y);
    bool isExpired() const;
    int getX() const;
    int getY() const;

private:
    int positionX;
    int positionY;
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    static const int duration = 500; // Duration of the explosion in milliseconds
};

#endif // EXPLOSION_HPP