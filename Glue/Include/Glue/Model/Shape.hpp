#include "Glue/Model/ModelInterfaces.hpp"

namespace Glue
{
    class Shape : public IShape
    {
    private:
        ShapeStyle style;
        //ShapeInteractions interactions;
        std::vector<ShapeAttribute*> attributes;

    public:
        Shape(ShapeStyle const& style);

        ShapeStyle const& get_style() const final;

        void addAttribute(ShapeAttribute* attr) final;
        std::vector<ShapeAttribute*> const& get_attributes() const final;
    };
}
