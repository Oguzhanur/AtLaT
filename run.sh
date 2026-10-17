rm -rf ./build/data ./build/raylibtest1
./build.sh
cp -r ./data/ ./build
cd build
./raylibtest1 