#include "Glue/Model/ModelInterfaces.hpp"

namespace Glue
{
    class Shape
    {
    private:
        ShapeStyle style;
        //ShapeInteractions interactions;
        std::vector<ShapeAttribute*> attributes;

    public:
        Shape(ShapeStyle const& style);

        ShapeStyle const& get_style() const;

        void addAttribute(ShapeAttribute* attr);
        std::vector<ShapeAttribute*> const& get_attributes() const;
    };
}
