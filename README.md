[![Build Status](https://github.com/civic-fv/romp/actions/workflows/build-test.yml/badge.svg)](https://github.com/civic-fv/romp/actions/workflows/build-test.yml)

The romp [random walk] [model checker]
====================================

romp is a verification tool that uses the murphi verification language along side a
parallelized random walk of the state-space to perform verification tasks.

It utilizes libmurphi which is a custom fork of [rumur]'s librumur murphi parsing library, and CMake build system.

<!--
.. Rumur
.. =====
.. Rumur is a [model checker], a formal verification tool for proving safety and
.. security properties of systems represented as state machines. It is based on a
.. previous tool, [CMurphi], and intended to be close to a drop-in replacement.
.. Rumur takes the same input format as CMurphi, the Murphi modelling language,
.. with some extensions and generates a C program that implements a verifier.
-->


Building from Source
--------------------

First you will need to have the following dependencies installed:

* Either [GCC] or [Clang]
* [Bison]
* [CMake]
* [Flex]
* [Libgmp]
* [Python] ≥ 3.4

Then:

```sh

# Download romp
git clone https://github.com/civic-fv/romp
cd romp

# Configure and compile
cmake -B build
cmake --build build

# Generate a checker
romp my-model.m

# Compile the checker
c++ -std=c++17 -pthread -O3 -o my-model.romp my-model.romp.cpp

# Run the checker
./my-model.romp

```

Compilation produces several artifacts including the `romp` binary itself:

  * romp: Tool for translating a Murphi model into a program that implements
    a checker;;
  * libmurphi.a: A library for building your own Murphi model tools; and
  * include/murphi/: The API for the above library.

<!--
.. Comparison with CMurphi
.. -----------------------
.. If you are migrating from CMurphi, you can read a comparison between the two
.. model checkers at (doc/vs-cmurphi.rst).
-->

Tests
-----

There is [a directory](tests/) full of test models to run with the checker, accompanied by an instructional [README.md](tests/README.md)

Legal
-----

Everything in this repository is in the public domain, under the terms of
the [Unlicense]. For the full text, see [LICENSE].


[rumur]: https://github.com/smattr/rumur
[Bison]: https://www.gnu.org/software/bison/
[CMake]: https://cmake.org/
[CMurphi]: http://mclab.di.uniroma1.it/site/index.php/software/18-cmurphi
[Clang]: https://clang.llvm.org/
[Flex]: https://github.com/westes/flex
[GCC]: https://gcc.gnu.org/
[Libgmp]: https://gmplib.org/
[LICENSE]: ./LICENSE
[model checker]: https://en.wikipedia.org/wiki/Model_checking
[Python]: https://www.python.org/
[random walk]: https://en.wikipedia.org/wiki/Random_walk
[Unlicense]: http://unlicense.org/
