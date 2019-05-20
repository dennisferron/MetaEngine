#pragma once

#include <string>
#include <map>
#include <vector>

namespace Glue {

class Object;
class Type;
class Interaction;
class Site;

using Subdomain = std::string;

class Domain
{
private:
    std::map<Subdomain, Object*> activeObjects;
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
