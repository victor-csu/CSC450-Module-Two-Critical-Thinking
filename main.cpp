/*
 * Program: Create a simple C++ console application
 * that will write a program that will take two string inputs from a user.
 * Your program should concatenate the two strings and then print the resulting output to the screen.
 * Take the two string inputs from the user 3 times for varying string lengths.
 */

#include <iostream>
#include <string>
#include <regex>

using namespace std::regex_constants;

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::string;
using std::to_string;
using std::tolower;
using std::transform;
using std::regex;
using std::regex_replace;
using std::regex_match;
using std::runtime_error;

/*
 * str_tolower
 * converts a string to lowercase
 * avoids mutating original string
 * returns the lowercase string
 */
string str_tolower(const string& value)
{
    string s;

    s.assign(value);

    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); }
    );

    return s;
}

/*
 * str_trim
 * trims the leading and trailing whitespaces in a string
 * avoids mutating original string
 * returns the trimmed string
 */
string str_trim(const string& value) {
    string s;

    s.assign(value);

    return regex_replace(
            regex_replace(s, regex( "^\\s+$" ), ""),
            regex( "\\s+$" ),
            ""
    );
}

/*
 * get_string_input
 * asks a user to enter a string
 * recursive
 *
 * returns the input string
 */
string get_string_input(const string& instruction, int max_length = 50) {
    try {
        cout << instruction;

        string input;

        getline(cin, input);

        string trimmed_input = str_trim(input);

        if (trimmed_input.empty()) {
            throw runtime_error(string("Input length must be greater than 1\n"));
        } else if (trimmed_input.length() > max_length) {
            throw runtime_error(string("Input length must be less than " + to_string(max_length) + "\n"));
        }

        return trimmed_input;
    } catch (const runtime_error& error) {
        cout << error.what();

        return get_string_input(instruction);
    }
}

/*
 * get_two_string_input
 * collects a string input twice using the get_string_input method
 *
 * returns a space separated concatenation of the two user input
 */
string get_two_string_input(int max_length = 50) {
    string max_length_string = to_string(max_length);
    string first_input(get_string_input("Enter a string(character length between 1 and " + max_length_string + "): ", max_length));
    string second_input(get_string_input("Enter another string(character length between 1 and " + max_length_string + "): ", max_length));

    return first_input + " " + second_input + "\n";
}

int main() {
    cout << "Collecting Two Inputs(First Batch)" << endl;

    string first_batch = get_two_string_input();

    cout << first_batch << endl;

    cout << "Collecting Two Inputs(Second Batch)" << endl;

    string second_batch = get_two_string_input(20);

    cout << second_batch << endl;

    cout << "Collecting Two Inputs(Third Batch)" << endl;

    string third_batch = get_two_string_input(10);

    cout << third_batch << endl;

    return 0;
}
