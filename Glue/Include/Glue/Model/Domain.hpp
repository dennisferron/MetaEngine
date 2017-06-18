#pragma once

namespace Glue {

class Object;
class Type;
class Interaction;
class Site;

class Domain
{
private:
    std::map<Domain*, Object*> activeObjects;
    std::vector<Interaction*> activeInteractions;

    Site* site ::= nil

public:

    Domain& merge(Domain* targetSubdomain, Domain* sourceDomain, Domain* sourceSubdomain);
    Domain& addObject(Domain* subdomain, Object* newObj, Interaction* expectedInteraction);
    void checkInteraction(Interaction* expectedInteraction, Domain* subdomain, Object* newObj);
    Object* findObject(Domain* subdomain, Type* objProto);
};

}
