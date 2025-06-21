#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <string>
#include <cstddef>
#include "CTransform.h"
#include "CCollision.h"
#include "CShape.h"
#include "CLifespan.h"
#include "CInput.h"
#include "CScore.h"
#include <memory>
#include <tuple>

class Entity
{
private:
    bool active = true;
    size_t id = 0;
    std::string tag = "default";

public:
    // by default null
    std::shared_ptr<CTransform> transform;
    std::shared_ptr<CCollision> collision;
    std::shared_ptr<CShape> shape;
    std::shared_ptr<CLifespan> lifespan;
    std::shared_ptr<CInput> input;
    std::shared_ptr<CScore> score;

public:
    Entity(size_t _id, const std::string &t) : id(_id), tag(t) {}
    ~Entity() = default;

    void destroy()
    {
        active = false;
    }

    bool isActive() const
    {
        return active;
    }

    std::string getTag()
    {
        return tag;
    }
    size_t Id() const
    {
        return id;
    }
};

#endif