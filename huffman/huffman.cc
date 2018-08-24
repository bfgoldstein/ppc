// HUFFMAN CODING
// @author Stefano Drimon Kurz Mor

#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

using Size   = std::size_t ;
using Symbol = std::string ;
using Weight = std::size_t ;
using Code   = std::string ;

using String
    = std::string ;

template <typename T>
using Greater
    = std::greater <T> ;

template <typename T>
using Vector
    = std::vector <T> ;

template <typename T1, typename T2>
using Map
    = std::map <T1, T2> ;

template <typename T>
using PriorityQueue
    = std::priority_queue
        < T
        , Vector  <T>
        , Greater <T>
        > ;

class HuffmanTree
{

    enum { left = 0, right = 1 } ;

    public :

    Weight weight = Weight {0} ;
    Symbol symbol = Symbol { } ;

    Vector <HuffmanTree> children ;

    /// regular type ///

    // default constructor
    HuffmanTree () { }

    // copy constructor
    HuffmanTree (const HuffmanTree& e) {
        symbol   = e.symbol   ;
        weight   = e.weight   ;
        children = e.children ;
    }

    // assignment operator
    HuffmanTree& operator= (const HuffmanTree& e) {
        symbol   = e.symbol   ;
        weight   = e.weight   ;
        children = e.children ;
        return *this ;
    }

    /// binary tree ///

    // leaf constructor
    HuffmanTree (Symbol s, Weight w) {
        symbol = s ;
        weight = w ;
    }

    // merge constructor
    HuffmanTree (HuffmanTree a, HuffmanTree b) {
        weight = a.weight + b.weight ;
        children.push_back (a) ; children.push_back (b) ;
        symbol = a.symbol + b.symbol ;
    }

    HuffmanTree left_subtree  () { return children[left ]   ; }
    HuffmanTree right_subtree () { return children[right]   ; }
    bool        is_leaf       () { return children.empty () ; }

    /// totally ordered ///

    friend bool operator== (HuffmanTree a, HuffmanTree b) {
        return a.symbol == b.symbol && a.weight == b.weight ;
    }

    friend bool operator< (HuffmanTree a, HuffmanTree b) {
        return a.weight == b.weight ? a.symbol < b.symbol : a.weight < b.weight ;
    }

    friend bool operator> (HuffmanTree a, HuffmanTree b) {
        return b < a ;
    }

    friend bool operator<= (HuffmanTree a, HuffmanTree b) {
        return ! (a > b) ;
    }

    friend bool operator>= (HuffmanTree a, HuffmanTree b) {
        return ! (a < b) ;
    }

} ;

HuffmanTree extract (PriorityQueue <HuffmanTree>& p)
{
    HuffmanTree r ;
    r = p.top () ;
    p.pop () ;
    return r ;
}

// depth-first binary tree walk
// appends to each leaf's code:
// bit 0 for each left side on the path
// bit 1 for each right side on the path
Map <Symbol, Code> walk
        ( HuffmanTree        h
        , Code               c = Code ()
        , Map <Symbol, Code> m = Map <Symbol, Code> () )
{
    if (h.is_leaf ()) {
        m.insert ({h.symbol, c}) ;
        return m ;
    }
    m = walk (h.left_subtree  (), c + Code ("0"), m) ;
    m = walk (h.right_subtree (), c + Code ("1"), m) ;
    return m ;
}


void print_queue(PriorityQueue <HuffmanTree> q) {
  while(!q.empty()) {
    std::cout << q.top().symbol<<":"<< q.top().weight << " ";
    q.pop();
  }
  std::cout << '\n';
}


// builds a (min) priority queue
// from entries in map of symbols and weights
// (each element is a leaf-only Huffman tree)
PriorityQueue <HuffmanTree> make_queue
        (Map <Symbol, Weight> m)
{
    PriorityQueue <HuffmanTree> q ;
    for (auto i : m) {
        q.push (HuffmanTree (i.first, i.second)) ;
    }
    return q ;
}

