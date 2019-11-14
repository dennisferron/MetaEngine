#include "boost/test/unit_test.hpp"
#include "Glue/Model/Graph.hpp"
#include "MockComponents.hpp"
#include "Glue/LevelSystem/LevelSystem.hpp"

#include <string>

using namespace Glue;

BOOST_AUTO_TEST_SUITE(ComponentsTests)

BOOST_AUTO_TEST_CASE(test_level_system)
{
    std::string conn_str = R"(C:\Users\dferr\MetaEngine\Data\Props.sqlite)";
    sqlite3* db = LevelSystem::open_db(conn_str);
    LevelSystem lvl_sys(db);
}

BOOST_AUTO_TEST_SUITE_END()