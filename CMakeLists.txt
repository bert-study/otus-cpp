cmake_minimum_required(VERSION 3.12)

if(DEFINED RUN_NUMBER)
    set(VERSION_PATCH "${RUN_NUMBER}")
else()
    set(VERSION_PATCH "0")
endif()

project(ip_filter VERSION 0.0.${VERSION_PATCH})

add_executable(ip_filter main.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)


if(WITH_BOOST_TEST)
    enable_testing()
endif()
