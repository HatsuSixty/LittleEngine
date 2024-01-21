# Documentation

**Warning: This is not full documentation, please also read [Example/Main.cpp](../Example/Main.cpp).**

## Objects

Things like the player and stuff that requires interaction are called `Objects`. To create one, create a class that inherits from the `Object` class, and implement the necessary methods.  
After creating your objects, you can instantiate an `ObjectManager`, and call `addObject` on a pointer to an instance of an object you instantiated.  
`ObjectManager`'s constructor needs a pointer to a `Tileset` instance.  
Call `ObjectManager`'s `update()` method on your game loop to update the objects.

## Tilesets

A tileset can be created out of an array of tiles, and a tile can be created out of a color or a texture. A tileset has the minimum size of 10x10 tiles.  
Call `Tileset`'s `update()` method on your game loop to update the tiles.

## Dialog boxes

To use dialog boxes, instantiate a `DialogBox` outside the loop, call `update()` inside the gameloop, and call `start()` to actually use it to display something.

## Translations

To use translations, call `Translation::getText()` on a string to get the translated version of that string. If no translation exists for that string, the original string is returned.  
To load a translation file, use `Translation::loadTranslation()` and give a file path as parameter. The translation file must be in the format `hello=olá=` (the `=` in the end of the line is mandatory).

## Utilities

The engine also comes with some utilities for updating the camera and getting input.

- `GetInputStrength(KeyboardKey key)` - Returns 1 if the key is pressed, and 0 if the key is not pressed.
- `scrollCameraWithPlayer(Camera2D* camera, Object* player, Tileset* tileset)` - Updates the specified camera based on the position of the given player and the dimensions of the provided tileset.
