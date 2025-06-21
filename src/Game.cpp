#include "../headers/Game.h"
#include <iostream>
#include <cmath>
#include <string>

Game::Game()
{
    randInt = Random<int>();
    randFloat = Random<float>();
    //  Try to load the font; if it fails, set isRunning to false and return
    if (!font.loadFromFile("assets/DejaVuSans.ttf"))
    {
        std::cout << "font could not be loaded" << std::endl;
        isRunning = false; // Prevent the game loop from running
        return;
    }

    if (!crackBuffer.loadFromFile("assets/enemyKilled.wav"))
    {
        std::cout << "crack sound could not be loaded" << std::endl;
        isRunning = false; // Prevent the game loop from running
        return;
    }
    crackSound.setBuffer(crackBuffer);
    crackSound.setVolume(100.0f); // Set volume to 100%
    if (!playerLostSoundBuffer.loadFromFile("assets/playerLost.wav"))
    {
        std::cout << "player lost sound could not be loaded" << std::endl;
        isRunning = false; // Prevent the game loop from running
        return;
    }
    if (!bgm.openFromFile("assets/DBZ.wav"))
    {
        std::cout << "BGM could not be loaded" << std::endl;
        isRunning = false; // Prevent the game loop from running
        return;
    }
    else
    {
        bgm.setLoop(true);     // Loop the background music
        bgm.setVolume(100.0f); // Set volume to 50%
        bgm.play();            // Start playing the background music
    }
    playerLostSound.setBuffer(playerLostSoundBuffer);
    playerLostSound.setVolume(100.0f); // Set volume to 100%

    text.setFont(font);          // Set the loaded font
    text.setString("Score : 0"); // Set the string
    text.setCharacterSize(24);   // In pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setPosition(50.0f, 50.0f); // Set position on screen

    window.create(sf::VideoMode(720, 720), "Shape Wars 2D", sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(60);

    entityManager = EntityManager(); // initialize entity manager
    spawnPlayer();
}

void Game::run()
{

    while (isRunning)
    {
        if (isPaused)
        {
            bgm.pause();
        }
        text.setString("Score : " + std::to_string(score));
        float deltaTime = clock.restart().asSeconds();
        entityManager.update();

        if (!player || !player->isActive() && (currFrame - lastPlayerSpawnTime) >= 60 * 2) // spawn player after death of
        {
            spawnPlayer();
        }

        if (!isPaused)
        {

            sMovement();
            sEnemySpawner();
            sCollision();
            sLifespan(deltaTime);
        }
        sUserInput();
        sRender();

        currFrame++;
    }
}

// Systems
void Game::sMovement()
{

    // player movement
    float speed = 3.0f;
    if (player && player->isActive() && player->input)
    {
        player->transform->velocity = {0, 0};
        if (player->isActive() && player->input)
        {
            if (player->input->up)
            {
                player->transform->velocity.y -= speed;
            }
            else if (player->input->down)
            {
                player->transform->velocity.y += speed;
            }
            if (player->input->left)
            {
                player->transform->velocity.x -= speed;
            }
            else if (player->input->right)
            {
                player->transform->velocity.x += speed;
            }
        }
    }

    for (auto entity : entityManager.getEntities())
    {
        if (entity && entity->isActive())
        {
            entity->transform->position.x += entity->transform->velocity.x;
            entity->transform->position.y += entity->transform->velocity.y;

            float radius = entity->shape->body.getRadius();

            // Bounce on left/right borders
            if (entity->transform->position.x - radius < 0)
            {
                entity->transform->position.x = radius;
                entity->transform->velocity.x *= -1;
            }
            else if (entity->transform->position.x + radius > window.getSize().x)
            {
                entity->transform->position.x = window.getSize().x - radius;
                entity->transform->velocity.x *= -1;
            }

            // Bounce on top/bottom borders
            if (entity->transform->position.y - radius < 0)
            {
                entity->transform->position.y = radius;
                entity->transform->velocity.y *= -1;
            }
            else if (entity->transform->position.y + radius > window.getSize().y)
            {
                entity->transform->position.y = window.getSize().y - radius;
                entity->transform->velocity.y *= -1;
            }
        }
    }
}

void Game::sCollision()
{
    for (auto bullet : entityManager.getEntities("bullet"))
    {
        for (auto enemy : entityManager.getEntities("enemy"))
        {
            if (bullet->isActive() && enemy->isActive() && enemy->collision && bullet->collision)
            {
                float ex = enemy->transform->position.x;
                float ey = enemy->transform->position.y;
                float bx = bullet->transform->position.x;
                float by = bullet->transform->position.y;
                float er = enemy->collision->radius;
                float br = bullet->collision->radius;
                float threshold = (er + br) * (er + br);
                float distance = std::pow(bx - ex, 2) + std::pow(by - ey, 2);
                if (distance <= threshold)
                {
                    // collision happened
                    bullet->destroy();
                    size_t sides = enemy->shape->body.getPointCount();
                    sf::Vector2f location = sf::Vector2f(ex, ey);
                    sf::Color color = enemy->shape->body.getFillColor();
                    enemy->destroy();
                    crackSound.play(); // play sound on collision
                    score++;
                    spawnSmallEnemies(location, sides, er, color);
                }
            }
        }
    }
    for (auto enemy : entityManager.getEntities("enemy"))
    {
        if (player->isActive() && enemy->isActive() && enemy->collision && player->collision)
        {
            float ex = enemy->transform->position.x;
            float ey = enemy->transform->position.y;
            float px = player->transform->position.x;
            float py = player->transform->position.y;
            float er = enemy->collision->radius;
            float pr = player->collision->radius;
            float threshold = (er + pr) * (er + pr);
            float distance = std::pow(px - ex, 2) + std::pow(py - ey, 2);
            if (distance <= threshold)
            {
                // collision happened
                sf::Color color = player->shape->body.getFillColor();
                player->destroy();
                playerLostSound.play(); // play sound on collision
                sf::Vector2f pos(px, py);
                spawnSmallEnemies(pos, 8, pr, color);
                score = 0;
                break;
            }
        }
    }
}

void Game::sUserInput()
{
    sf::Event evnt;
    while (window.pollEvent(evnt))
    {
        if (player && player->isActive() && player->input)
        {
            if (evnt.type == sf::Event::Closed)
            {
                isRunning = false;
                window.close();
            }
            if (evnt.type == sf::Event::KeyPressed)
            {
                if (evnt.key.code == sf::Keyboard::Space)
                {
                    isPaused = !isPaused;
                }
                if (evnt.key.code == sf::Keyboard::Escape)
                {
                    isRunning = false;
                    window.close();
                }

                if (evnt.key.code == sf::Keyboard::W)
                {
                    player->input->up = true;
                }
                if (evnt.key.code == sf::Keyboard::S)
                {
                    player->input->down = true;
                }
                if (evnt.key.code == sf::Keyboard::A)
                {
                    player->input->left = true;
                }
                if (evnt.key.code == sf::Keyboard::D)
                {
                    player->input->right = true;
                }
            }
            if (evnt.type == sf::Event::KeyReleased)
            {
                if (evnt.key.code == sf::Keyboard::W)
                {
                    player->input->up = false;
                }
                if (evnt.key.code == sf::Keyboard::S)
                {
                    player->input->down = false;
                }
                if (evnt.key.code == sf::Keyboard::A)
                {
                    player->input->left = false;
                }
                if (evnt.key.code == sf::Keyboard::D)
                {
                    player->input->right = false;
                }
            }
            if (evnt.type == sf::Event::MouseButtonPressed)
            {
                if (evnt.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f target = sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y);
                    spawnBullet(target);
                }
                if (evnt.mouseButton.button == sf::Mouse::Right)
                {
                    spawnSpecialWeapon();
                }
            }
        }
    }
}

