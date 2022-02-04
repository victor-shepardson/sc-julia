module SCJulia

# NOTE: seems like all deps should be explicit,
# and in pacakge dependencies, even if they are
# available in a defualt REPL, e.g. `rand`
using Random

export whitenoise

# function noise(gain)
#     return (rand(typeof(gain))*2-1) * gain;
# end

Base.@ccallable function whitenoise(gain::Cfloat)::Cfloat
    # return noise(gain)
    return (rand(Cfloat)*2-1) * gain;
end

end