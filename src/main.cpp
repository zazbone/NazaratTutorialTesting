#include "Game.hpp"




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
    struct EntityBundle entities; 

    // Ajout de la composante pour le rendu
    auto& renderSystem = world.AddSystem<Nz::RenderSystem>();
    // Faire le lien avec  un context GPU
    Nz::WindowSwapchain& windowSwapchain = renderSystem.CreateSwapchain(mainWindow);

    // Gestion des évènements
    Nz::WindowEventHandler& eventHandler = mainWindow.GetEventHandler();

    entities.cameraEntity = gameInit::orthographicCamera(world, windowSwapchain);

    entities.textEntity = gameInit::helloWorld(world, mainWindow);

    gameInit::eventHandling(eventHandler, app, entities);

    // Une foin que  tout est déclarer on run l'app (main loop)
    return app.Run();
}