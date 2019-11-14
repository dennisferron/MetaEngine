#pragma once

#include "LevelEditor.hpp"
#include "Props.hpp"
#include "Tile.hpp"
#include "Terrain.hpp"

#include "sqlite3.h"

namespace Glue {

    class LevelSystem
    {
    private:
        Props props;

    public:
        static sqlite3* open_db(std::string conn_str);
        LevelSystem(sqlite3* db);
    };

}