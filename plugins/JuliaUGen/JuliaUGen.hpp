// PluginJuliaUGen.hpp
// Victor Shepardson (victor.shepardson@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

extern "C" {
    #include "julia_init.h"
}
#include "scjulia.h"

namespace JuliaUGen {

//global flag for whether Julia runtime needs init
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
    SCJuliaState state;
    // Julia step function
    // step_fn_t step;

};

} // namespace JuliaUGen
