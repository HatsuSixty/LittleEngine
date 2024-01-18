littleengine_include_dir = include_directories('Include')

lib_littleengine = library('LittleEngine', [
  'Objects/Object.cpp',
  'Objects/ObjectManager.cpp',
  'Tiles/Tile.cpp',
  'Tiles/Tileset.cpp',
  'DialogBox.cpp',
  'Main.cpp',
  'Settings.cpp',
  'Util.cpp',
], include_directories : [
  littleengine_include_dir,
], dependencies : [
  dependency('raylib'),
])
