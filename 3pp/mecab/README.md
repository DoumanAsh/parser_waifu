# mecab(CMake)

Add CMake support to mecab.

## Build

```
mkdir build/
cd build/
cmake ../
make            ///or whatever generator you use
```

By default you build static library.
In case you want shared one:

```
cmake ..\ -DSHARED_LIB=ON
```
