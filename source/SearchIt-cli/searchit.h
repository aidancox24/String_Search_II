#include <sstream>
#include <string>
#include <vector>

class SearchIt {
private:
    // The type of search (KMP or BM)
    std::string _searchType;

    // The pattern the user wants to search for
    std::string _pattern;

    // The text we will be searching within
    std::string _text;

    // Writes out the search results to a file
    std::string writeSearchResults(float duration, std::vector<int> found_patterns);

    // KMP helper function
    std::vector<int> find_shift_table();

    // BM helper function
    std::vector<int> preprocess_bad_character(std::vector<std::vector<int>> &bad_characters);

    // BM helper function
    std::vector<int> preprocess_good_suffix(std::vector<std::vector<int>> &bad_characters);

public:
    // Constructor
    SearchIt(std::string text, std::string pattern);

    // The search entry point into our search cli that initiates the search using KMP or BM
    std::string search(std::string searchType);

    // Search using the Knuth-Morris-Pratt algorithm
    std::vector<int> searchUsingKMP();

    // Search using the Boyer-Moore algorithm
    std::vector<int> searchUsingBM();
};