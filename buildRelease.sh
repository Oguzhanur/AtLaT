cmake -B build-linux \
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
    -DCMAKE_BUILD_TYPE=Release

cmake --build build-linux -j$(nproc)
