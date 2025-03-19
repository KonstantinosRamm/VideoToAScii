#pragma once
#include <string>


/**
 * @brief  function to calculate current pixels value and 
 * convert it into ascii character
 * @param pixelValue current pixels value
 * @param ascii_index used to check which pattern to use default = 0
 * @return character based on current pixel
 */
char pixelToAscii(int pixelValue,int ascii_index = 0);