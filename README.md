[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/XUCedPox)
# Design Patterns Assignment
Team: Anton Hedlund, Magnus Andersson, Johan Brandt, Erik Lund

## Pacman Clone
Our game is a basic Pacman clone; with many but not all features of the original game. We have built the code in two distinct projects; an Engine part and a game part. 

The Engine project wraps all SDL functionality, such as window management, rendering and input management, as well as data types, and file loading.

The Game project handles all gameplay, with a tickable World->Actor->ActorComponent hierarchy. It does not interact directly with the SDL library.

## Patterns used
### Game Loop & Update Method
[GameBase.h](/GameEngine/source/Engine/Game/GameBase.h) is defined in the Engine, and manage the **main game loop** with input handling, **DeltaTime-ticking**, rendering, and FPS-locking, in that order. The base is extended by [PacmanGame.h](PacmanClone/source/Game/PacmanGame.h) which manages the actual game initialization with map generation using [GridGenerator.h](PacmanClone/source/Grid/GridGenerator.h) which reads info parsed from a CSV file by [PacmanLevelInfoParser.h](PacmanClone/source/Game/PacmanLevelInfoParser.h)

### Broker
The main gameplay involves eating lots of dots. The main gameplay functionality communicates with these actions through the [EventBroker.h](PacmanClone/source/Event/EventBroker.h) which has a few statically accessible Events, defined in [Event.h](PacmanClone/source/Event/Event.h). The win condition system can listen to the OnDotEaten event to keep track of how many are eaten; and each Dot can invoke the event upon consumption.

### Component
As mentioned in the summary above, the game's objects are managed in a World->Actor->ActorComponent hierarchy. There are multiple [ActorComponent.h](PacmanClone/source/World/Actors/ActorComponent.hpp) implementations, such as [SpriteComponent.h](PacmanClone/source/World/Actors/SpriteComponent.hpp) which keeps information about what needs to be rendered on screen, using the Actor's [Transform.h](GameEngine/source/Data/Transform.hpp) to determine location and size. This component is the only thing that the renderer needs to be able to visualize an object on screen. Movement is also handled in the [MovementComponent.h](PacmanClone/source/Movement/MovementComponent.h)
