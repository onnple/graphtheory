cmake_minimum_required(VERSION 3.14)
project(graphtheory C)

set(CMAKE_C_STANDARD 99)

add_executable(graphtheory main.c densegraph.c densegraph.h queue.c queue.h sparsegraph.c sparsegraph.h list.c list.h cyclegraph.c cyclegraph.h disjset.c disjset.h graph.c graph.h binaryheap.c binaryheap.h)