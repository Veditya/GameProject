#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <tuple>
#include <type_traits>
#include <stdexcept>
#include <string>

template <typename... Components>

class Entity : public std::enable_shared_from_this<Entity<Components...>>
{
protected:
    std::tuple<std::shared_ptr<Components>...> components;
    bool alive = true;
    std::string tag;

public:
    Entity() = default;
    virtual ~Entity() = default;

    template <typename T>
    void add<T>(std::shared_ptr<T> component)
    {
        std::get<std::shared_ptr<T>>(components) = component;
        std::get<std::shared_ptr<T>>(components)->exists = true;
    }

    template <typename T>
    std::shared_ptr<T> &get(T)
    {
        std::get<std::shared_ptr<T>>(components);
    }

    template <typename T>
    bool has()
    {
        return std::get<std::shared_ptr<T>>(components)->exists;
    }

    template <typename T>
    void remove()
    {
        std::get<std::shared_ptr<T>>(components).reset();
    }

    std::string getTag()
    {
        return tag;
    }

    void setTag(string &x)
    {
        tag = x;
    }

    bool isAlive()
    {
        return alive;
    }

    void kill()
    {
        alive = false;
    }

    virtual void update(float deltaTime);
};

#endif