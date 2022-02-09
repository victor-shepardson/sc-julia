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

// c++ -I/Applications/Julia-1.7.app/Contents/Resources/julia/include/julia -I/Users/victor/sc-julia/SCJulia/build/scjulia/include -fPIC -fvisibility=hidden -o test.cpp.o -c ../plugins/JuliaUGen/test.cpp -std=gnu++17 -g; c++ -o test test.cpp.o -L/Users/victor/sc-julia/SCJulia/build/scjulia/lib  -L/Users/victor/sc-julia/SCJulia/build/scjulia/lib/julia  -Wl,-rpath,/Users/victor/sc-julia/SCJulia/build/scjulia/lib -Wl,-rpath,/Users/victor/sc-julia/SCJulia/build/scjulia/lib/julia -lscjulia -ljulia; DYLD_PRINT_RPATHS=1 ./test

// c++ -I/Applications/Julia-1.7.app/Contents/Resources/julia/include/julia -I/Users/victor/sc-julia/SCJulia/build/scjulia/include -fPIC -fvisibility=hidden -o test.cpp.o -c ../plugins/JuliaUGen/test.cpp -std=gnu++17 -g; c++ -o test test.cpp.o -L/Users/victor/sc-julia/SCJulia/build/scjulia/lib  -L/Users/victor/sc-julia/SCJulia/build/scjulia/lib/julia  -Wl,-rpath,@loader_path/../SCJulia/build/scjulia/lib -Wl,-rpath,@loader_path/../SCJulia/build/scjulia/lib/julia -lscjulia -ljulia; DYLD_PRINT_RPATHS=1 ./test

// c++ -I/Applications/Julia-1.7.app/Contents/Resources/julia/include/julia -I/Users/victor/sc-julia/SCJulia/build/scjulia/include -fPIC -fvisibility=hidden -o test.cpp.o -c ../plugins/JuliaUGen/test.cpp -std=gnu++17 -g; c++ -o test test.cpp.o -Wl,-rpath,@loader_path/../SCJulia/build/scjulia/lib -Wl,-rpath,@loader_path/../SCJulia/build/scjulia/lib/julia /Users/victor/sc-julia/SCJulia/build/scjulia/lib/libscjulia.dylib /Users/victor/sc-julia/SCJulia/build/scjulia/lib/libjulia.dylib; DYLD_PRINT_RPATHS=1 DYLD_PRINT_LIBRARIES=1 ./test 2>&1