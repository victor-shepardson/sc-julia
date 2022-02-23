module SCJulia

# NOTE: seems like all deps should be explicit,
# and in pacakge dependencies, even if they are
# available in a defualt REPL, e.g. `rand`
using Random, StaticArrays

export setup

# want to do allocation in the cpp host using RTAlloc.
# so julia code should use preallocation,
# and the host should pass in pointers to workspace

# three ways to manage state
# =============================================================================

# option A
# keep state in a C struct, and pass it as the first argument to a global step function
# setup is only needed to disable GC

struct State
    phase::MVector{1, Cfloat}
end

@Base.ccallable function scjulia_step(s::State, in::Cfloat, gain::Cfloat)::Cfloat
    s.phase .+= 0.01f0
    s.phase .%= 1
    ϕ = SVector{1}(s.phase)
    (in + sum(sinpi.(2ϕ))) * gain
end

Base.@ccallable function scjulia_setup()::Cvoid
    GC.enable(false)
    nothing
end

# =============================================================================

# option B
# keep all state in a callable State object,
# and return its call function to C

# struct State
#     phase::MVector{1, Cfloat}
# end

# function (s::State)(in::Cfloat, gain::Cfloat)::Cfloat
#     s.phase .+= 0.01f0
#     s.phase .%= 1
#     ϕ = SVector{1}(s.phase)
#     (in + sum(sinpi.(2ϕ))) * gain
# end

# Base.@ccallable function setup(workspace::Ptr{Cfloat}, size::Csize_t)::Ptr{Cvoid}
#     GC.enable(false)

#     # RTAlloc'd workspace
#     step = State(MVector{1}(unsafe_wrap(Array{Cfloat}, workspace, 1)))

#     # return a C function pointer
#     # still a closure, still leaking memory...
#     @cfunction($step, Cfloat, (Cfloat, Cfloat)).ptr
# end

# =============================================================================

# option C
# close over state, defining step inside of setup
# pass step back to C as a function pointer

# signature of step depends only on UGen input/output signature this way

# note: this is cute but apparently ARM does not support closing over cfunctions

# hmm, for multiple outputs, return a C struct? C++ tuple?
# or pass in pointers to output locations and return nothing?

#  @cfunction doesn't like this but could use a macro I think
# const step_return_t = Cfloat
# const step_args_t = (Cfloat, Cfloat)

# there may be insurmountable performance problems with using a closure?
# https://docs.julialang.org/en/v1/manual/performance-tips/#man-performance-captured

# Base.@ccallable function setup(workspace::Ptr{Cfloat}, size::Csize_t)::Ptr{Cvoid}
#     GC.enable(false)

#     # state is closed over
#     w = unsafe_wrap(Array{Cfloat}, workspace, size) # RTAlloc'd workspace
#     phase::Cfloat = 0f0 # stack allocated (?) state

#     function step(in::Cfloat, gain::Cfloat)::Cfloat
#         phase = (phase + w[2])%1
#         (in + rand(Cfloat)*2-1 + sinpi(2phase)) * gain
#     end

#     # return a C function pointer
#     @cfunction($step, Cfloat, (Cfloat, Cfloat)).ptr
# end

end