void Game::sRender()
{
    window.clear(sf::Color::Black);
    for (auto e : entityManager.getEntities())
    {
        if (e->isActive())
        {
            e->shape->body.setPosition(e->transform->position);
            e->transform->angle += 1.0f;
            e->shape->body.setRotation(e->transform->angle);
            window.draw(e->shape->body);
        }
    }
    window.draw(text);
    window.display();
}

void Game::sEnemySpawner()
{
    if (currFrame - lastEnemySpawnTime > 60 * 3) // spawn an enemy every 3 seconds
    {
        int sides = randInt.get(3, 8);
        float radius = randFloat.get(16.0f, 32.0f);
        spawnEnemy(radius, sides);
    }
}

void Game::sLifespan(float deltaTime)
{
    for (auto entity : entityManager.getEntities())
    {
        if (entity->isActive() && entity->lifespan)
        {
            entity->lifespan->remainingTime -= deltaTime;
            if (entity->lifespan->remainingTime <= 0.0f)
            {
                entity->destroy();
            }
        }
    }
}

// helpers

void Game::spawnPlayer()
{

    float mx = window.getSize().x / 2.0f;
    float my = window.getSize().y / 2.0f;

    auto entity = entityManager.addEntity("player");
    entity->transform = std::make_shared<CTransform>(sf::Vector2f(mx, my), sf::Vector2f(0.0f, 0.0f), 0.0f);
    entity->shape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
    entity->input = std::make_shared<CInput>();
    entity->collision = std::make_shared<CCollision>(32.0f);
    player = entity;
    lastPlayerSpawnTime = currFrame;
}
void Game::spawnEnemy(float radius, int sides)
{
    auto entity = entityManager.addEntity("enemy");
    float ex = randFloat.get(radius, window.getSize().x - radius);
    float ey = randFloat.get(radius, window.getSize().y - radius);

    float rx = randFloat.get(-2.0f, 2.0f);
    float ry = randFloat.get(-2.0f, 2.0f);

    int rc = randInt.get(0, 255);
    int gc = randInt.get(0, 255);
    int bc = randInt.get(0, 255);

    int r = randInt.get(0, 255);
    int g = randInt.get(0, 255);
    int b = randInt.get(0, 255);

    entity->transform = std::make_shared<CTransform>(sf::Vector2f(ex, ey), sf::Vector2f(rx, ry), 0.0f);
    entity->shape = std::make_shared<CShape>(radius, sides, sf::Color(rc, gc, bc), sf::Color(r, g, b), 4.0f);
    entity->collision = std::make_shared<CCollision>(radius);
    lastEnemySpawnTime = currFrame;
}

