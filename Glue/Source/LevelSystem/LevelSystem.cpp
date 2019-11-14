#include "Glue/LevelSystem/LevelSystem.hpp"

#include <stdexcept>

namespace Glue
{

    sqlite3* LevelSystem::open_db(std::string filename)
    {
        sqlite3 *db;
        int rc = sqlite3_open(filename.c_str(), &db);

        if (rc)
        {
            throw std::runtime_error("Unable to open database.");
        }

        return db;
    }

    LevelSystem::LevelSystem(sqlite3* db)
        : props(db)
    {

    }

}