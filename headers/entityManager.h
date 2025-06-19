#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include "./headers/entities/entity.h"

template <typename... Components>
class EntityManager
{
private:
    using EntityType = Entity<Components...>;
    using EntityPtr = std::shared_ptr<EntityType>;

    std::vector<EntityPtr> entities;
    std::map<std::string, std::vector<EntityPtr>> entity_map;
    std::vector<EntityPtr> toAdd;

public:
    EntityManager() = default;

    EntityPtr addEntity()
    {
        auto entity = std::make_shared<EntityType>();
        toAdd.push_back(entity);
        return entity;
    }

    void updateAll(float deltaTime)
    {
        for (auto &entity : entities)
        {
            if (entity->isAlive())
                entity->update(deltaTime);
        }

        entities.erase(std::remove_if(entities.begin(), entities.end(),
                                      [](const EntityPtr &e)
                                      { return !e->isAlive(); }),
                       entities.end());

        for (auto &pair : entity_map)
        {
            pair.second.erase(std::remove_if(pair.second.begin(), pair.second.end(),
                                             [](const EntityPtr &e)
                                             { return !e->isAlive(); }),
                              pair.second.end());
        }

        for (auto &entity : toAdd)
        {
            entities.push_back(entity);
            entity_map[entity->getTag()].push_back(entity);
        }
        toAdd.clear();
    }

    const std::vector<EntityPtr> &getEntities() const { return entities; }

    const std::vector<EntityPtr> &getEntitiesByTag(const std::string &tag) const
    {
        static const std::vector<EntityPtr> empty;
        auto it = entity_map.find(tag);
        return (it != entity_map.end()) ? it->second : empty;
    }
};

#endif