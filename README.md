# snake

This game can be compiled and ran in a browser using Emscripten with instructions below.

First install Emscripten:
```bash
$ git clone git@github.com:emscripten-core/emsdk.git
$ cd emsdk
$ ./emsdk install 3.1.67
$ ./emsdk activate 3.1.67
$ source ./emsdk_env.sh
```

Then get this fork of SFML:
```bash
$ git clone git@github.com:Zombieschannel/SFML.git
$ cd SFML
$ git switch SFML-2.6.x-EMCC
```

Build and install static SFML libraries somewhere (my `cmake` version is 3.24.0):
```bash
$ mkdir build && cd build
$ emcmake cmake .. -DBUILD_SHARED_LIBS=false
$ emmake make -j 8
$ cmake --install . --prefix=path/to/somewhere/SFML
```

and the debug libraries too:
```bash
$ emcmake cmake -DCMAKE_BUILD_TYPE=Debug .
$ emmake make -j 8
$ cmake --install . --prefix=path/to/somewhere/SFML
```


Now go back to this repo and build with the installed libraries: \
!!! NEED TO FIRST EDIT `CMakeLists.txt` TO UPDATE THE PATH TO SFML ON L46 !!!
```bash
$ cd path/to/snake
$ mkdir build && cd build
$ emcmake cmake ..
$ emmake make
```

The compiled game can then be run in any browser, for example:
```bash
$ emrun Project.html --browser /mnt/c/Program\ Files\ \(x86\)/Microsoft/Edge/Application/msedge.exe
```

Do `$ emrun --list-browsers` to see a list of identified browsers on your machine
