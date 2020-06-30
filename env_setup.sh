#!/bin/bash
# mkdir trial
# cd trial
# sudo apt-get update && sudo apt-get upgrade -y
# echo "Done"

git clone https://github.com/oktal/pistache.git
git submodule update --init
cd pistache
mkdir -p {build,prefix}
cd build
cmake -G "Unix Makefiles" \
        -DCMAKE_BUILD_TYPE=Release \
        -DPISTACHE_BUILD_EXAMPLES=true \
        -DPISTACHE_BUILD_TESTS=true \
        -DPISTACHE_BUILD_DOCS=false \
        -DPISTACHE_USE_SSL=true \
        -DCMAKE_INSTALL_PREFIX=$PWD/../prefix \
        ../
make -j
sudo make install

cd ../..
git clone https://github.com/Tencent/rapidjson/
cd rapidjson
git submodule update --init
mkdir build
cd build
cmake ..
make
sudo make install

cd ../..
git clone https://github.com/jbeder/yaml-cpp.git
cd yaml-cpp
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..