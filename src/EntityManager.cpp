#include "../headers/EntityManager.h"

EntityManager::EntityManager() : entities{}, toAdd{}, entityMaps{} {}

void EntityManager::init()
{
    entities.clear();
    toAdd.clear();
    entityMaps.clear();
}
std::shared_ptr<Entity> EntityManager::addEntity(const std::string &_tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(nextId++, _tag));
    toAdd.push_back(entity);
    return entity;
}

std::vector<std::shared_ptr<Entity>> &EntityManager::getEntities()
{
    return entities;
}
std::vector<std::shared_ptr<Entity>> &EntityManager::getEntities(std::string t)
{
    return entityMaps[t];
}
void EntityManager::update()
{
    // Add new entities
    for (auto &entity : toAdd)
    {
        entities.push_back(entity);
        entityMaps[entity->getTag()].push_back(entity);
    }
    toAdd.clear();

    // Remove inactive entities
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [](const std::shared_ptr<Entity> &entity)
                                  { return !entity->isActive(); }),
                   entities.end());

    // Update entity maps
    for (auto &pair : entityMaps)
    {
        pair.second.erase(std::remove_if(pair.second.begin(), pair.second.end(),
                                         [](const std::shared_ptr<Entity> &entity)
                                         { return !entity->isActive(); }),
                          pair.second.end());
    }
}