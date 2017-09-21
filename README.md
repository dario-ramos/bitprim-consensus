# Bitprim Consensus <a target="_blank" href="https://gitter.im/bitprim/Lobby">![Gitter Chat][badge.Gitter]</a>

*Bitcoin consensus library*

| **master(linux/osx)** | **dev(linux/osx)**   | **master(windows)**   | **dev(windows)** |
|:------:|:-:|:-:|:-:|
| [![Build Status](https://travis-ci.org/bitprim/bitprim-consensus.svg)](https://travis-ci.org/bitprim/bitprim-consensus)       | [![Build StatusB](https://travis-ci.org/bitprim/bitprim-consensus.svg?branch=dev)](https://travis-ci.org/bitprim/bitprim-consensus?branch=dev)  | [![Appveyor Status](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-consensus?svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-consensus)  | [![Appveyor StatusB](https://ci.appveyor.com/api/projects/status/github/bitprim/bitprim-consensus?branch=dev&svg=true)](https://ci.appveyor.com/project/bitprim/bitprim-consensus?branch=dev)  |

Table of Contents
=================

   * [Bitprim Consensus](#bitprim-consensus)
      * [About](#about)
      * [Bitprim Integration](#bitprim-integration)
      * [Installation](#installation)
        * [Using Conan](#using-conan-recommended)
        * [Build from source](#build-from-source)
            * [Debian/Ubuntu](#debianubuntu)
            * [Windows with Visual Studio](#windows-with-visual-studio)

# About

This library includes the following 33 files considered to be bitcoin script consensus-critical. These files are identical to those used in version 0.13.2 of bitcoin-core.

```
amount.h
hash.cpp
hash.h
prevector.h
pubkey.cpp
pubkey.h
serialize.h
tinyformat.h
uint256.cpp
uint256.h
utilstrencodings.cpp
utilstrencodings.h
version.h
compat/byteswap.h
compat/endian.h
crypto/common.h
crypto/hmac_sha512.cpp
crypto/hmac_sha512.h
crypto/ripemd160.cpp
crypto/ripemd160.h
crypto/sha1.cpp
crypto/sha1.h
crypto/sha256.cpp
crypto/sha256.h
crypto/sha512.cpp
crypto/sha512.h
primitives/transaction.cpp
primitives/transaction.h
script/interpreter.cpp
script/interpreter.h
script/script.cpp
script/script.h
script/script_error.h
```

# Bitprim Integration

Bitprim natively implements consensus checks that are redundant with `bitprim-consensus`. Bitprim includes a full bitcoin client and server SDK. This includes the full node implementation [bitprim-node](https://github.com/bitprim/bitprim-node), which builds on [bitprim-core](https://github.com/bitprim/bitprim-core) and [bitprim-blockchain](https://github.com/bitprim/bitprim-blockchain).

The `bitprim-blockchain` configuration provides the `--with-consensus` option. This allows the developer to select either `bitprim-core` native or `bitprim-consensus` checks. The option defaults to `yes` so that by default all `bitprim-node` and `bitprim-server` builds use the same consensus checks as a Satoshi node.

## Installation
Make sure you have installed [bitprim-core](https://github.com/bitprim/bitprim-core) beforehand according to its respective build instructions.

### Using Conan (recommended)

Conan is a Python package for dependency management; it only requires Python and Pip.
With Conan, install can be performed on any OS. If there are no prebuilt binaries for a given
OS-compiler-arch combination, Conan will build from source.

```
pip install conan
conan remote add bitprim https://api.bintray.com/conan/bitprim/bitprim
conan install bitprim-consensus/0.1@bitprim/stable
```

The last step will install binaries and headers in Conan's cache, a directory outside the usual
system paths. This will avoid conflict with system packages such as boost.
Also, notice it references the stable version 0.1. To see which versions are available,
please check [Bintray](https://bintray.com/bitprim/bitprim/bitprim-consensus%3Abitprim).

### Build from source

#### Debian/Ubuntu

```
$ git clone https://github.com/bitprim/bitprim-consensus.git
$ cd bitprim-consensus
$ mkdir build
$ cd build
$ cmake .. -DWITH_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++11"
$ make -j2
$ sudo make install
```

`bitprim-consensus` is now installed in `/usr/local/`.

#### Windows with Visual Studio

This project, unlike secp256k1, has external dependencies such as boost.
The easiest way to build them is to use Conan from the CMake script,
which will install boost and other libraries in non-system directories.

From a [Visual Studio Developer Command Prompt](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs):

```
$ pip install conan
$ git clone https://github.com/bitprim/bitprim-consensus.git
$ cd bitprim-consensus
$ mkdir build
$ cd build
$ conan install ..
$ cmake .. -DUSE_CONAN=ON -DNO_CONAN_AT_ALL=OFF
$ msbuild ALL_BUILD.vcxproj
```

[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
    