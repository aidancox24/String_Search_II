#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "searchit.h"

/**
 * Constructor for the SearchIt class
 * @param textFile
 * @param pattern
 *
 * Implementation written by Aidan Cox
 */
SearchIt::SearchIt(std::string text, std::string pattern) {
    // Keep track of the text we want to search through
    _text = text;

    // Keep track of the pattern to search for
    _pattern = pattern;
}

/**
 * The search entry point into our search cli.
 *
 * Implementation written by Aidan Cox
 */
std::string SearchIt::search(std::string searchType) {
    // Keep track of the indices of the matched patterns
    std::vector<int> found_patterns;

    // Use the clock, so we can determine how long the search routine takes
    long start = std::clock();

    // Determining which search algorithm to use
    if (searchType == "KMP") {
        // Let's use the Knuth-Morris-Pratt search algorithm
        _searchType = "KMP";
        found_patterns = searchUsingKMP();
    } else if (searchType == "BM") {
        // Let's use the Boyer-Moore search algorithm
        _searchType = "BM";
        found_patterns = searchUsingBM();
    } else {
        std::cout << searchType
                  << " is not a supported search type.  \n\nSupported search types are 'KMP' and 'BM'.\n\nSee "
                     "searchit.exe -help for details.";
        return "";
    }

    // At this point the search is complete and found_patterns has the search results

    // End the clock so can calculate how long the search took
    long end = std::clock();
    float duration = 1.0 * (end - start) / CLOCKS_PER_SEC;

    // Write out the search results to the search results file
    std::string searchResults = writeSearchResults(duration, found_patterns);

    // Also display the search results to the console
    std::cout << searchResults << "\n";

    return searchResults;
}

/**
 * Write a summary of the search results to a file.
 *
 * Implementation written by Aidan Cox
 */
std::string SearchIt::writeSearchResults(float duration, std::vector<int> found_patterns) {
    // Create the name of the file we are about to write for the search results
    // Example: AABA-SEARCH-RESULTS-KMP.txt
    std::string resultsSummaryFileName = _pattern + "-SEARCH-RESULTS-" + _searchType + ".txt";

    // Create a string stream to write our search results to - We'll write this out to a file later
    std::stringstream searchResultsStream;

    // Add some summary text to our results summary stream
    if (_searchType == "KMP") {
        searchResultsStream << "\n* * * Knuth Morris Pratt Search Algorithm * * *\n\n";
    } else {
        searchResultsStream << "\n* * * Boyer Moore Search Algorithm * * *\n\n";
    }

    // Add some results information to our searchResultsStream
    searchResultsStream << std::fixed << std::setprecision(4) << "Search Duration:      " << duration
                        << " milliseconds\n";
    searchResultsStream << "Search Pattern:       " << _pattern << "\n";
    searchResultsStream << "Search Results File:  " << resultsSummaryFileName << "\n";
    searchResultsStream << "Search Results:\t" << "\n";

    // Indicate the number of matches
    if (found_patterns.empty()) {
        // Indicate we found no matches
        searchResultsStream << "\tNo matches found for '" << _pattern << "'\n";
    } else {
        // Append the matches results to the results summary stream
        for (int i = 0; i < found_patterns.size(); i++) {
            searchResultsStream << "\t\"" << _pattern << "\" found at index " << found_patterns[i] << '\n';
        }
    }

    // Open the summary results file, so we can write out a summary of search results
    std::fstream resultsSummaryOutFile;
    resultsSummaryOutFile.open(resultsSummaryFileName, std::ios::out);

    // Write the summary data to the summary file
    resultsSummaryOutFile << searchResultsStream.str();

    // Close our summary file
    resultsSummaryOutFile.close();

    // Return the search summary results as a string
    return searchResultsStream.str();
}

/**
 * Shows the command line usage for our SearchIt cli
 *
 * Implementation written by Aidan Cox
 */
