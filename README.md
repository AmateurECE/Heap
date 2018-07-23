## A Heap for C Programs ##

This repository contains an implementation of a Heap, written in C, with a very
simple API. The Heap implementation is contained in the file `heap.c` and
`heap.h` contains the necessary type definitions and prototypes. The file
`test-heap.c` contains test code. Test cases are thoroughly commented.

## Features ##

The implementation is contained solely in the file `heap.c`. The `Makefile` is
not meant to be portable, however, it is so simple that it ought to work on
any POSIX system. None of the components have been tested on any version of
Windows.

## Min Heap or Max Heap ##

The library allows the user to configure the heap as a Max Heap or a Min Heap
at creation time, via the `createMax()` and `createMin()` functions. After
creation, Max Heaps and Min Heaps interface to the library in the same way, and
are handled accordingly internally.

## Implementation Sans Heap ##

The implementation contains a version which will not utilize the program heap
(by not calling `malloc` and `free`). This is especially helpful on embedded
systems. If the macro `CONFIG_NO_HEAP` is defined, this version of the library
will be compiled in. The reader may note the irony in not using a heap in a
heap implementation. As long as the user utilizes the library correctly, they
will not experience memory leaks. The test cases in `test-heap.c` have been
utilized to test for memory leaks caused by the implementation. None were
found. Valgrind v3.13.0 was used.

## The Heap API ##

The Heap API is very standard, and should be familiar to anyone who has used a
heap before. Simplicity was favored over feature. Below is a brief description
of the API.

Some of the descriptions below note operations on the 'minimum' element in a
Heap. It is assumed that if the Heap is a Max Heap, these operations will work
on the 'maximum' element of the Heap.

`void * Heap_peek(Heap * heap)`

Return the minimum element of the Heap, without destroying the element. The
data will remain in the Heap after the call returns.

`int Heap_push(Heap * heap, void * data)`

Insert a new element into the Heap. If the Heap becomes unbalanced after
insertion, the Heap will be rebalanced. The argument `data` is a pointer to the
user's data which will be inserted into the Heap.

`int Heap_pop(Heap * heap, void ** data)`

Return the minimum element of the Heap, removing the element from the Heap in
the process. The reference `data` is a pointer to a receptacle where the user's
data will be placed upon successful completion of this call.

`Heap * Heap_createMin(void (*destroy)(void *),
int (*compare)(void *, void *))`

`int Heap_createMin(Heap * heap, void (*destroy)(void *),
int (*compare)(void *, void *), size_t len, void * (*workspace)[len])`

Create an empty Min Heap. If an error occurs during the call, `NULL` is
returned. The argument `destroy` is a pointer to a function which frees user
data when it is no longer necessary. It takes a pointer to the user data. The
function `compare` compares two user data (passed as arguments), returning -1
if the first is greater, 0 if they are the same, and 1 if the second is
greater. The second prototype will only be compiled if `CONFIG_NO_HEAP` is
defined at compilation time.

`Heap * Heap_createMax(void (*destroy)(void *),
int (*compare)(void *, void *))`

`int Heap_createMax(Heap * heap, void (*destroy)(void *),
int (*compare)(void *, void *), size_t len, void * (*workspace)[len])`

Create an empty Max Heap. If an error occurs during the call, `NULL` is
returned. The argument `destroy` is a pointer to a function which frees user
data when it is no longer necessary. It takes a pointer to the user data. The
function `compare` compares two user data (passed as arguments), returning -1
if the first is greater, 0 if they are the same, and 1 if the second is
greater. The second prototype will only be compiled if `CONFIG_NO_HEAP` is
defined at compilation time.

`void Heap_destroy(Heap * heap)`

Destroys the heap pointed to. This function frees all internally allocated
memory (if using the Heap) and, if the member `destroy` is non-null, it is
called on every user datum in the Heap.

`Heap * Heap_heapify(size_t len, void * (*array)[len], enum Config config)`

Create a new Heap from the array `array`. The parameter `config` is one of two
values defined in `enum Status`. The choices are `HEAP_MAX` and `HEAP_MIN`.
These correspond to creation of a Max Heap and Min Heap, respectively.

`int Heap_size(Heap * heap)`

This is a macro which expands to access of the Heap's size parameter, which is
of type `int`.

`int Heap_isEmpty(Heap * heap)`

This is a macro which expands to `(int)0` if the Heap is empty, and `(int)1`
otherwise.
