//#include <functional>
//#include <stdexcept>
//#include <string>
//#include <vector>
//#include <tuple>
//#include <iostream>
//#include <bitset>
//
//#include "mpark/variant.hpp"
//
//namespace fngl {
//
//struct SearchTree;
//struct Gamma;
//
//struct Deferred
//{
//    std::function<SearchTree(Gamma)> get;
//};
//
//struct Lattice
//{
//    std::vector<SearchTree> terms;
//};
//
//struct Branch
//{
//    std::vector<SearchTree> terms;
//
//    Branch() : terms() {}
//    Branch(std::vector<SearchTree> terms) : terms(terms) {}
//};
//
//struct SearchTree
//{
//    mpark::variant<Deferred, Lattice, Branch> value;
//};
//
//template <typename... Ts>
//auto search_branch(Ts... terms)
//{
//    return Branch
//    {
//        std::vector<SearchTree>
//        {
//            SearchTree {Ts}...
//        }
//    };
//}
//
//template <typename... Ts>
//auto search_lattice(Ts... terms)
//{
//    return Lattice
//    {
//        std::vector<SearchTree>
//        {
//            SearchTree {Ts}...
//        }
//    };
//}
//
//SearchTree success()
//{
//    return Lattice {{}};
//}
//
//SearchTree failure()
//{
//    return Branch {{}};
//}
//
//void test_it()
//{
//    auto tb = branch(
//        [](Gamma){ return success(); },
//        [](Gamma){ return success(); },
//        [](Gamma){ return failure(); }
//     );
//}
//
//}
