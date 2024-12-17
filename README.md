Small sample demonstrating how to use the physx vcpkg port in a CMake project.

Also read [https://omni-101.github.io/omniverse/2023/07/07/omniverse-physx-vcpkg-port/](https://omni-101.github.io/omniverse/2023/07/07/omniverse-physx-vcpkg-port/) for more information.

```bash
$ vcpkg install physx
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release .. && make
$ ./hello_physx
Hello from PhysX!
```
