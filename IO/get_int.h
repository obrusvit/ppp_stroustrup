#include<iostream>
#include<string>
#include<stdexcept>

/**
 * Helper function.
 * Called by get_int if input stream fail().
 * This method discards all characters until it meets int.
 */
void skip_to_int();

/**
 * Stubbornly wait until integer is on input
 */
int get_int();

/**
 * Prompt user to enter integer.
 * 1st parameter: the message for a user.
 * 2nd parameter: the message in a case of wrong input.
 */
int get_int(const std::string& greeting, const std::string& sorry);

/**
 * Prompt user to enter integer constrained by a range (inclusive).
 * 1st parameter: the message for a user.
 * 2nd parameter: the message in a case of wrong input.
 * 3rd parameter: lower bound.
 * 4th parameter: upper bound.
 *
 */
int get_int(const std::string& greeting, const std::string& sorry,int range_low, int range_high);
