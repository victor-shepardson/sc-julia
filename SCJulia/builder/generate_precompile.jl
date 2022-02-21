using SCJulia, StaticArrays

# SCJulia.whitenoise(Cfloat(0.5))

# SCJulia.setup()

# w_size = Csize_t(3);
# w = ones(Cfloat, w_size)
# step = SCJulia.setup(pointer(w), w_size)
# ccall(step, Cfloat, (Cfloat, Cfloat), Cfloat(0.5), Cfloat(0.5))

SCJulia.scjulia_setup()

state = SCJulia.State(MVector{1}([rand(Cfloat)]))
SCJulia.scjulia_step(state, rand(Cfloat), rand(Cfloat))