#include "Util.hpp"

#include <raylib.h>

int GetKeyStrength(int key)
{
    if (IsKeyDown(key))
        return 1;
    return 0;
}
