#include <Nazara/Core.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform/AppWindowingComponent.hpp>


struct EntityBundle
{
    entt::handle cameraEntity;
    entt::handle textEntity;
};


namespace gameInit {
    entt::handle orthographicCamera(Nz::EnttWorld& world, Nz::WindowSwapchain& windowSwapchain);

    entt::handle helloWorld(Nz::EnttWorld& world, Nz::Window& mainWindow);

    void eventHandling(Nz::WindowEventHandler& eventHandler, Nz::Application<Nz::Graphics>& app, struct EntityBundle& entities);
}