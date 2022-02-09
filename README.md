# JuliaUGen

Author: Victor Shepardson

proof-of-concept SuperCollider+Julia integration.

Currently tested against MacOS 10.14.6, Supercollider 3.13.0-dev, Julia 1.7.1

### Requirements

- CMake >= 3.5
- SuperCollider source code
- Julia >= 1.7.1

### Building

For macOS x64

Build Julia
(it ought to work with the official release but there is some esoteric linking problem):

    git clone https://github.com/JuliaLang/julia
    cd julia
    git checkout v1.7.1
    make
    ln -s julia /usr/local/bin/julia
    cd ..

Clone the project:

    git clone https://github.com/victor-shepardson/sc-julia

CMake will build the Julia package, then the SuperCollider extension:

    cd sc-julia
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=RelWithDebugSymbols
    cmake --build . --config Release

Finally, link `sc-julia` into your SuperCollider extensions directory. The `install` 
target is not set up yet.

<!--
TODO: install target
    cmake --build . --config Release --target install

You may want to manually specify the install location in the first step to point it at your
SuperCollider extensions directory: add the option `-DCMAKE_INSTALL_PREFIX=/path/to/extensions`.
-->

It's expected that the SuperCollider repo is cloned at `../supercollider` relative to this repo. If
it's not: add the option `-DSC_PATH=/path/to/sc/source`.

The julia executable should be linked to a default system location so it can be invoked as `julia`
or `julia-debug` (in the latter case supply `-DJULIA=julia-debug` to CMake)

### Developing

Use the command in `regenerate` to update CMakeLists.txt when you add or remove files
 from the
project. You don't need to run it if you only change the contents of existing files. You may need to
edit the command if you add, remove, or rename plugins, to match the new plugin paths. Run the 
script with `--help` to see all available options.

### Known Issues / Caveats

- Currently works with locally built version of Julia only. 
- Probably not compatible with any other SC plugins which attempt to use Julia!
