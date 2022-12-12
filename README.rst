romp
====
romp is a verification tool that uses the murphi verification language along side a 
parallelized random walk of the state-space to perform verification tasks.

It utilizes libmurphi which is a custom fork of rumur_'s librumur murphi parsing library, and CMake build system.

.. Rumur
.. =====
.. Rumur is a `model checker`_, a formal verification tool for proving safety and
.. security properties of systems represented as state machines. It is based on a
.. previous tool, CMurphi_, and intended to be close to a drop-in replacement.
.. Rumur takes the same input format as CMurphi, the Murphi modelling language,
.. with some extensions and generates a C program that implements a verifier.


Building from Source
~~~~~~~~~~~~~~~~~~~~
First you will need to have the following dependencies installed:

* Either GCC_ or Clang_
* Bison_
* CMake_
* Flex_
* Libgmp_
* Python_ ≥ 3.4

Then:

.. code-block:: sh

  # Download romp
  git clone https://github.com/civic-fv/romp
  cd romp

  # Configure and compile
  mkdir build
  cd build
  cmake ..
  make
  make install

  # Generate a checker
  romp my-model.m

  # Compile the checker
  cc -std=c++17 -pthread -O3 -o my-model.romp my-model.romp.cpp

  # Run the checker
  ./a.out

Compilation produces several artifacts including the `romp` binary itself:

* romp: Tool for translating a Murphi model into a program that implements
  a checker;;
* libmurphi.a: A library for building your own Murphi model tools; and
* include/murphi/: The API for the above library.

.. Comparison with CMurphi
.. -----------------------
.. If you are migrating from CMurphi, you can read a comparison between the two
.. model checkers at `doc/vs-cmurphi.rst`_.

.. _doc/vs-cmurphi.rst: doc/vs-cmurphi.rst

Tests
-----
There is a directory (tests/) full of test models to run with the checker, accompanied by an instructional README.md

Legal
-----
Everything in this repository is in the public domain, under the terms of
`the Unlicense`_. For the full text, see LICENSE_.

.. _rumur: https://github.com/smattr/rumur
.. _Bison: https://www.gnu.org/software/bison/
.. _CMake: https://cmake.org/
.. _CMurphi: http://mclab.di.uniroma1.it/site/index.php/software/18-cmurphi
.. _Clang: https://clang.llvm.org/
.. _Flex: https://github.com/westes/flex
.. _GCC: https://gcc.gnu.org/
.. _Libgmp: https://gmplib.org/
.. _LICENSE: ./LICENSE
.. _`model checker`: https://en.wikipedia.org/wiki/Model_checking
.. _Python: https://www.python.org/
.. _`the Unlicense`: http://unlicense.org/
