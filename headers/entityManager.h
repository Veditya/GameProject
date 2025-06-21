#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Entity.h"
#include <map>
#include <memory>

class EntityManager
{
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> toAdd;
    std::map<std::string, std::vector<std::shared_ptr<Entity>>> entityMaps;
    size_t nextId = 0;

public:
    EntityManager();
    ~EntityManager() = default;

    void init();

    std::shared_ptr<Entity> addEntity(const std::string &_tag);

    std::vector<std::shared_ptr<Entity>> &getEntities();

    std::vector<std::shared_ptr<Entity>> &getEntities(std::string t);

    void update();
};

#endif