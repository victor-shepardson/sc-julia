#include "test.hpp"
#include <iostream>

int main (int argc, char** argv){
    // std::cout << argc;
    // for(int i=0; i<argc; i++) std::cout << argv[i];
    int argc_ = 1;
    const char* arg = "";
    char** argv_ = const_cast<char**>(&arg);
    init_julia(argc_, argv_);

    std::cout << whitenoise(0.5f);
    
    shutdown_julia(0);
    return 0;
}

// simple test file for debugging without scsynth involved

// c++ -I/Applications/Julia-1.7.app/Contents/Resources/julia/include/julia -I/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/include -fPIC -fvisibility=hidden -o test.cpp.o -c ../plugins/JuliaUGen/test.cpp -std=gnu++17 -g; c++ -o test test.cpp.o -L/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/lib  -L/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/lib/julia  -Wl,-rpath,/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/lib -Wl,-rpath,/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/lib/julia -lscjulia -ljulia; ./test

//julia-debug:
// c++ -I/Users/victor/julia/usr/include/julia -I/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/include -fPIC -fvisibility=hidden -o test.cpp.o -c ../plugins/JuliaUGen/test.cpp -std=gnu++17 -g; c++ -o test test.cpp.o -L/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/lib  -L/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/lib/julia  -Wl,-rpath,/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/lib -Wl,-rpath,/Users/victor/sc-julia/SCJulia/scjulia-0.1.0/scjulia/lib/julia -lscjulia -ljulia-debug; ./test