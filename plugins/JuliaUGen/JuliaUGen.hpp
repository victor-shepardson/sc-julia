// PluginJuliaUGen.hpp
// Victor Shepardson (victor.shepardson@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace JuliaUGen {

class JuliaUGen : public SCUnit {
public:
    JuliaUGen();

    // Destructor
    // ~JuliaUGen();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace JuliaUGen