void showUsage() {
    std::cout << "Usage: \n";
    std::cout << "\tsearchit.exe [searchType] [searchPattern] [text | fileName -file] \n\n";
    std::cout << "\tArguments:\n";
    std::cout << "\t\t[searchType] - KMP (Knuth-Morris-Pratt) or BM (Boyer-Moore)\n";
    std::cout << "\t\t[searchPattern] - text pattern to search\n";
    std::cout << "\t\t[text | fileName -file] - text or a filename that has text (use -file when specifying a "
                 "                                                                  filename)\n\n";
    std::cout << "\tExamples:\n";
    std::cout << "\t\t# Use the KMP algorithm to search for 'AABA' in the text 'ABCAABACDBABABABBA'\n";
    std::cout << "\t\tsearch.exe KMP AABA ABCAABACDBABABABBA\n\n";
    std::cout << "\t\t# Use the BM algorithm to search for 'AABA' in the file sample.txt'\n";
    std::cout << "\t\tsearch.exe KMP AABA sample.txt -file\n\n";
}

/**
 * The main entry into our search cli application.
 *
 * Implementation written by Aidan Cox
 */
int main(int argc, char *argv[]) {
    // Check if we should show the command usage help if no arguments are provided
    if (argc < 2) {
        showUsage();
        return -1;
    }

    // Make sure we have the correct number of arguments otherwise show the usage help
    if (argc > 5 || argc < 4) {
        std::cout << "Invalid arguments.\n\n";
        showUsage();
        return -1;
    }

    // Get the pattern
    std::string pattern = argv[2];

    // The text we want to search for - the user can specify the actual text OR a file name which has the text in it
    std::string text;

    // Determine if the user gave us text or a text file to search
    if (argc > 4 && std::string(argv[4]) == "-file") {
        // The user wants to search for text from a text file... Let's load the file
        std::string textFileName = std::string(argv[3]);
        std::fstream infile;
        infile.open(textFileName, std::ios::in);

        if (infile.is_open()) {
            std::string line;

            // Loop through the text file and read it in line by line
            while (getline(infile, line)) {
                text.append(line);
            }

            // Close the file
            infile.close();

        } else {
            // Problem opening the file
            std::cerr << "Could not load the text file: " << textFileName << "\n";
            return -1;
        }

    } else {
        // The user gave us text on the command line, lets use it
        text = argv[3];
    }

    // Get the search algorithm to use (KMP or BM)
    std::string searchType = std::string(argv[1]);

    // Create an instance of our SearchIt class which has the search algorithm implementation
    SearchIt searchIt(text, pattern);

    // Initiate the search
    searchIt.search(searchType);

    return 0;
}

/**
 * Knuth-Morris-Pratt (KMP)
 * KMP search, using the table of shift values
 * @return vector of ints representing indices of matches
 *
 * Knuth-Morris-Pratt implementation written by Nicholas Mendes
 */
std::vector<int> SearchIt::searchUsingKMP() {
    // Vector of indexes that match the pattern, the pattern and text indexes are initialized
    std::vector<int> found_patterns;
    int pattern_index = 0;
    int text_index = 0;

    std::vector<int> shift_table = find_shift_table();

    // Run until there are no more characters to check
    while (text_index < _text.size()) {
        // If there is a match, increment the indexes
        if (_pattern[pattern_index] == _text[text_index]) {
            text_index++;
            pattern_index++;
        }

        // If the pattern index makes it past the pattern without an encountering a mismatch, push the index of the text
        // Into the vector and reset the index
        if (pattern_index == _pattern.size()) {
            found_patterns.push_back(text_index - _pattern.size());
            pattern_index = shift_table[pattern_index - 1];
            // If a mismatch occurs, then either reset the pattern index if the mismatch occurred anywhere but the first
            // Character or increment the text index if the mismatch is on the first character
        } else if (_pattern[pattern_index] != _text[text_index]) {
            if (pattern_index) {
                pattern_index = shift_table[pattern_index - 1];
            } else {
                text_index++;
            }
        }
    }

    // Return the vector of indexes
    return found_patterns;
}

