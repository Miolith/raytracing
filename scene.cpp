#include <ranges>
#include "object.hpp"
#include "scene.hpp"

Scene::Scene()
{}

Scene::~Scene()
{}

void Scene::add(Object& object)
{
    objects.push_back(&object);
}

void Scene::add(Object&& object)
{
    objects.push_back(&object);
}

std::vector<Object*> Scene::getObjects()
{
    return objects;
}