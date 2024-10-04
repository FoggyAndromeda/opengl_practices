# Getting sources

Should be cloned recursived, all dependecies included as submodules.

```sh
git clone --recursive https://github.com/FoggyAndromeda/opengl_practices.git
cd opengl_practicies
```

# Building

```sh
mkdir build
cd build
cmake ..
make -j 4
```

# Running

Don't forget to copy shaders from ./src/shaders/ to directories with binaries
