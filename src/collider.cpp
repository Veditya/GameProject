#include "../headers/collider.h"

bool Collider::checkCollision(Collider *other, float push)
{
    sf::Vector2f thisPosition = body.getPosition();
    sf::Vector2f otherPosition = other->GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    sf::Vector2f otherHalfSize = other->GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + otherHalfSize.y);
    float intersectY = abs(deltaY) - (otherHalfSize.y + otherHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if (intersectX > intersectY)
        {
            if (deltaX > 0.0f)
            {
                move(intersectX * (1.0f - push), 0.0f);
                other->move(-intersectX * push, 0.0f);
            }
            else
            {
                move(-intersectX * (1.0f - push), 0.0f);
                other->move(intersectX * push, 0.0f);
            }
        }
        else
        {
            if (deltaY > 0.0f)
            {
                move(0.0f, intersectY * (1.0f - push));
                other->move(0.0f, -intersectY * push);
            }
            else
            {
                move(0.0f, -intersectY * (1.0f - push));
                other->move(0.0f, intersectY * push);
            }
        }
        return true;
    }

    return false;
}

void Collider::move(float dx, float dy)
{
    body.move(dx, dy);
}

Collider::Collider(sf::RectangleShape &_body) : body{_body} {}

Collider::~Collider()
{
}

sf::Vector2f Collider::GetPosition()
{
    return body.getPosition();
}

sf::Vector2f Collider::GetHalfSize()
{
    return body.getSize() / 2.0f;
}