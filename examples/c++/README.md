## C++ Concurrency Primitive Examples

## Building

Making use of _[CMAKE](https://cmake.org/cmake/help/latest/)_, _[CTEST](https://cmake.org/cmake/help/latest/manual/ctest.1.html)_ in the build system.

Before building the test executable ensure you have _initialised all_ `.gitmodules` via:

```bash
git submodule update --init
```

### Dependencies

- _[GoogleTest](https://github.com/google/googletest)_
- _[pthreads](https://man7.org/linux/man-pages/man7/pthreads.7.html)_

### Quickstart

The following [guide](http://google.github.io/googletest/quickstart-cmake.html) is very helpful to get up and running. The following commands can be used on a _\*UNIX_ system to build the test executables.

```bash
# build the build system
mkdir -p build
cmake -S . -B build

# compile & link executables
cmake --build build

# run executables (tests)
cd build
ctest
```


## FAQ

#### How can I get verbose stdout output when running `ctest`?

Specifically to get the print information to `stdout` you can use the following command

```bash
ctest --verbose
```