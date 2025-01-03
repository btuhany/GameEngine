# OpenGL Game Engine

This is a 2D/3D game engine developed from scratch using **C++** and the **OpenGL API**.

This is my first attempt at developing a game engine for learning and experimenting with various game & engine development concepts and techniques, including rendering, physics, and system architecture. With this project, I started learning OpenGL and improving my fundamental knowledge of C/C++.

The purpose of this project is to
- Improve my programming skills by learning C++ and OpenGL, 
- Understand the fundamentals of how game and rendering engines work
- Learn the key concepts of graphics programming while putting theory into practice.

The project currently includes a 3D Sandbox project and a 2D game: Breakout, which demonstrate some basic functionality of the engine.

### Features
- Basic ECS 
	- Components: Collider, BoxCollider2D, MeshRenderer, SpriteRenderer, Transform, UIRenderer, UITextRenderer
	- Systems: Renderer, Collision
- Event Bus / Event Manager
- Rendering: OpenGL API implementation
	- Ambient and diffuse lighting
	- Point, spot, directional lights
	- Skybox
	- ShadowMaps
	- Orthographic and perspective camera 
- Basic custom math library
- Resources: texture, shader (frag, vert, geo), sprite, material (specular and shininess), mesh and model

### Libraries Used
- SPDLOG -> Logging
- Assimp -> 3D model importing
- STB_IMAGE -> Image loading
- FreeType -> Text Rendering

## Plans  
I plan to continue improving this project from time to time. 
Instead of focusing on simple games, I aim to add/implement new core systems, architectural designs and mechanics used in current game engines and that can be built using OpenGL to this engine and experiment with the ideas. 

#### Refactoring/Missing Tasks  
There are many parts of the project that need refactoring. More detailed version is in the Notes.md file in docs folder.
- Make file and make system
- Abstract component class with data template
- Engine starting settings static class
- Abstract entity/components which use Initialize, Start, Tick
- Abstract managers (renderer, textRenderer, collision manager)
- FPS limit fix
- Camera space ui canvas
- JSON Serialization/Deserialization
- Application quit handler
- Multiple scenes / transitions
- DLL instead of Static Library
- Primitives: quad, cube, plane
- x64 instead of x86
- Architecture related refactors

#### Features to Add  
- Sound engine
- Animation system (also skinned meshes)
- Post-processor system
- Instanced drawing
- Anti aliasing
- Normal mapping
- Deferred shading
- Async resource loading
- Engine editor (ImGui)
- Physics engine (Nvidia physx)

## References and Resources
Throughout this project, I utilized various resources to improve my knowledge and guide my implementation. The primary resources i used in this project:
- OpenGL Official Documentation
- LearnOpenGL
- "Computer Graphics with Modern OpenGL and C++" udemy course by Ben Cook
- The Cherno, YouTube channel
  
I am deeply grateful to all the authors, contributors, and communities who made these resources available.
