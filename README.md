[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/XUCedPox)
# Design Patterns Assignment
Team: Anton Hedlund, Magnus Andersson, Johan Brandt, Erik Lund

## Pacman Clone
Our game is a basic Pacman clone; with many but not all features of the original game. We have built the code in two distinct projects; an Engine part and a game part. 

The Engine project wraps all SDL functionality, such as window management, rendering and input management, as well as data types, and file loading.

The Game project handles all gameplay, with a tickable World->Actor->ActorComponent hierarchy. It does not interact directly with the SDL library.

The image in the left side of this table is an early version of the map using dummy sprites to visualise the level. The right image is the final version; which is generated in runtime based on the gameplay grid in the [CellSpriteGenerator.h](PacmanClone/source/Grid/CellSpriteGenerator.h), using the Sprite Atlas found below.

| Early Dummy Map | Real Map | 
| --- | --- |
| ![Early Dummy Map](Screenshots/DummyMap.png) | ![Real Map](Screenshots/RealMap.png) 

| Sprite Atlas |
| --- | 
| ![Sprite Atlas](Screenshots/SpriteAtlasCropped.png) |



## Patterns used
### Game Loop & Update Method
It seemed almost impossible to make our game without using these two patterns. The game loop is required for the SDL rendering to function properly while handling game logic and input. Choosing to manage game entities with an update (tick) method was only marginally less obvious; it let us manage game objects as you would in engines like Unity and Unreal, making it very easy to apply the Component pattern as well (see below.)

[GameBase.h](/GameEngine/source/Engine/Game/GameBase.h) is defined in the Engine, and manages the **main game loop** with input handling, **DeltaTime-ticking**, rendering, and FPS-locking, in that order. The base is extended by [PacmanGame.h](PacmanClone/source/Game/PacmanGame.h) which manages the actual game initialization with map generation using [GridGenerator.h](PacmanClone/source/Grid/GridGenerator.h) which uses level information parsed from a CSV file by [PacmanLevelInfoParser.h](PacmanClone/source/Game/PacmanLevelInfoParser.h). The actual level information is stored as a simple [.txt file](PacmanClone/MapGenFiles/LevelInfo.txt) with a pre-determined pattern given by the enums in the GridGenerator.

### Broker & Observer
The main gameplay involves eating lots of dots. To be able to separate the dots being eaten from win conditions and possible score-keeping; we decided to combine the Observer and Broker patterns. Normally a Broker might use a generic message system; but for the scope of our game we instead went with a few pre-determined Observable Events, defined in [Event.h](PacmanClone/source/Event/Event.h). These are all statically accessible through the [EventBroker.h](PacmanClone/source/Event/EventBroker.h). When a dot is eaten, it invokes the respective Event in the Broker, and other systems can register their functions as observers without changing the functionality of the dot.

### Component
As mentioned above, the game's objects are managed in a World->Actor->ActorComponent hierarchy. There are multiple [ActorComponent.h](PacmanClone/source/World/Actors/ActorComponent.hpp) implementations, such as [SpriteComponent.h](PacmanClone/source/World/Actors/SpriteComponent.hpp) which keeps information about what needs to be rendered on screen, using the Actor's [Transform.h](GameEngine/source/Data/Transform.hpp) to determine location and size. This component is the only thing that the renderer needs to be able to visualize an object on screen. Movement is also handled in the [MovementComponent.h](PacmanClone/source/Movement/MovementComponent.h). Once again, using a Component pattern let us avoid inheritance when possible, while working in a way that resembles the way you would in one of the more extensive game engines.

### Flyweight
Since our game uses a Sprite Atlas for our in-game sprites, we realised it would be an excellent use case for the Flyweight pattern. We decided to make the [Sprite.hpp](GameEngine/source/Data/Visuals/Sprite.hpp) and [SpriteComponent.h](PacmanClone/source/World/Actors/SpriteComponent.hpp) separate, and multiple Components can reference a single Sprite. That way we only have to load and store each texture once even if we render it hundreds of times per frame, such as with the edible Dot. 

We do this by using an [AssetLoader.hpp](GameEngine/source/Engine/Asset/AssetLoader.hpp) which we tell to pre-load all textures at the start of the game, generating the necessary Sprite objects. A SpriteComponent can then ask the AssetLoader for a reference to the Sprite it wants to render. Finally, the Renderer uses the SpriteComponent's owner's Transform to determine location and size for rendering.