/**
 * KMP helper function.
 *
 * Function to create a table of values to replace the index of the pattern when a mismatch occurs
 *
 * The value contained in the indexes represents where the text should be shifted to at the last matched character
 *
 * Knuth-Morris-Pratt implementation written by Nicholas Mendes
*/
std::vector<int> SearchIt::find_shift_table() {
    // Initialize a vector of indexes to return
    std::vector<int> shift_table;
    shift_table.push_back(0); // If the mismatch is at the first character, nothing should change (placeholder)

    // Initialize the shift and the size of the prefix to be the first two characters, making the prefix substring
    int shift;
    int prefix_size = 2;
    std::string prefix = _pattern.substr(0, prefix_size);

    // Run so long as the prefix is not bigger than the pattern
    while (prefix_size <= _pattern.size()) {
        shift = 0; // Set the shift to 0
        int pre_start = 0; // Index where the prefix of the prefix starts
        int pre_size = 1; // Number of characters in the prefix of the prefix
        int suf_start = prefix.size() - 1; // Index where the suffix should begin

        // Run while the suffix of the prefix does not include the first character
        while (suf_start > 0) {
            // Make substrings to hold the prefix and suffix of the prefix
            std::string temp_prefix = prefix.substr(pre_start, pre_size);
            std::string temp_suffix = prefix.substr(suf_start);

            // If the strings are equivalent, set the shift to the number of characters in the matching strings
            if (temp_prefix == temp_suffix) {
                shift = temp_prefix.size();
            }

            // Increase the size of the prefix and suffix sizes
            pre_size++;
            suf_start--;
        }
        // Add the shift to the table, increase the size of the prefix, then reset the prefix based on the new size
        shift_table.push_back(shift);
        prefix_size++;
        prefix = _pattern.substr(0, prefix_size);
    }
    // Return the table of indexes
    return shift_table;
}

/**
 * Boyer-Moore (BM)
 *
 * Boyer Moore implementation written by Nicholas Mendes
 */
std::vector<int> SearchIt::searchUsingBM() {
    std::vector<std::vector<int>> indexes; // Creates table of indexes for preprocessing
    std::vector<int> bad_char = preprocess_bad_character(indexes); // Finds the bad_character table
    std::vector<int> good_suf = preprocess_good_suffix(indexes); // Finds the good suffix table
    std::vector<int> found_patterns; // Vector to be returned of indexes

    // Initialize both string indices to be the furthest right index of the pattern
    int text_index = _pattern.size() - 1;
    int pattern_index = _pattern.size() - 1;

    // Run until there are no more valid indexes to check
    while (text_index <= _text.size() - _pattern.size()) {
        // store old index for reassignment latter
        int origin = text_index;

        // Until there is a mismatch or either index goes less than 0, decrease both indices
        while ((pattern_index >= 0 || text_index >= 0) && _pattern[pattern_index] == _text[text_index]) {
            pattern_index--;
            text_index--;
        }

        // If a pattern is found (index = -1), add the text index, then reset the index to be one to the right of the
        // pattern
        if (pattern_index < 0) {
            found_patterns.push_back(text_index + 1);
            text_index = origin + 1;
            // If no pattern is found, find the appropriate shift from each table and then add the largest to the index
            // of the text
        } else {
            int bad_char_shift = bad_char[static_cast<int>(_text[text_index])];
            int good_suf_shift = good_suf[_pattern.size() - pattern_index - 1];
            if (good_suf_shift >= bad_char_shift) {
                text_index += good_suf_shift;
            } else {
                text_index += bad_char_shift;
            }
        }
        // Reset pattern_index to right most index
        pattern_index = _pattern.size() - 1;
    }

//    // Write out the results to the search results file
//    std::string results = writeSearchResults(duration, found_patterns);

    // Return string of found patterns
    return found_patterns;
}

/**
 * BM helper function.
 *
 * Bad Character Heuristic:
 *
 * If there is a mismatch, check if the mismatched character in the text exists further left in the pattern.
 *
 * If it exists, shift the pattern so the character in the text lines up with the one in the pattern.
 *
 * If it does not exist, shift the pattern past the character in the text.
 *
 * Boyer Moore implementation written by Nicholas Mendes
*/

std::vector<int> SearchIt::preprocess_bad_character(std::vector<std::vector<int>> &bad_characters) {
    int alphabet_size = 256; // Set alphabet to 256 (size of extended ASCII alphabet)
    int most_recent_idx; // Index for both tables

    std::vector<int> bad_character_table; // 1D table of shift values

    for (int i = 0; i < alphabet_size; i++) { // Run for the size of the alphabet
        // Reset the index to -1
        most_recent_idx = -1;

        // Row for the 2D table
        std::vector<int> row_for_table;

        for (int j = 0; j < _pattern.size(); j++) { // Run for the size of the pattern
            // If the character exists in the pattern, replace the most recent index for j
            if (i == static_cast<int>(_pattern[j])) {
                most_recent_idx = j;
            }
            // Push the most recent index into the row
            row_for_table.push_back(most_recent_idx);
        }
        // Push the row into the 2D table and the left most index into the table
        bad_characters.push_back(row_for_table);
        bad_character_table.push_back(_pattern.size() - most_recent_idx - 1);
    }
    // Return the table
    return bad_character_table;
}

