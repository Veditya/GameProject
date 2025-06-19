#include "headers/entities/player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::countKills()
{
    kills++;
}

int Player::getKills() { return kills; }

bool Player::checkMode() { return mode; }

void Player::update(float deltaTime)
{
}
void Player::Shoot(sf::Vector2f mousePos)
{
}