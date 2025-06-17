#include "../headers/animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u _imageCount, float _switchTime)
{
    imageCount = _imageCount;
    switchTime = _switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}
Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime)
{
    currentImage.x = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.y++;

        if (currentImage.y >= imageCount.y)
        {
            currentImage.y = 0;
        }
    }

    uvRect.left = currentImage.y * uvRect.width;
    uvRect.top = currentImage.x * uvRect.height;
}
