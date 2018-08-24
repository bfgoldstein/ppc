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

#include "spec.hh"

// IMPLEMENTATIONS /////////////////////////////////////////////////////////////

template <typename T>
Set <T> insert (T e, Set <T> s) {
    s.insert (e) ;
    return s ;
}

template <typename T>
Bool belongs_to (T e, Set <T> s) {
    return s.find (e) != std::end (s) ;
}

SymbolString left (Production p) {
    return p.first ;
}

SymbolString right (Production p) {
    return p.second ;
}

Set <Production> productions (Grammar g) {
    return g.productions ;
}

Set <Symbol> nonterminals (Grammar g) {
    return g.nonterminals ;
}

Path derivations (Eval e) {
    return e.first ;
}

Path derivations (Stack s) {
    return s.derivations ;
}

Bool accept (Eval e) {
    return e.second ;
}

Grammar& grammar (Input& in) {
    return in.first ;
}

SymbolString& string (Input& in) {
    return in.second ;
}

String linebreak () {
    return String ("\n") ;
}

String back_trim (String s) {
    std::size_t first = std::size_t (0) ;
    std::size_t last  = s.find_last_not_of (' ') ;
    return s.substr (first, (last - first + 1)) ;
}

String to_string (SymbolString ss) {
    String x = "" ;
    for (String s : ss) {
        x += s + String (" ") ;
    }
    return back_trim (x) ;
}

SymbolString to_symbol_string (String s) {
    return split_string <SymbolString> (s) ;
}

template <typename Container>
Container split_string (String s) {
    Container c ;
    std::istringstream iss (s) ;
    std::copy
        ( std::istream_iterator <String> (iss)
        , std::istream_iterator <String> ()
        , std::inserter (c, std::begin (c)) ) ;
    return c ;
}

Pair <String, String> split_string_delim_pair (String delim, String s) {
    String::size_type pos = s.find (delim) ;
    return {s.substr (0, pos), s.substr (pos + delim.size (), s.size ())} ;
}

void print (String s) {
    std::cout << s << std::endl ;
}

String production_string (Production prod) {
    return
        to_string (left (prod))
            + " "
            + production_delim_string ()
            + " "
            + to_string (right (prod)) ;
}

String path_string (Path deriv) {
    String s ;
    for (Production p : deriv) {
        s += production_string (p) ;
        s += linebreak () ;
    }
    return s ;
}

String not_valid_string () {
    return String ("FAILED") ;
}

String valid_string () {
    return String ("SUCCESS") ;
}

String end_of_productions_string () {
    return String ("-") ;
}

String production_delim_string () {
    return String (":") ;
}

template <typename Stream>
String get_line (Stream& fin) {
    String s ;
    std::getline (fin, s) ;
    return s ;
}

template <typename Container>
Container read_set_of_symbols (String s) {
    return split_string <Set <Symbol>> (s) ;
}

Production read_production (String s) {
    Pair <String, String> ss
        = split_string_delim_pair (production_delim_string (), s) ;
    return
        Production
            ( to_symbol_string (ss.first)
            , to_symbol_string (ss.second) ) ;
}

template <typename Stream>
Set <Production> read_productions (Stream& fin) {
    Set <Production> prod ;
    String s ;
    String end_mark = end_of_productions_string () ;
    while (true) {
        s = get_line (fin) ;
        if (s == end_mark) break ;
        prod = insert (read_production (s), prod) ;
    }
    return prod ;
}

template <typename Stream>
Symbol read_start (Stream& fin) {
    Symbol sym ;
    std::istringstream (get_line (fin)) >> sym ;
    return sym ;
}

template <typename Stream>
Set <Symbol> read_nonterminals (Stream& fin) {
    return read_set_of_symbols <Set <Symbol>> (get_line (fin)) ;
}

template <typename Stream>
Set <Symbol> read_terminals (Stream& fin) {
    return read_set_of_symbols <Set <Symbol>> (get_line (fin)) ;
}

template <typename Stream>
Grammar read_grammar (Stream& fin) {
    Grammar g ;
    g.terminals    = read_terminals (fin)    ;
    g.nonterminals = read_nonterminals (fin) ;
    g.start        = read_start (fin)        ;
    g.productions  = read_productions (fin)  ;
    return g ;
}

template <typename Stream>
SymbolString read_symbol_string (Stream& fin) {
    return to_symbol_string (get_line (fin)) ;
}

template <typename Stream>
Input read_input (Stream& fin) {
    Input in ;
    string  (in) = read_symbol_string (fin) ;
    grammar (in) = read_grammar (fin) ;
    return in ;
}

String productions_string (Set <Production> sp) {
    String s ;
    for (Production p : sp) {
        s += production_string (p) ;
        s += linebreak () ;
    }
    return s ;
}

String make_output_string (Path p, Bool accept) {
    String s
        = accept ? path_string (p) + valid_string () : not_valid_string () ;
    return s ;
}

Bool is_terminal (Grammar g, Symbol s) {
    if (g.terminals.find (s) != std::end (g.terminals)) {
        return true ;
    }
    return false ;
}

Bool is_nonterminal (Grammar g, Symbol s) {
    return ! is_terminal (g, s) ;
}

