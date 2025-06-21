#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "EntityManager.h"
#include "Entity.h"
#include <memory>
#include "../headers/Random.h"

class Game
{
private:
    sf::RenderWindow window;     //
    EntityManager entityManager; //
    Random<int> randInt;
    Random<float> randFloat;
    sf::Font font;               //
    sf::Text text;               //
    sf::Clock clock;             //
    sf::Music bgm;               //
    sf::SoundBuffer crackBuffer; //
    sf::Sound crackSound;
    sf::SoundBuffer playerLostSoundBuffer; //
    sf::Sound playerLostSound;             //
    std::shared_ptr<Entity> player;        //

    int score = 0;
    int currFrame = 0;
    int lastEnemySpawnTime = 0;
    int lastPlayerSpawnTime = 0;

    // Game state variables
    bool isRunning = true;
    bool isPaused = false;

public:
    Game();

    ~Game() = default;

    void run();

    // Systems
    void sMovement();

    void sCollision();

    void sUserInput();

    void sRender();

    void sEnemySpawner();

    void sLifespan(float deltaTime);

    // helpers

    void spawnPlayer();
    void spawnEnemy(float radius, int sides);
    void spawnSmallEnemies(sf::Vector2f &location, size_t sides, float radius, sf::Color);
    void spawnBullet(sf::Vector2f &mousePos);
    void spawnSpecialWeapon();
};

#endif