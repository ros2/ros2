# The main use case for this file is to
# include dependencies and linting tools required by spaceros
# into every ROS package without modifying 'CMakeLists.txt' files

# The code can be injected into packages with `CMAKE_PROJECT_INCLUDE` variable 
# Check: https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_INCLUDE.html

cmake_minimum_required(VERSION 3.15)
find_package(ament_cmake REQUIRED)

# required to avoid test duplications in case tests are already defined in packages
set(AMENT_LINT_AUTO_SKIP_PREEXISTING_TESTS ON)

if (BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    # include common set of spaceros linters
    find_package(ament_cmake_clang_tidy REQUIRED)
    find_package(ament_cmake_cobra REQUIRED)
    find_package(ament_cmake_copyright REQUIRED)
    find_package(ament_cmake_cppcheck REQUIRED)
    find_package(ament_cmake_cpplint REQUIRED)
    find_package(ament_cmake_ikos REQUIRED)
    find_package(ament_cmake_flake8 REQUIRED)
    find_package(ament_cmake_lint_cmake REQUIRED)
    find_package(ament_cmake_pep257 REQUIRED)
    find_package(ament_cmake_uncrustify REQUIRED)
    find_package(ament_cmake_xmllint REQUIRED)
endif()

