#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "enemy.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "explosion.hpp"

class Game {
public:
    Game();
    void start();
    void update();
    void render();
    bool isRunning() const;

private:
    bool running;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Explosion> explosions; // Track explosions
    int deathCount; // Track the number of times the player has died
    int enemyKillCount; // Track the number of enemies killed
    int spawnCounter; // Counter to control enemy spawning
    static const int spawnInterval = 50; // Interval to spawn new enemies
    static const int gameWidth = 100; // Width of the game space
    static const int gameHeight = 50; // Height of the game space
};

#endif // GAME_HPP