Bool exists_non_terminal (Grammar g, SymbolString ss) {
    for (Symbol s : ss) if (is_nonterminal (g, s)) {
        return true ;
    }
    return false ;
}

Bool begins_with_terminal (Grammar g, SymbolString ss) {
    if (! ss.empty ()) {
        if (is_terminal (g, * std::begin (ss))) {
            return true ;
        }
    }
    return false ;
}

Symbol first_leftmost_nonterminal (Set <Symbol> n, SymbolString ss) {
    for (Symbol s : ss) {
        if (belongs_to (Symbol (s), n)) return s ;
    }
    return Symbol () ;
}

Bool left_side_equals (Production p, SymbolString l) {
    return p.first == l ;
}

Set <Production> all_productions_from_nonterminal
    ( Set <Production> lp
    , Symbol nt ) {
    Set <Production> x ;
    for (Production p : lp) {
        if (left_side_equals (p, SymbolString {nt})) x = insert (p, x) ;
    }
    return x ;
}

Bool any_empty (Stack s) {
    return s.current.empty () || s.input.empty () ;
}

SymbolString common_prefix (SymbolString a, SymbolString b) {
    // pre : assert (! empty (a) && ! empty (b)) ;
    auto miss
        = std::mismatch
            ( std::begin (a)
            , std::end   (a)
            , std::begin (b) ) ;
    return SymbolString (std::begin (a), miss.first) ;
}

SymbolString remove_prefix (SymbolString prefix, SymbolString ss) {
    ss.erase
        ( std::begin (ss)
        , std::next
            ( std::begin (ss)
            , std::min (prefix.size (), ss.size ()) ) ) ;
    return ss ;
}

Pair <SymbolString, SymbolString> eliminate_common_prefix (SymbolString a, SymbolString b) {
    SymbolString cpref = common_prefix (a, b) ;
    return
        Pair <SymbolString, SymbolString>
            (remove_prefix (cpref, a), remove_prefix (cpref, b)) ;
}

SymbolString current (Stack s) {
    return s.current ;
}

SymbolString replace_once
        ( SymbolString text
        , SymbolString old_string
        , SymbolString new_string ) {
    auto i
        = std::search
            ( std::begin (text)
            , std::end   (text)
            , std::begin (old_string)
            , std::end   (old_string) ) ;
    i = text.erase (i, std::next (i, old_string.size ())) ;
    text.insert (i, std::begin (new_string), std::end (new_string)) ;
    return text ;
}

Stack reduce (Stack s) {
    if (any_empty (s)) return s ;
    Pair <SymbolString, SymbolString> p
        = eliminate_common_prefix (s.current, s.input) ;
    s.current = p.first ;
    s.input = p.second ;
    return s ;
}

Stack expand (Stack s, Production p) {
    s.current = replace_once (current (s), left (p), right (p)) ;
    s.derivations.push_back (p) ;
    return s ;
}

Set <Stack> expand_all (Stack s, Set <Production> lp) {
    Set <Stack> stacks ;
    for (Production p : lp) {
        stacks = insert (expand (s, p), stacks) ;
    }
    return stacks ;
}

Set <Stack> all_leftmost_derivations_nonempty (Grammar g, Stack s) {
    Set <Production> lp
        = all_productions_from_nonterminal
            ( productions (g)
            , first_leftmost_nonterminal (nonterminals (g), current (s)) ) ;
    return expand_all (s, lp) ;
}

Set <Stack> all_leftmost_derivations (Grammar g, Stack s) {
    if (! exists_non_terminal (g, current (s))) return Set <Stack> () ;
    return all_leftmost_derivations_nonempty (g, s) ;
}

Eval accept_any_of (Grammar g, Set <Stack> ls) {
    // pre : assert (reduced (s)) ;
    for (Stack s : ls) {
        Eval e = parse_recursive_descent (g, s) ;
        if (accept (e)) {
            return e ;
        }
    }
    return Eval (Path (), false) ;
}

Eval accept_any_of_all_leftmost_derivations (Grammar g, Stack s) {
    // pre : assert (reduced (s)) ;
    Set <Stack> ald = all_leftmost_derivations (g, s) ;
    return accept_any_of (g, ald) ;
}

Eval parse_recursive_descent (Grammar g, Stack s) {
    s = reduce (s) ;
    if (begins_with_terminal (g, s.current)) {
        return Eval (Path (), false) ;
    }
    if (s.input.empty ()) {
        if (s.current.empty ()) {
            return Eval (derivations (s), true) ;
        }
        if (! exists_non_terminal (g, s.current)) {
            return Eval (Path (), false) ;
        }
    }
    return accept_any_of_all_leftmost_derivations (g, s) ;
}

Eval parse_recursive_descent (Grammar g, SymbolString input) {
    return
        parse_recursive_descent
            (g, Stack (SymbolString {g.start}, input, Path ())) ;
}

// MAIN ////////////////////////////////////////////////////////////////////////

int main () {
    Input in = read_input (std::cin) ;
    Eval  ev = parse_recursive_descent (grammar (in), string (in)) ;
    print (make_output_string (derivations (ev), accept (ev))) ;
    return 0 ;
}

