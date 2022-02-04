// PluginJuliaUGen.hpp
// Victor Shepardson (victor.shepardson@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

extern "C" {
    #include "julia_init.h"
}
#include "scjulia.h"

namespace JuliaUGen {

bool JULIA_INIT = false;

class JuliaUGen : public SCUnit {
public:
    JuliaUGen();

    // Destructor
    ~JuliaUGen();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace JuliaUGen
