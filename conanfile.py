#
# Copyright (c) 2017 Bitprim developers (see AUTHORS)
#
# This file is part of Bitprim.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

from conans import ConanFile, CMake

def option_on_off(option):
    return "ON" if option else "OFF"

class BitprimConsensusConan(ConanFile):
    name = "bitprim-consensus"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/bitprim/bitprim-consensus"
    description = "Bitcoin Consensus Library"
    settings = "os", "compiler", "build_type", "arch"

    # options = {"shared": [True, False]}
    # default_options = "shared=False"

    options = {"shared": [True, False],
               "fPIC": [True, False],
               "with_tests": [True, False],
               "with_java": [True, False],
               "with_python": [True, False],
               "use_cpp11_abi": [True, False]
    }

    default_options = "shared=False", \
        "fPIC=True", \
        "with_tests=True", \
        "with_java=False", \
        "with_python=False", \
        "use_cpp11_abi=True"

    generators = "cmake"
    build_policy = "missing"

    exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "bitprim-consensusConfig.cmake.in", "include/*", "test/*"

    package_files = "build/lbitprim-consensus.a"


    requires = (("bitprim-conan-boost/1.64.0@bitprim/stable"),
                ("secp256k1/0.1@bitprim/stable"),
                ("bitprim-core/0.1@bitprim/stable"))

    def build(self):
        cmake = CMake(self)

        cmake.definitions["USE_CONAN"] = "ON"
        cmake.definitions["NO_CONAN_AT_ALL"] = "OFF"
        cmake.definitions["CMAKE_VERBOSE_MAKEFILE"] = "ON"
        cmake.definitions["ENABLE_SHARED"] = option_on_off(self.options.shared)
        cmake.definitions["ENABLE_POSITION_INDEPENDENT_CODE"] = option_on_off(self.options.fPIC)
        cmake.definitions["USE_CPP11_ABI"] = option_on_off(self.options.use_cpp11_abi)
        cmake.definitions["WITH_TESTS"] = option_on_off(self.options.with_tests)
        cmake.definitions["WITH_JAVA"] = option_on_off(self.options.with_java)
        cmake.definitions["WITH_PYTHON"] = option_on_off(self.options.with_python)
        
        if self.settings.compiler == "gcc":
            if float(str(self.settings.compiler.version)) >= 5:
                cmake.definitions["_GLIBCXX_USE_CXX11_ABI"] = "1"
            else:
                cmake.definitions["_GLIBCXX_USE_CXX11_ABI"] = "0"
        
        cmake.configure(source_dir=self.conanfile_directory)
        cmake.build()

    def imports(self):
        self.copy("*.h", "", "include")

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.ipp", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)


    def package_info(self):
        self.cpp_info.includedirs = ['include']
        self.cpp_info.libs = ["bitprim-consensus"]
