# 👇 About minecraft
Minecraft like voxel renderer / world generator written in a week using C++ and OpenGL.

![screenrecord](screenrecord.gif)

# Getting started
```shell
# Using an apt based system
sudo apt install libglew-dev libglm-dev libspdlog-dev nlohmann-json3-dev
git clone https://github.com/douidik/minecraft
cd mincraft
mkdir build && cd build
cmake .. -GNinja
ninja
cd ..
./build/Minecraft
```
