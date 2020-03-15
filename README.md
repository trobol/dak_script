# GOALS
## Primary

* A scripting language that allows smooth development of components (mainly for games), blending the performance and ease of large systems development wi

* Allow for data oriented programming without some of the hassles that come along with that. e.g. buffer creation/management, filter and aggregate


* Promote/advise developer with best practices, with code analysis and with full benchmark/cache miss analysis

* Allow simple separation of concerns.

* Compilation to machine code with LLVM as a dynamic library.

* Relatively easy swap out of user generated (dak_script) library at runtime.

* Easily add functions to the scripting language while using this library

* Mimic functional languages, and be statically typed

## Secondary

* Gain familiarity with the inner workings of programming languages.

* Gain familiarity with testing frameworks & test driven design.

# MVP
* Component creation.
    * Parse files
    * Lexer
    * Tokenizer
* Component Definition Sharing
* Parser "API" 
    * static (non dll) functions
    * component functions that will be used by the program they are linked with (e.g. `update`, `onStart`)
* (user defined POD members)

# TECHNICAL STACK


* cpp
* [LLVM](https://llvm.org) (script compilation)
* [Catch2](https://github.com/catchorg/Catch2) (testing)
* CMake

