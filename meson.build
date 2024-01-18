project('LittleEngine', 'cpp',
        default_options : ['cpp_std=c++20',
                           'warning_level=2'])

subdir('LittleEngine')
if not meson.is_subproject()
  subdir('Example')
endif

littleengine_dep = declare_dependency(include_directories : littleengine_include_dir,
                                      link_with : littleengine)
