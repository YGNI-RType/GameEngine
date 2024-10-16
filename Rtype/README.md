# R-Type

## Project Purpose

This project is an educational reproduction of the classic R-Type game. It serves as our first "product" project, where we must consider product constraints and maintain a clean architecture, particularly through the use of an Entity Component System (ECS).

## Dependencies

- [raylib](https://www.raylib.com/): Graphics library
- [GEngine](https://github.com/YGNI-RType/GEngine): Internal engine providing ECS with pre-built components and systems and a networking layer
- [stduuid](https://github.com/mariusbancila/stduuid): C++ UUID library
- [vcpkg](https://vcpkg.io/): Package manager to install the dependencies

All dependencies are installed via `vcpkg`, which is automatically downloaded if not present on the system.

## Supported Platforms

- **Linux**
- **macOS**
- **Windows**

## Build

To compile the project:

```bash
cd build
cmake ..
cmake --build .
```

This process uses vcpkg to install the required dependencies and CMake to handle the build.

## Usage

Once compiled, the game requires both a server and a client to run. To start the server, and then the client, use the following commands in the build folder:

```bash
./r_type-server
```

In an other terminal:

```bash
./r_type-server
```

Alternatively, you can use the run.sh script located at the root of the repository to automatically start both the server and the client in one terminal session:

## GEngine integration

R-Type leverages our internally developed GEngine, which provides the ECS architecture, along with various components and systems such as:

### Components

    •	Drawable
    •	Sprites
    •	Texts
    •	Animations
    •	Transform and velocity
    •	Hitboxes

### Systems

    •	AnimationManager
    •	Collisions
    •	Keyboard input handling
    •	RenderWindow
    •	Motion mechanics

GEngine is automatically downloaded and compiled with the cmake .. command.

## License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE.txt) file for details.

## Authors

- Adrien AUDIARD
- Antoine ESMAN
- Basile FOUQUET
- Nathan FLATTIN
- Thomas POMMIER

## Useful Links

[GEngine Github Repository](https://github.com/YGNI-RType/GEngine)

[R-Type Wikipedia](https://en.wikipedia.org/wiki/R-Type)

[R-Type in a browser](https://www.retrogames.cc/arcade-games/r-type-us.html)
