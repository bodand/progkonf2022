## Progkonf 2022
#
# Copyright (c) 2022 András Bodor
# All rights reserved.
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
#
# CMakeLists.txt --
#   The main cmake entry file.
#   Separates the build into the three specific implementations in the subdirs
#   of the root.

cmake_minimum_required(VERSION 3.20)

project(DynamicVisitor
        VERSION 1.0.0
        LANGUAGES CXX)

add_subdirectory(dynamic_cast)
add_subdirectory(type_info)
add_subdirectory(custom)

set(user_files
    user-code/main.cxx
    user-code/base.hxx
    user-code/derived_A.hxx
    user-code/derived_B.hxx
    user-code/derived_C.hxx)

add_executable(dynamic_cast ${user_files})
target_link_libraries(dynamic_cast PRIVATE lib-dynamic_cast)

add_executable(type_info ${user_files})
target_link_libraries(type_info PRIVATE lib-type_info)

add_executable(custom ${user_files})
target_link_libraries(custom PRIVATE lib-custom)
