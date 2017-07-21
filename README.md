# Parser Waifu

WIP Japanese parser app.

## Source code structure

* `src/` - contains main application code with GUI
* `lib/` - contains internal libraries that are used by main application
* `3pp/` - contains third party libraries that are used. It is not made as submodules just for the sake of effectivness. Plus github doesn't bundle submodules into zip.
* `test/` - tests by means of Google test

## Build

### Requirements

* CMake
* C++ compiler
* Qt5 - should be installed so that CMake will find it

### Instructions

```
mkdir build
cd build

cmake ../ [-DUNIT_TEST=on -DSHARED_LIB=on]
```

* **UNIT_TEST** builds tests exe
* **SHARED_LIB** builds mecab as dll
