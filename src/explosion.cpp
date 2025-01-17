#include "explosion.hpp"
#include <chrono>

Explosion::Explosion(int x, int y) : positionX(x), positionY(y) {
    startTime = std::chrono::steady_clock::now();
}

bool Explosion::isExpired() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
    return elapsed > duration;
}

int Explosion::getX() const {
    return positionX;
}

int Explosion::getY() const {
    return positionY;
}