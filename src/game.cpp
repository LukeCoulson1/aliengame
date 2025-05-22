#include "game.hpp"
#include "utils/graphics.hpp"
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm> // Include this header for std::remove_if

// Initialize gameOver to false in the constructor
Game::Game() : running(true), player(gameWidth / 2, gameHeight - 2), lives(3), enemyKillCount(0), spawnCounter(0), gameOver(false) {
    int numEnemies = 5;
    int spacing = gameWidth / (numEnemies + 1);
    for (int i = 0; i < numEnemies; ++i) {
        enemies.push_back(Enemy((i + 1) * spacing, 0, 'E')); // Equally spaced out and centered horizontally
    }
}

void Game::start() {
    // Set console window size to 800x400 pixels
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 400, TRUE);

    // Set console buffer size
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize = {100, 50}; // 100 columns, 50 rows
    SetConsoleScreenBufferSize(hOut, newSize);

    // Ensure the console window is not minimized or hidden
    ShowWindow(console, SW_RESTORE);
    SetForegroundWindow(console);

    // Modified main loop in Game::start()
    while (running) { 
        if (gameOver) {
            renderGameOver();
            if (GetAsyncKeyState('Q') & 0x8000) {
                running = false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } else {
            // Check if game should stop due to other reasons (e.g. player quit mid-game via 'Q' in update)
            // isRunning() currently returns 'running'. If 'Q' is pressed in update(), 'running' becomes false.
            if (!isRunning()) { 
                 break; 
            }
            update();
            render();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Game loop delay
        }
    }
}

void Game::update() {
    // Handle 'Q' to quit first. If 'Q' is pressed, game loop in start() will terminate.
    if (GetAsyncKeyState('Q') & 0x8000) {
        running = false;
        // std::cout << "Game ended by user." << std::endl; // Optional: remove if Game Over screen is enough
        return; // Important to return here so no other updates happen if quitting.
    }

    // If game is over, no game logic updates should occur.
    // This check is technically redundant if start() loop doesn't call update() when gameOver is true,
    // but it's a good safeguard.
    if (gameOver) {
        return;
    }

    // Player movement and actions
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        player.moveUp();
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        player.moveDown();
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        player.moveLeft();
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        player.moveRight();
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        player.shoot(playerBullets);
    }
    if (GetAsyncKeyState('Q') & 0x8000) {
        running = false;
        std::cout << "Game ended by user." << std::endl;
    }

    for (auto& enemy : enemies) {
        enemy.move();
        enemy.shoot(enemyBullets);
    }

    for (auto& bullet : playerBullets) {
        bullet.move();
    }

    for (auto& bullet : enemyBullets) {
        bullet.move();
    }

    // Check for collisions and remove hit enemies and bullets
    for (auto it = playerBullets.begin(); it != playerBullets.end();) {
        bool hit = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if (it->checkCollision(*enemyIt)) {
                explosions.push_back(Explosion(enemyIt->getX(), enemyIt->getY())); // Add explosion
                enemyIt = enemies.erase(enemyIt);
                hit = true;
                enemyKillCount++; // Increment enemy kill count
                break;
            } else {
                ++enemyIt;
            }
        }
        if (hit) {
            it = playerBullets.erase(it);
        } else {
            ++it;
        }
    }

    // Check for collisions and remove hit player and bullets
    for (auto it = enemyBullets.begin(); it != enemyBullets.end();) {
        if (it->checkCollision(player)) {
            lives--; // Decrement lives
            player = Player(gameWidth / 2, gameHeight - 2); // Reset player position (will be refined in next subtask)
            // If lives are depleted, set gameOver state
            if (lives <= 0) {
                gameOver = true;
            }
            it = enemyBullets.erase(it); // Remove the bullet that hit the player
        } else {
            ++it;
        }
    }

    // Remove bullets that are off-screen
    playerBullets.erase(std::remove_if(playerBullets.begin(), playerBullets.end(), [](const Bullet& bullet) {
        return bullet.isOffScreen();
    }), playerBullets.end());

    enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(), [](const Bullet& bullet) {
        return bullet.isOffScreen();
    }), enemyBullets.end());

    // Remove enemies that are off-screen
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
        return enemy.isOffScreen();
    }), enemies.end());

    // Remove expired explosions
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](const Explosion& explosion) {
        return explosion.isExpired();
    }), explosions.end());

    // Spawn new enemies at intervals
    spawnCounter++;
    if (spawnCounter >= spawnInterval) {
        enemies.push_back(Enemy(rand() % gameWidth, 0, 'E')); // Spawn a new enemy at a random X position
        spawnCounter = 0;
    }
}

void Game::render() {
    clearScreen();
    drawPlayer(player.getX(), player.getY());
    for (const auto& enemy : enemies) {
        drawEnemy(enemy.getX(), enemy.getY());
    }
    for (const auto& bullet : playerBullets) {
        drawBullet(bullet.getX(), bullet.getY());
    }
    for (const auto& bullet : enemyBullets) {
        drawBullet(bullet.getX(), bullet.getY());
    }
    for (const auto& explosion : explosions) {
        drawExplosion(explosion.getX(), explosion.getY());
    }

    // Display the scoreboard
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "Lives: " << lives << "  E = " << enemyKillCount;
}

// Implement Game::renderGameOver()
void Game::renderGameOver() {
    clearScreen();
    COORD pos;

    // Display "GAME OVER" message (centered)
    pos = { (short)(gameWidth / 2 - 5), (short)(gameHeight / 2 - 2) }; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "GAME OVER";

    // Display final score (centered below "GAME OVER")
    pos = { (short)(gameWidth / 2 - 15), (short)(gameHeight / 2) }; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "Final Score (Enemies Killed): " << enemyKillCount;

    // Display "Press Q to Quit" message (centered below score)
    pos = { (short)(gameWidth / 2 - 7), (short)(gameHeight / 2 + 2) }; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "Press Q to Quit";
}

bool Game::isRunning() const {
    return running && !gameOver;
}