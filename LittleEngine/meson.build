littleengine_include_dir = include_directories('Include')

littleengine = library('LittleEngine', [
  'Objects/ObjectManager.cpp',
  'Objects/Object.cpp',
  'Tiles/Tile.cpp',
  'Tiles/Tileset.cpp',
  'Main.cpp',
  'Util.cpp',
], include_directories : [
  littleengine_include_dir,
], dependencies : [
  dependency('raylib'),
])
