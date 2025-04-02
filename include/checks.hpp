#pragma once
#include <string>
#include <limits>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>


/**
 * @brief checks if argument passed to argv is valid integer 
 * @param str string to be passed and converted to int
 * @return the string converted to integer as int
 */
int strToInteger(const std::string& str);
