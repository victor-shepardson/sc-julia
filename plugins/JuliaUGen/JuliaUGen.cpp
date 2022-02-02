// PluginJuliaUGen.cpp
// Victor Shepardson (victor.shepardson@gmail.com)

#include "SC_PlugIn.hpp"
#include "JuliaUGen.hpp"

static InterfaceTable* ft;

namespace JuliaUGen {

JuliaUGen::JuliaUGen() {
    mCalcFunc = make_calc_function<JuliaUGen, &JuliaUGen::next>();
    next(1);
}

void JuliaUGen::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace JuliaUGen

PluginLoad(JuliaUGenUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<JuliaUGen::JuliaUGen>(ft, "JuliaUGen", false);
}
