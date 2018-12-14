cmake_minimum_required(VERSION 3.5)
project(tstpkg)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)

include_directories(
  include
)

set(executable_name tstpkg)

add_executable(${executable_name}
  src/main.cpp
)

set(dependencies
  rclcpp
  tf2_ros
)

ament_target_dependencies(${executable_name}
  ${dependencies}
)

install(TARGETS ${executable_name}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

# install(DIRECTORY include/
  # DESTINATION include/
# )

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)

ament_package()
