cmake_minimum_required(VERSION 3.12)

project(ip_filter VERSION 1.0.20)

add_executable(ip_filter_cli main.cpp)

set_target_properties(ip_filter_cli PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
