#ifndef __ALGORITHMS_HH_
#define __ALGORITHMS_HH_

// std
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>

// local
#include "types.hh"

template <typename N>
Set<Vertex> build_vertex_set (N n)
{
    Set<Vertex> x ;
    while (n) {
        x.insert (n --) ;
    }
    return x ;
}

template <typename N, typename M>
Set<Edge> build_random_edge_set (N n, M m)
{
    Set<Edge> e ;
    for (N i = N (1) ; i <= n ; ++ i) {
        for (N j = N (1) ; j <= m ; ++ j) {
            N x ;
            do { x = (N (rand ()) % n) + N (1) ; } while (x == i) ;
            e.insert (Edge (std::min (i, x), std::max (i, x))) ;
        }
    }
    return e ;
}

Graph read_graph ()
{
    std::size_t nv, ne ;
    std::cin >> nv >> ne ;
    Graph g ;
    g.v = build_vertex_set (nv) ;
    while (ne --) {
        Edge i ;
        std::cin >> i.first >> i.second ;
        g.e.insert (i) ;
    }
    return g ;
}

Set<Vertex> read_vertex_set ()
{
    Set<Vertex> v ;
    for (Vertex x ; std::cin >> x ; ) {
        v.insert (x) ;
    }
    return v ;
}

template <typename S> inline
void set_difference (S& x, const S& y) {
    for (const auto& i : y) {
        x.erase (i) ;
    }
    return ;
}

template <typename S> inline
void set_union (S& x, const S& y) {
    for (const auto& i : y) {
        x.insert (i) ;
    }
    return ;
}

void exclude_neighbors (Set<Vertex>& v, const Graph& g) {
    for (Vertex i : v) for (Vertex j : v) {
        if (g.are_neighbors (i, j)) {
            v.erase (i) ;
        }
    }
    return ;
}

Set<Vertex> neighbors (const Vertex& x, const Graph& g) {
    Set<Vertex> v ;
    for (Edge i : g.e) {
        if (i.first == x) {
            v.insert (i.second) ;
        }
        if (i.second == x) {
            v.insert (i.first) ;
        }
    }
    return v ;
}

Set<Vertex> neighbors (const Set<Vertex>& v, const Graph& g) {
    Set<Vertex> x ;
    for (Vertex i : v) {
        set_union (x, neighbors (i, g)) ;
    }
    return x ;
}

// selects node with probability 1/2^n
// using a uniformly random generated natural m
template <typename N, typename M> inline
bool try_select (N n, M m)
{
    return (m % (N (1) << n)) + N (1) <= N (1) ;
}

// randomly select a subset of vertexes
// selection probability 1/2^i for vertex of degree i
template <typename RandGenerator>
void rand_select (Set<Vertex>& u, const Set<Vertex>& v, const Graph& g, RandGenerator& r) {
    // constant-time clear of u (STL method is linear time)
    Set<Vertex> x ;
    x.swap (u) ;
    for (Vertex i : v) {
        if (try_select (g.degree (i), r ())) {
            u.insert (i) ;
        }
    }
    return ;
}

#endif /* end of include guard: __ALGORITHMS_HH_ */

