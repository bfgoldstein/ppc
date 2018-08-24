#include <algorithm>
#include <iostream>
#include <set>
#include <string>

using String = std::string ;

template<typename T>
using Set = std::set <T> ;

inline auto
read_string_from_standard_input () -> String
{
    String s ;
    std::cin >> s ;
    return s ;
}

auto
all_permutations (String s) -> Set <String>
{
    std::sort (s.begin (), s.end ()) ;
    Set <String> x ;
    do {
        x.insert (s) ;
    } while (std::next_permutation (s.begin (), s.end ())) ;
    return x ;
}

template <typename N> inline auto
write_number_and_break (N n) -> void
{
    std::cout << std::size_t (n) << std::endl ;
}

inline auto
write_strings (const Set <String>& ss) -> void
{
    for (String s : ss) {
        std::cout << s << std::endl ;
    }
}

int main (int argc, char const* argv[])
{
    // s = 720 for the contest
    String s = read_string_from_standard_input () ;
    Set <String> ss = all_permutations (s) ;
    write_number_and_break (ss.size ()) ;
    write_strings (ss) ;
    return 0 ;
}

