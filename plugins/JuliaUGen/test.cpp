#include "test.hpp"
#include <iostream>

using namespace std;

int main (int argc, char** argv){
    // std::cout << argc;
    // for(int i=0; i<argc; i++) std::cout << argv[i];
    int argc_ = 1;
    const char* arg = "";
    char** argv_ = const_cast<char**>(&arg);
    init_julia(argc_, argv_);

    cout << "julia initialized\n";

    // float* workspace = (float*)malloc(3*sizeof(float));
    // workspace[1] = 0.5;
    // step_fn_t step = setup(workspace, 3);
    scjulia_setup();

    cout << "gc disabled\n";

    float* phase = (float*)malloc(sizeof(float));
    *phase = 0.0f;
    struct SCJuliaState state = {phase};

    cout << "state struct created\n";

    for (int i=0; i<8; i++)
        cout << scjulia_step(state, 0.5, 0.5) << "\n";

    cout << "...\n";
    for (int i=0; i<100000000; i++){
        scjulia_step(state, 0.5, 0.5);
    }

    for (int i=0; i<8; i++)
        cout << scjulia_step(state, 0.5, 0.5) << "\n";

    shutdown_julia(0);

    cout << "julia shut down\n";

    return 0;
}

// simple test file for debugging without scsynth involved

// c++ -I/Applications/Julia-1.7.app/Contents/Resources/julia/include/julia -I/Users/victor/sc-julia/SCJulia/build/scjulia/include -fPIC -fvisibility=hidden -o test.cpp.o -c ../plugins/JuliaUGen/test.cpp -std=gnu++17 -g; c++ -o test test.cpp.o -L/Users/victor/sc-julia/SCJulia/build/scjulia/lib  -L/Users/victor/sc-julia/SCJulia/build/scjulia/lib/julia  -Wl,-rpath,/Users/victor/sc-julia/SCJulia/build/scjulia/lib -Wl,-rpath,/Users/victor/sc-julia/SCJulia/build/scjulia/lib/julia -lscjulia -ljulia; DYLD_PRINT_RPATHS=1 ./test

// c++ -I/Applications/Julia-1.7.app/Contents/Resources/julia/include/julia -I/Users/victor/sc-julia/SCJulia/build/scjulia/include -fPIC -fvisibility=hidden -o test.cpp.o -c ../plugins/JuliaUGen/test.cpp -std=gnu++17 -g; c++ -o test test.cpp.o -L/Users/victor/sc-julia/SCJulia/build/scjulia/lib  -L/Users/victor/sc-julia/SCJulia/build/scjulia/lib/julia  -Wl,-rpath,@loader_path/../SCJulia/build/scjulia/lib -Wl,-rpath,@loader_path/../SCJulia/build/scjulia/lib/julia -lscjulia -ljulia; DYLD_PRINT_RPATHS=1 ./test

// c++ -I/Applications/Julia-1.7.app/Contents/Resources/julia/include/julia -I/Users/victor/sc-julia/SCJulia/build/scjulia/include -fPIC -fvisibility=hidden -o test.cpp.o -c ../plugins/JuliaUGen/test.cpp -std=gnu++17 -g; c++ -o test test.cpp.o -Wl,-rpath,@loader_path/../SCJulia/build/scjulia/lib -Wl,-rpath,@loader_path/../SCJulia/build/scjulia/lib/julia /Users/victor/sc-julia/SCJulia/build/scjulia/lib/libscjulia.dylib /Users/victor/sc-julia/SCJulia/build/scjulia/lib/libjulia.dylib; DYLD_PRINT_RPATHS=1 DYLD_PRINT_LIBRARIES=1 ./test 2>&1