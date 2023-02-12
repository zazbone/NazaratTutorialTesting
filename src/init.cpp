#include "Game.hpp"

namespace gameInit {
entt::handle orthographicCamera(Nz::EnttWorld& world, Nz::WindowSwapchain& windowSwapchain) {
    // Création de la caméra, c'est la première entitée qu'on ajoute à l'ecs
    entt::handle cameraEntity = world.CreateEntity();
    // Donne des propriétée spatiales à la camera et permet d'y atacher d'autres entitée.
    cameraEntity.emplace<Nz::NodeComponent>();

    // On lui donne la propriétée d'être une camera 2D
    auto& cameraComponent = cameraEntity.emplace<Nz::CameraComponent>(&windowSwapchain, Nz::ProjectionType::Orthographic);
    cameraComponent.UpdateClearColor(Nz::Color(0.46f, 0.48f, 0.84f, 1.f));

    return cameraEntity;
}

entt::handle helloWorld(Nz::EnttWorld& world, Nz::Window& mainWindow) {
    // Création d'un texte avec une sorte de texte box
    Nz::SimpleTextDrawer textDrawer;
    textDrawer.SetText("Hello world !");
    textDrawer.SetCharacterSize(72);
    textDrawer.SetOutlineThickness(4.f);

    // Le rendu de la textbox
    std::shared_ptr<Nz::TextSprite> textSprite = std::make_shared<Nz::TextSprite>();
    textSprite->Update(textDrawer);

    // Ajoute de l'entitée texte
    entt::handle textEntity = world.CreateEntity();
    {
        // On en fait une node
        auto& nodeComponent = textEntity.emplace<Nz::NodeComponent>();

        // On lui donne acces au rendu et on y attache le sprite
        auto& gfxComponent = textEntity.emplace<Nz::GraphicsComponent>();
        gfxComponent.AttachRenderable(textSprite);

        // On set les positions spatiales de la node de texte
        Nz::Boxf textBox = textSprite->GetAABB();
        Nz::Vector2ui windowSize = mainWindow.GetSize();
        nodeComponent.SetPosition(windowSize.x / 2 - textBox.width / 2, windowSize.y / 2 - textBox.height / 2);
    }
    return textEntity;
}

void eventHandling(Nz::WindowEventHandler& eventHandler, Nz::Application<Nz::Graphics>& app, struct EntityBundle& entities) {
    // Quand la fenetre est fermé
    eventHandler.OnQuit.Connect([&](const Nz::WindowEventHandler*)
    {
        app.Quit(); //< fermeture de l'application (et donc de la fenêtre)
    });

    Nz::NodeComponent& textNode = entities.textEntity.get<Nz::NodeComponent>();

    // Lorsqu'une key est appuyé
    eventHandler.OnKeyPressed.Connect([&](const Nz::WindowEventHandler*, const Nz::WindowEvent::KeyEvent& key)
    {
        switch (key.scancode)
        {
        case Nz::Keyboard::Scancode::Escape:
            app.Quit();
            break;
        case Nz::Keyboard::Scancode::Up:
            textNode.Move(0, 100);
            break;
        case Nz::Keyboard::Scancode::Down:
            textNode.Move(0, -100);
            break;
        case Nz::Keyboard::Scancode::Right:
            textNode.Move(100, 0);
            break;
        case Nz::Keyboard::Scancode::Left:
            textNode.Move(-100, 0);
            break;
        case Nz::Keyboard::Scancode::Space:
            fmt::print("Jump! Go ahead and jump!\n");
            break;
        default:
            fmt::print("Key pressed: {}\n", Nz::Keyboard::GetKeyName(key.virtualKey));
            break;
        }
    });

    // Lorsqu'une key est released
    eventHandler.OnKeyReleased.Connect([&](const Nz::WindowEventHandler*, const Nz::WindowEvent::KeyEvent& key)
    {
        switch (key.scancode)
        {
        case Nz::Keyboard::Scancode::Space:
            fmt::print("Space bar released.\n");
            break;
        default:
            //fmt::print("Key released: {}\n", Nz::Keyboard::GetKeyName(key.virtualKey));
            break;
        }
    });

    

}
}