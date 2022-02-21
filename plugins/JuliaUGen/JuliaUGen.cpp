// PluginJuliaUGen.cpp
// Victor Shepardson (victor.shepardson@gmail.com)
// #include "julia_init.h"
#include "SC_PlugIn.hpp"
#include "JuliaUGen.hpp"

static InterfaceTable* ft;

namespace JuliaUGen {

JuliaUGen::JuliaUGen() {
    // the first Julia UGen created will block scsynth here:
    if (!JULIA_INIT) {
        int argc_ = 1;
        const char* arg = "";
        char** argv_ = const_cast<char**>(&arg);
        init_julia(argc_, argv_);
        JULIA_INIT = true;
    }

    // RTalloc workspace to send to Julia
    // const size_t w_size = 3;
    // float* workspace = (float*)RTAlloc(this->mWorld, w_size*sizeof(float));
    // memset(workspace, 0.0f, w_size*sizeof(float));

    // workspace[1] = 0.01;
    // sample-wise step function is returned from Julia as a function pointer
    // step = setup(workspace, w_size);

    float* phase = (float*)RTAlloc(this->mWorld, sizeof(float));
    state = {phase};

    scjulia_setup();

    mCalcFunc = make_calc_function<JuliaUGen, &JuliaUGen::next>();
    next(1);
}

JuliaUGen::~JuliaUGen() {

}

void JuliaUGen::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        // outbuf[i] = (*step)(input[i], gain[i]);
        outbuf[i] = scjulia_step(state, input[i], gain[i]);
    }
}

} // namespace JuliaUGen

// try to clean up Julia runtime
// not sure this is correct
C_LINKAGE SC_API_EXPORT void unload(InterfaceTable* inTable) {
     if (JuliaUGen::JULIA_INIT){
        shutdown_julia(0);
        JuliaUGen::JULIA_INIT = false;
     }
}

PluginLoad(JuliaUGenUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<JuliaUGen::JuliaUGen>(ft, "JuliaUGen", false);
}