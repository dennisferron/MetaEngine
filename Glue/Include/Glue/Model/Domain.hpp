#pragma once

#include <string>

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

    Domain& merge(Subdomain targetSubdomain, Domain* sourceDomain, Subdomain sourceSubdomain);
    Domain& addObject(Subdomain subdomain, Object* newObj, Interaction* expectedInteraction);
    void checkInteraction(Interaction* expectedInteraction, Subdomain subdomain, Object* newObj);
    Object* findObject(Subdomain subdomain, Type* objProto);
};

}
