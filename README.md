# Tarantino++

Tarantino++ (or Tarantinopp) is a C++ reimplementation of [Tarantino](https://github.com/himanshu-dutta/tarantino) web framework. Similar to before, this is a "for learning only" implementation of a web framework.

The key idea is to learn the ins and outs of working on a C++ project. Along with learning more about working with raw TCP and Unix domain sockets, building multhithreaded applications, and more.

## Installation

The library can currently be built and used by using `CMake`. Run the following commands in order to generate the static library along with include files:

```console
$ mkdir -p build
$ cd build
$ cmake ..
$ make
```

## Running an example

After building the library along with the examples, you can run the generated executable

```console
$ ./build/example/example
```

## Running examples in `Docker`

The example can also be build and run as a docker container.

```console
$ docker compose up --build
```
