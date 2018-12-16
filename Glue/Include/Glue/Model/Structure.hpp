#pragma once

#include <iostream>

namespace Glue {

    // Structure Description Language -
    // This Io DSL allows you to specify nested, hierarchical
    // compound structures of 3d objects.  Example:
    // myStructure := Structure build(
    //      headStyle neckJoint bodyStyle(
    //          leftShoulder armStyle, rightShoulder armStyle, leftHip legStyle, rightHip legStyle
    //      ) tailJoint tailStyle
    // )
    //
    // Simple juxtaposition indicates connections should be made; messages with parenthesis indicate one or more substructures
    // to attach.  The joins are the union of the argument list and the atom following it, so the
    // following two forms result in the same structure:
    //      head(leftEye, rightEye)
    //      head(leftEye) rightEye
    // It does matter though if anything further is following the last atom.  The following two are NOT the same:
    //      head(leftEye, rightEye) neck  // a head with two eyes on a neck
    //      head(leftEye) rightEye neck  // a head with one eye, attached to another eye and that eye has a neck.

    // TODO:  Make this work without needing to be a template.
    class Structure
    {

    };

//    template <typename T, typename... As>
//    class Structure
//    {
//    private:
//        T root;
//        std::tuple<As...> attachments;
//
//    public:
//
//        Structure(T& root, As&... attachments);
//
//        friend std::ostream& operator <<(std::ostream& os, Structure<T, As...> const& s)
//        {
//            return os << s << "(" << s.attachments << ")";
//        }
//
//        Structure<T, As...> move(Scalar x, Scalar y, Scalar z) const
//        {
//            throw "Not implemented.";
//            //return Structure(root.move(x,y,z), attachments.move(x,y,z)...);
//        }
//    };
}
