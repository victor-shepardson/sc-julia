// Julia headers (for initialization and gc commands)
#include "uv.h"
#include "julia.h"

// prototype of the C entry points in our application
// extern "C" float whitenoise(float);

// typedef float (*step_fn_t)(float, float);
// extern "C" step_fn_t setup(float* w, size_t s);

struct SCJuliaState {
    float* phase;
};

extern "C" float scjulia_step(SCJuliaState, float, float);
extern "C" void scjulia_setup();