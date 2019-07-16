#pragma once

#include <iostream>

//#define DBG

#ifdef DBG

    #define DBG_PRINT \
    std::cout << "\n DBG print: " << __FUNCSIG__ << " (line: " << __LINE__ << ")";

#else 
    #define DBG_PRINT

#endif 
