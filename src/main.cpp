#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform/AppWindowingComponent.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <iostream>
#include "init.hpp"

int main()
{
    // Mise en place de l'application, de la fenêtre et du monde

    // Initialisation de l'application avec le module Graphique
    Nz::Renderer::Config rendererConfig;
    rendererConfig.preferredAPI = Nz::RenderAPI::OpenGL;
    Nz::Application<Nz::Graphics> app(rendererConfig);

    // Ajout de composantes à l'app (tout type de ApplicationComponent)
    // Ici une pour avoir du fenetrage, windowing et une ref à cette composante.
    auto& windowing = app.AddComponent<Nz::AppWindowingComponent>();
    // Ici on créer une fenetre principale, et on récupère de nouveau une ref.
    Nz::Window& mainWindow = windowing.CreateWindow(Nz::VideoMode(1280, 720), "Tut01 - Hello world");
    // Jusqu'ici, tout ce que fait app.Run() est de faire apparaitre une fenetre vide.

    // Ajout des composante ecs et le world
    auto& ecs = app.AddComponent<Nz::AppEntitySystemComponent>();
    auto& world = ecs.AddWorld<Nz::EnttWorld>();

    // Ajout de la composante pour le rendu
    auto& renderSystem = world.AddSystem<Nz::RenderSystem>();
    // Faire le lien avec  un context GPU
    Nz::WindowSwapchain& windowSwapchain = renderSystem.CreateSwapchain(mainWindow);

    // Gestion des évènements
    Nz::WindowEventHandler& eventHandler = mainWindow.GetEventHandler();
    gameInit::eventHandling(eventHandler, app);

    [[maybe_unused]]
    entt::handle cameraEntity = gameInit::orthographicCamera(world, windowSwapchain);

    [[maybe_unused]]
    entt::handle textEntity = gameInit::helloWorld(world, mainWindow);

    // Une foin que  tout est déclarer on run l'app (main loop)
    return app.Run();
}