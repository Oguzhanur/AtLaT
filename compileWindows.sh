# Tekrar yapılandırın ve derleyin
cmake -B build-windows -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build-windows