// main algorithm
// assembles the prefix tree of codes
HuffmanTree huffman (Map <Symbol, Weight> m)
{
    assert (! m.empty ()) ; // precondition
    PriorityQueue <HuffmanTree> p = make_queue (m) ;
    HuffmanTree a ;
    HuffmanTree b ;
    do {
        a = extract (p) ;
        if (p.empty ( )) break ;
        b = extract (p) ;
        p.push (HuffmanTree (a, b)) ;
    } while (true) ;
    return a ;
}

// writes output to given stream
// prints each symbol and its
// associated weight and prefix code
template <typename OutStream>
int write
        ( OutStream&           out
        , Map <Symbol, Weight> w
        , Map <Symbol, Code  > c )
{
    for (auto i : w) {
        out << i.first    ;
        out << " "        ;
        out << i.second   ;
        out << " "        ;
        out << c[i.first] ;
        out << std::endl  ;
    }
    return 0 ;
}

// returns true if element
// pointed by iterator i
// is inside the container m
template <typename I, typename M>
bool found (I i, const M& m)
{
    return i != std::end (m) ;
}

// inserts on the given map
// a new symbol with weight 1
// or increments the weight
// if the symbol is already
// in the map
template <typename Pair>
Map <Symbol, Weight> insert_or_add
        ( Map <Symbol, Weight> m
        , Pair                 p )
{
    auto i = m.find (p.first) ;
    if (found (i, m))
        i -> second += p.second ;
    else
        m.insert (p) ;
    return m ;
}

// union of two maps a and b
// all symbols in a remain
// all symbols in b and not in a are added
// all symbols in both are replaced
// by the same symbol with added weights
Map <Symbol, Weight> map_weighted_union
    ( Map <Symbol, Weight> a
    , Map <Symbol, Weight> b )
{
    for (auto e : b) {
        a = insert_or_add (a, e) ;
    }
    return a ;
}

// reads a line as a string from a stream
template <typename InStream>
String read_line (InStream& in)
{
    String s ;
    std::getline (in, s) ;
    return s ;
}

// convert read character to proper symbol
Symbol to_symbol (char c)
{
    if (c == ' ') return Symbol ("space") ;
    return Symbol ({c}) ;
}

// inserts on the given map
// a new symbol with weight 1
// or increments the weight
// if the symbol is already
// in the map
Map <Symbol, Weight> insert_or_increment
        ( Map <Symbol, Weight> m
        , Symbol               s )
{
    auto i = m.find (s) ;
    if (found (i, m))
        ++ (i -> second) ;
    else
        m.insert ({s, Weight (1)}) ;
    return m ;
}

// reads a line of text
// extracts the symbols and weights
// returns a map of symbols and weights
template <typename InStream>
Map <Symbol, Weight> read_entry (InStream& in)
{
    Map <Symbol, Weight> m ;
    for (char c : read_line (in)) {
        m = insert_or_increment (m, to_symbol (c)) ;
    }
    return m ;
}

// reads the number of lines
// being read as input
template <typename InStream>
Size read_number_of_entries (InStream& in)
{
    String n ;
    std::getline (in, n) ;
    return Size (std::stoll (n)) ;
}

// reads the input from a stream
template <typename InStream>
Map <Symbol, Weight> read (InStream& in)
{
    Map <Symbol, Weight> m ;
    Size n = read_number_of_entries (in) ;
    while (n --)
        m = map_weighted_union (m, read_entry (in)) ;
    return m ;
}

int main (int argc, char const* argv[])
{
    Map <Symbol, Weight> weights = read    (std::cin) ;
    HuffmanTree          prefix  = huffman (weights)  ;
    Map <Symbol, Code>   codes   = walk    (prefix)   ;
    return write (std::cout, weights, codes) ;
}

