# Example

This is an example "Game" showing how the engine works.  

## Rough Explanation

Things like the player and stuff that requires interaction are called `Objects`. To create one, create a class that inherits from the `Object` class, and implement the necessary methods.  
After creating your objects, you can instantiate an `ObjectManager`, and call `addObject` on a pointer to an instance of an object you instantiated.  
`ObjectManager`'s constructor needs a pointer to a `Tileset` instance.  
A tileset can be created out of an array of tiles, and a tile can be created out of a color or a texture. A tileset has the minimum size of 10x10 tiles.  
After initializing everything, you can call the `update()` method on the tileset and the `ObjectManager` inside the game loop.  
**Now please fucking read [./Main.cpp](./Main.cpp) to see a practical example of everything I just wrote.**
