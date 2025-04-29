Programming Test Internship Gameplay Programmer Larian Studios
Carlos Caz Pretus

The next level test consisted of developing the Arkanoid (Breakout) videogame with C++ in a period of one week.

During the development of the project I used the following libraries to cover different aspects of the game:

- OpenGL, GLFW, Glad: For the use of a graphics library with modern OpenGL.

- GLM: Although it is possible to create my own library of math operations and 2D vectors, I have opted for the use of GLM to simplify and speed up the development.

- STB_image: When loading textures with OpenGL in the game I have made use of this library.

- ImGUI: When implementing a UI element that indicates the player's score, as first option I opted for the use of FreeType, but the limited experience I have with that library required to carry out a research that increased the development time, so I finally opted for the use of ImGUI as it is a library I have worked with before and I know better.


The game architecture is based on my own ECS where the structure of the game elements or entities is based on components, where each system executes the logic associated to its respective component.

In addition, in the code architecture I have implemented design patterns to have a more scalable, efficient and secure code:

- Singleton Pattern: I have used the Singleton Pattern in elements of the game, such as systems, engine... in order to have only one instance of each element during the whole game.

- Message System: In order to allow systems to send events and communicate with each other, I have implemented a messaging system with events using the principle of the Observer design pattern.

Additionally, in order to avoid having to recompile the code every time changes are made to component data, I have implemented a Data Driven architecture, where the entity data is defined in .json files that the program reads when creating those entities.


Finally, there are several additional elements that I would have liked to implement but it has not been possible:

- Factory and Abstract factory design patterns: These design patterns allow to generate different families of objects through factories, with the objective of creating different elements at the level of the object.
- Builder design pattern: Through this design pattern, it would be possible to implement in an efficient, safe and scalable way different levels in the game without generating unnecessary complexity in the game.

- Sound system: Sound as a gameplay element is essential for a good gaming experience. However, not having worked with sound systems with C++, the implementation of this in the project meant a considerable increase in development time.
