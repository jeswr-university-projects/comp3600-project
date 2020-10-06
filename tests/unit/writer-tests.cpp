// TODO: Actually write the fuckers

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

// int main(int argc, char *argv[])
// {
//     Triples triples = {
//         {"http://example.org/Alice", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org/human"},
//         {"http://example.org/Alice", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org/agent"},
//         {"http://example.org/Alice", "http://example.org/alive", "\"true\""},
//         {"http://example.org/Bob", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org/human"},
//         {"http://example.org/Bob", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org/agent"},
//         {"http://example.org/Bob", "http://example.org/alive", "\"true\""},
//         {"http://test.org/Bob", "http://example.org/alive", "\"true\""},
//     };

//     map<string, string> prefixes = {
//         {"ex", "http://example.org/"}};

//     writeTriples(triples, prefixes, "test-write.ttl");

//     return 0;
// };