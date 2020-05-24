# Overview

The code is organised as follows.
[main.cpp] is the main program, from which options are executed.

# Options
* `default` Default option; essentially a script
* `test` Another script option
* `k_blin_maker` Same as crepes, but using a fixed number of generators
* `crepes` Generating coset representatives for a subgroup of Gamma
* `adj_liszt` Computing adjacency lists for an arithmetic cover of the starting manifold
* `guacomology` Computing the homology of a graph (WIP)
* `magma_convexion` Converting magma formatted file to C++ readable file
* `variants` Computing invariants of a graph (WIP)
* `pp` Printing in Perseus readable format
* `lest_mod3` List the elements of a given data file that are the identity mod 3
* `volution` Volume computation (WIP)

## Option files

* `magma_parser.*`
* `2_gen.*`
* `graph.*`
* `invariants.*`

## Library files

* `util_io.*`
* `matrix.*`

# Other code files

* `global.*`
* `makefile`

## Data files (in `data/` directory)

* `4x4Id.txt` A space separated 4x4 identity matrix
* `DataMikeStudent2.txt` Sage data provided by Aurel Page. 
The file is, for each pair of points with adjacency witnesses, the list of adjacency witnesses:

```
[ p, q ]
[ comma separated list of adjacency witnesses ]
```

* `starting_data.txt` Same information as `DataMikeStudent2.txt` in C++ readable format.
The file starts with `n`, the number of lists of adjacency witnesses, followed by `n` lists of adjacency witnesses, each in the format:

```
p q
k
list
```

where `p` and `q` are the two points of hyperbolic space, `k` is the number of adjacency witnesses in `list`, and `list` is the list of adjacency witnesses (each is a 4x4 matrix).

* `gen*.txt` Each such file is an arbitrarily adjacency witness of `starting_data.txt`.
They are used to generate coset representatives for the subgroup of Gamma.

* `coset_reps_mod3.txt` List of coset representatives for Gamma', the subgroup of Gamma consiting of all matrices that are the identity modulo 3.
The file starts with `n`, the number of coset representatives, followed by the `n` coset representatives in 4x4 matrix format.

* `adjacency_lists_mod3_cover.txt` Adjacency witness lists for Gamma'. 
The file starts with `n`, the number of adjacency witness lists, followed by `n` adjacency witness lists in the format:

```
i size rep1 rep2 p q
list
```

where `i` is the index of the adjacency in the complete adjacency witness list (for all edges before removing empty lists; essentially for debugging purposes); `size` is the number of witnesses in the list for this specific edge (should always be 1); `rep1` coset representative for `p`; `rep2` coset representative for `q`; `p` and `q`, points from the original data for Gamma; `list` is the list of elements witnessing closeness between `rep1*p` and `rep2*q` in the quotient by Gamma'.

* `graph.txt` The graph corresponding to the data in `adjacency_lists_mod3_cover.txt` in adjacency list for each vertex format.
* `mod3_2skel_simplex_format.txt` The 2-skeleton of the Rips complex of the data in `graph.txt`, in Perseus readable format.

