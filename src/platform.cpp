#include "../headers/platform.h"

Platform::Platform(sf::RectangleShape _body) : body{_body}, collider{nullptr} {}

Platform::~Platform() {}

void Platform::setCollider(Collider *_collider)
{
    collider = _collider;
}