/**
 * BM helper function
 *
 * Good Suffix Heuristic:
 *
 * If there exists a mismatch, check to see if the characters to the right of the mismatched character exist
 * elsewhere in the string.
 *
 * If the suffix exists elsewhere and the character to the left does not match in both substrings or the suffix
 * exists as a prefix, shift the pattern so the substring that matched lines up with the part of the string.
 *
 * If the suffix does not exist elsewhere in the string, shift the pattern past the mismatched character
 *
 * Boyer Moore implementation written by Nicholas Mendes
*/
std::vector<int> SearchIt::preprocess_good_suffix(std::vector<std::vector<int>> &bad_characters) {
    std::vector<int> good_suffixes; // Vector to hold the shift values of the different
    std::string suffix; // String to hold the suffix of the pattern

    int last_index = _pattern.size() - 1; // Initialize last index to be furthest right index
    int next_index; // Index for potential patterns

    bool found; // Boolean for if a pattern has been found

    // Until the left most character does not match the last character, add the character to the front of the string
    while (last_index >= 0 && _pattern[last_index - 1] == _pattern[last_index]) {
        last_index--;
    }

    suffix = _pattern.substr(last_index);

    // Add the size of the initial suffix to the vector of shift values
    for (int i = 0; i < suffix.size(); i++) {
        good_suffixes.push_back(suffix.size());
    }

    // Run until you reach index 0
    while (last_index > 0) {
        // Set next index to the closest leftmost index where the first character in the suffix matches
        next_index = bad_characters[static_cast<int>(suffix[0])][last_index - 1];
        found = false; // Set found to false

        // Run until either the index is <= 0 or the suffix is found elsewhere in the string
        while (next_index > 0 && !found) {
            // Create a substring that is the same size as the suffix, staring at the next leftmost index
            std::string possible_suffix_loc = _pattern.substr(next_index, suffix.size());

            // If the suffix matches with this substring of the pattern and the next character to the left does not
            // Match, add the shift to the vector and set found to true;
            if (possible_suffix_loc == suffix && _pattern[next_index - 1] != _pattern[last_index - 1]) {
                good_suffixes.push_back(last_index - next_index + suffix.size()); // Shift is the distance between the
                // Two matching indices plus the size of the suffix
                found = true;
            } else {
                // If the above conditions fail, reset next_index and try again
                next_index = bad_characters[static_cast<int>(suffix[0])][next_index - 1];
            }
        }
        // If it is at the end of the string, a substring has not been found yet, and the suffix matches the prefix,
        // Push the size of the pattern as the shift
        if (next_index == 0 && (suffix == _pattern.substr(0, suffix.size())) && !found) {
            good_suffixes.push_back(_pattern.size());
            // If it does not fit the prefix, check if the suffixes of the suffix match the prefix of the string
        } else if (!found) {
            int shift = 0;
            for (int i = 1; i < suffix.size(); i++) {
                // If a match is found, store the number of characters skipped, set found to true, then break
                std::string suf_of_suf = suffix.substr(i);
                if (suf_of_suf == _pattern.substr(0, suf_of_suf.size())) {
                    shift = i;
                    found = true;
                    break;
                }
            }

            // If a suffix of the suffix was found, set the shift to the size of the pattern plus the number of
            // Characters skipped in the suffix
            if (found) {
                good_suffixes.push_back(_pattern.size() + shift);
            } else {
                // If nothing was found, set the shift to be the size of the pattern plus the size of the suffix
                // (shift all the way past the mismatch)
                good_suffixes.push_back(_pattern.size() + suffix.size());
            }
        }
        // Add the character to the left into the suffix and decrement last index
        last_index--;
        suffix = _pattern.substr(last_index);
    }
    return good_suffixes;
}