#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>

namespace Glue {

using Object = void;
class Type;
class Interaction;
class Site;

class Domain
{
private:
    std::map<std::string, std::set<void*>> activeObjects;
    std::vector<Interaction*> activeInteractions;

    Site* site;

public:

    Domain();
    Domain& merge(Domain* targetSubdomain, Domain* sourceDomain, Domain* sourceSubdomain);
    Domain& addObject(char const* subdomain, void* newObj);
    //void checkInteraction(Interaction* expectedInteraction, Domain* subdomain, Object* newObj);
    Object* findObject(Domain* subdomain, Type* objProto);
};

}