void Game::spawnSmallEnemies(sf::Vector2f &location, size_t sides, float radius, sf::Color color)
{
    float speed = 5.0f;
    for (int i = 0; i < static_cast<int>(sides); i++)
    {
        float angle = static_cast<float>(i) * 2.0f * 3.14159265f / static_cast<float>(sides);

        auto enemy = entityManager.addEntity("enemy");
        enemy->transform = std::make_shared<CTransform>(location, sf::Vector2f(speed * std::cos(angle), speed * std::sin(angle)), 0.0f);
        enemy->shape = std::make_shared<CShape>(radius / 2.0f, sides, color, sf::Color::White, 4.0f);
        enemy->lifespan = std::make_shared<CLifespan>(1.0f);
    }
}

void Game::spawnBullet(sf::Vector2f &target)
{
    float bx = player->transform->position.x;
    float by = player->transform->position.y;
    float tx = target.x;
    float ty = target.y;
    float dx = tx - bx;
    float dy = ty - by;
    float mag = std::sqrt(dx * dx + dy * dy);
    if (mag == 0)
    {
        mag = 1.0f;
    }
    float speed = 10.0f;
    auto bullet = entityManager.addEntity("bullet");
    bullet->transform = std::make_shared<CTransform>(sf::Vector2f(bx, by), sf::Vector2f(speed * dx / mag, speed * dy / mag), 0.0f);
    bullet->shape = std::make_shared<CShape>(10, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2);
    bullet->collision = std::make_shared<CCollision>(10.0f); // Add collision component
    bullet->lifespan = std::make_shared<CLifespan>(2.0f);    // Add lifespan component
}

void Game::spawnSpecialWeapon()
{
    float px = player->transform->position.x;
    float py = player->transform->position.y;

    for (int i = 0; i < 8; i++)
    {
        float angle = static_cast<float>(i) * 2.0f * 3.14159265f / 8.0f;

        auto bullet = entityManager.addEntity("bullet");
        bullet->transform = std::make_shared<CTransform>(sf::Vector2f(px, py), sf::Vector2f(5.0f * std::cos(angle), 5.0f * std::sin(angle)), 0.0f);
        bullet->shape = std::make_shared<CShape>(10.0f, 8, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
        bullet->collision = std::make_shared<CCollision>(10.0f);
        bullet->lifespan = std::make_shared<CLifespan>(2.0f);
    }
}