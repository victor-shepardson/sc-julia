
# MIT License

# Copyright (c) 2020-2021, Simon Byrne, Kevin Squire, Nikhil Mitra

# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

import PackageCompiler, TOML

if length(ARGS) < 1 || length(ARGS) > 2
    println("Usage: julia $PROGRAM_FILE lib_name [major|minor]")
    println()
    println("where:")
    println("    lib_name is the name (excluding 'lib' prefix) of the library bundle")
    println("    [major|minor] is the (optional) compatibility version (default: major).")         
    println("    Use 'minor' if you use new/non-backwards-compatible functionality.")
    println()
    println("    [major|minor] is only useful on OSX.")
    exit(1)
end

const build_dir = @__DIR__
const lib_name = ARGS[1]
const project_toml = realpath(joinpath(build_dir, "..", "Project.toml"))
const version = VersionNumber(TOML.parsefile(project_toml)["version"])

const compatibility = length(ARGS) == 2 ? ARGS[2] : "major"

PackageCompiler.create_library(".", string("build/", lib_name);
    lib_name=lib_name,
    precompile_execution_file=[joinpath(build_dir, "generate_precompile.jl")],
    precompile_statements_file=[joinpath(build_dir, "additional_precompile.jl")],
    incremental=false,
    filter_stdlibs=true,
    header_files=[joinpath(build_dir, "scjulia.h")],
    force=true,
    # version=version,
    compat_level=compatibility,
    sysimage_build_args=`-g 2 -O0 -t 4`
)