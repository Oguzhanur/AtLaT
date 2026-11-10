cmake -B build-windows \
    -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake \
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
    -DCMAKE_BUILD_TYPE=Release

cmake --build build-windows -j$(nproc)
