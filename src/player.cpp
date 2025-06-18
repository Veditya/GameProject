
#include "../headers/player.h"

Player::Player(sf::RectangleShape _body) : body{_body}, collider{nullptr}, animation{nullptr} {}

Player::~Player() {}

void Player::setCollider(Collider *_collider)
{
    collider = _collider;
}

void Player::setAnimation(Animation *_animation)
{
    animation = _animation;
}

void Player::update(float deltaTime)
{
    // keyboard input processing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        animation->update(1, deltaTime);
        body.move(-0.1f, 0.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        animation->update(2, deltaTime);
        body.move(0.05f, 0.0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        animation->update(3, deltaTime);
        body.move(0.0, -0.05f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        animation->update(0, deltaTime);
        body.move(0.0, 0.05f);
    }
}
