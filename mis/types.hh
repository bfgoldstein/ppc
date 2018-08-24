#ifndef __TYPES_HH_
#define __TYPES_HH_

// std
#include <cstddef>
#include <set>
#include <utility>

#define Set    std::set
#define Vertex std::size_t
#define Edge   std::pair<Vertex, Vertex>

// data structures

struct Graph {

    Set<Vertex> v ;
    Set<Edge>   e ;

    // default constructor
    Graph () {} ;

    // copy constructor
    Graph (const Graph& x) : v (x.v), e (x.e) { } ;

    // assignment
    Graph& operator= (const Graph& x) {
        this->~Graph () ;
        new (this) Graph (x) ;
        return *this ;
    } ;

    // equality comparison
    friend
        bool operator== (const Graph& x, const Graph& y) {
            return (x.v == y.v) && (x.e == y.e) ;
        } ;

    // inequality comparison
    friend
        bool operator!= (const Graph& x, const Graph& y) {
            return ! (x == y) ;
        } ;

    // vertex degree
    std::size_t degree (Vertex i) const
    {
        std::size_t n = 0 ;
        for (const Edge& p : e) {
            if (p.first  == i || p.second == i) ++ n ;
        }
        return n ;
    }

    // vertex degree
    bool are_neighbors (Vertex x, Vertex y) const
    {
        Vertex a = std::min (x, y) ;
        Vertex b = std::max (x, y) ;
        if (e.find (Edge (a, b)) != e.end ()) return true ;
        return false ;
    }

} ;

#endif /* end of include guard: __TYPES_HH_ */

