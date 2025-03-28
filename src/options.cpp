#include "options.hpp"



int strToInteger(const std::string& str)
{
    try{
        //return str to integer if succeeded
        return std::stoi(str);
    }
    //invalid number
    catch (const std::invalid_argument& e){
    
            std::cerr << e.what();
    }//overflow or underflow
    catch (const std::out_of_range& e){
    
        std::cerr << e.what();
    }//handle any undecpected exception
    catch (const std::exception& e){
    
        std::cerr << e.what();
    }


    //return 0 in case of failure to convert str to 0 (dafault argument)
    return 0;
}

