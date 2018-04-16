#include <vector>

/*

template <typename T>
class var
{
};

template <typename T>
class vars
{
};

template <typename T>
class assume
{
};

class Style
{
};

class Attribute
{
};

class AttributeInteraction
{
    virtual var<bool> operator()(vars<Attribute> attrs) const
    {
        return var<bool>();
    }
};

class Configuration
{
    vars<AttributeInteraction> possible_interactions;
};

class Entity
{
    var<Style> style;
    vars<Attribute> attrs;

public:
    Entity(var<Style> style, var<Attribute> attrs)
        : style(style), attrs(attrs)
    {
    }

    auto operator()(auto cont) const
    {
        return cont(style, attrs);
    }
};

class Component
{
public:
    virtual var<Attribute> get_attr(var<Style> style) const
    {
        return var<Attribute>();
    }
};

class Engine
{
    vars<Component> components;
    vars<Entity> entities;
    vars<AttributeInteraction> poss_inter;
public:
    auto operator()()
    {
        assume<Component> comp <<= components;
        assume<Entity> ent <<= entities;
        ent->attrs >>= comp->get_attr(ent->style);
    }
};

class EngineRules
{
private:
    var<Engine> engine;
    var<Component> component;
    var<Entity> entity;
    var<Style> style;
    var<Attribute> attribute;
    var<AttributeInteraction> attr_inter;

    auto engine_component(subs<EngineRules> sb)
    {
        return sb[engine][component];
    }

    auto engine_entity(subs<EngineRules> sb)
    {
        return composition(sb,
        {
            engine,
            {
                entity { style }
            }
        });
    }

    auto entity_attribute(subs<EngineRules> sb)
    {
        return sb[entity].has_many(sb[attribute]);
    }

    auto entity_style(subs<EngineRules> sb)
    {
    }

    auto component_attribute(subs<EngineRules> sb)
    {
        auto make_attr = [](Component const& cmp_inst, Style const& style)
            { return cmp_inst.make_attr(style); };

        return (sb[component] * sb[entity]) >> call(make_attr, component, style);
    }

    auto attribute_interaction(subs<EngineRules> s0)
    {
        auto s1 = entity_attribute(s0);
        return posb_interaction(s1[entity],
                                s1[attribute][0],
                                s1[attribute][1]);
    }
};

void do_test()
{

}

*/
