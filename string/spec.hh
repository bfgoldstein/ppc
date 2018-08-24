# pragma once

/*
 * SIMPLE PARSER ET CETERA
 *
 * license     : Creative Commons (creativecommons.org)
 * author      : Stefano Drimon Kurz Mor
 * date (v1.0) : 25/08/16
 *
 * BEWARE, the code below is not guaranteed to be, in any way,
 * - optimal (performance, memory, etc),
 * - organized,
 * - consistent,
 * - indented properly,
 * - bug-free or
 * - thoroughly tested.
 * Also, the algorithms are organized in groups by (loose) similarity.
 * Use it at your own risk.
 *
 * usage : $ ./spec
 * [input : symbol string : list]
 * {FAILED, [derivations] SUCCESS}
 */

// INCLUDES ////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// DATA TYPES //////////////////////////////////////////////////////////////////

using Bool
    = bool ;

using String
    = std::string ;

// containers ------------------------------------------------------------------

template <typename T, typename U>
using Pair
    = std::pair <T, U> ;

template <typename T>
using Set
    = std::set <T> ;

template <typename T>
using Vector
    = std::vector <T> ;

// domain ----------------------------------------------------------------------

using Symbol
    = String ;

using SymbolString
    = Vector <Symbol> ;

using Production
    = Pair <SymbolString, SymbolString> ;

using Path
    = Vector <Production> ;

// data structures -------------------------------------------------------------

struct Grammar
{

    Set <Symbol>     nonterminals ;
    Set <Symbol>     terminals    ;
    Set <Production> productions  ;
    Symbol           start        ;

    // constructor : default
    Grammar ()
        : nonterminals (Set <Symbol> ())
        , terminals    (Set <Symbol> ())
        , productions  (Set <Production> ())
        , start        (Symbol ())
    {
        ;
    }

    // constructor : components
    Grammar
        ( Set <Symbol>     nonterminals
        , Set <Symbol>     terminals
        , Set <Production> productions
        , Symbol           start )
            : nonterminals (nonterminals)
            , terminals    (terminals)
            , productions  (productions)
            , start        (start)
    {
        ;
    }

} ;

struct Stack
{

    SymbolString current     ;
    SymbolString input       ;
    Path         derivations ;

    // constructor : default
    Stack ()
        : current     (SymbolString ())
        , input       (SymbolString ())
        , derivations (Path ())
    {
        ;
    }

    // constructor : components
    Stack
        ( SymbolString current
        , SymbolString input
        , Path         derivations )
            : current     (current)
            , input       (input)
            , derivations (derivations)
    {
        ;
    }

    // partial order
    friend Bool operator < (Stack a, Stack b)
    {
        if (a.current     < b.current    ) return true  ;
        if (a.current     > b.current    ) return false ;
        if (a.input       < b.input      ) return true  ;
        if (a.input       > b.input      ) return false ;
        if (a.derivations < b.derivations) return true  ;
        if (a.derivations > b.derivations) return false ;
        return false ;
    }

} ;

// HEADERS/PROTOTYPES //////////////////////////////////////////////////////////

// I-O TYPES -------------------------------------------------------------------

using Input
    = Pair <Grammar, SymbolString> ;

using Eval
    = Pair <Path, Bool> ;

// SET ALGORITHMS --------------------------------------------------------------

template <typename T>
Bool
belongs_to (T e, Set <T> s) ;

template <typename T>
Set <T>
insert (T e, Set <T> s) ;

// DATA ACCESS ALGORITHMS ------------------------------------------------------

Bool
accept (Eval e) ;

Path
derivations (Eval e) ;

Path
derivations (Stack s) ;

Grammar&
grammar (Input& in) ;

SymbolString
left (Production p) ;

Set <Symbol>
nonterminals (Grammar g) ;

Set <Production>
productions (Grammar g) ;

SymbolString
right (Production p) ;

SymbolString&
string (Input& in) ;

// STRING ALGORITHMS -----------------------------------------------------------

String
back_trim (String s) ;

String
linebreak () ;

template <typename Container>
Container
split_string (String s) ;

Pair <String, String>
split_string_delim_pair (String delim, String s) ;

String
to_string (SymbolString ss) ;

SymbolString
to_symbol_string (String s) ;

// I/O -------------------------------------------------------------------------

String
end_of_productions_string () ;

template <typename Stream>
std::istringstream
line_as_input_string_stream (Stream& fin) ;

String
make_output_string (Path p, Bool accept) ;

String
not_valid_string () ;

String
path_string (Path deriv) ;

void
print (String s) ;

String
production_delim_string () ;

String
production_string (Production prod) ;

template <typename Stream>
Grammar
read_grammar (Stream& fin) ;

template <typename Stream>
Input
read_input (Stream& fin) ;

template <typename Stream>
Set <Symbol>
read_nonterminals (Stream& fin) ;

Production
read_production (String s) ;

template <typename Stream>
Set <Production>
read_productions (Stream& fin) ;

template <typename Container>
Container
read_set_of_symbols (std::istringstream iss) ;

template <typename Stream>
Symbol
read_start (Stream& fin) ;

template <typename Stream>
SymbolString
read_symbol_string (Stream& fin) ;

template <typename Stream>
Set <Symbol>
read_terminals (Stream& fin) ;

String
to_string (Grammar g) ;

String
valid_string () ;

// GRAMMAR ALGORITHMS ----------------------------------------------------------

Set <Production>
all_productions_from_nonterminal (Set <Production> lp, Symbol nt) ;

Bool
begins_with_terminal (Grammar g, SymbolString ss) ;

Bool
exists_non_terminal (Grammar g, SymbolString ss) ;

Symbol
first_leftmost_nonterminal (Set <Symbol> n, SymbolString ss) ;

Bool
is_nonterminal (Grammar g, Symbol s) ;

Bool
is_terminal (Grammar g, Symbol s) ;

Bool
left_side_equals (Production p, SymbolString l) ;

// STACK ALGORITHMS ------------------------------------------------------------

Stack
expand (Stack s, Production p) ;

Set <Stack>
expand_all (Stack s, Set <Production> lp) ;

Stack
reduce (Stack s) ;

// PARSING ALGORITHMS ----------------------------------------------------------

Eval
accept_any_of (Grammar g, Set <Stack> ls) ;

Eval
accept_any_of_all_leftmost_derivations (Grammar g, Stack s) ;

Set <Stack>
all_leftmost_derivations_nonempty (Grammar g, Stack s) ;

Set <Stack>
all_leftmost_derivations (Grammar g, Stack s) ;

Eval
parse_recursive_descent (Grammar g, Stack s) ;

