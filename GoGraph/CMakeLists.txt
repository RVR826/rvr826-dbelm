# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GoGraph")

# -------------------------------------------------
# Compiler setup
# -------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optional: place build output in /out directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

# -------------------------------------------------
# Include METIS + GKlib
# -------------------------------------------------
set(METIS_ROOT "${CMAKE_SOURCE_DIR}/ext/metis")
set(GKLIB_PATH "${CMAKE_SOURCE_DIR}/ext/GKlib")

# Disable installing METIS binaries (we just want the lib)
set(METIS_BUILD_SHARED FALSE CACHE BOOL "Build METIS as static library" FORCE)
set(METIS_INSTALL FALSE CACHE BOOL "Disable METIS installation" FORCE)
set(GKLIB_INSTALL FALSE CACHE BOOL "Disable GKlib installation" FORCE)

# Add subdirectories
add_subdirectory(${METIS_ROOT})
add_subdirectory(${GKLIB_PATH})

# -------------------------------------------------
# Project sources and includes
# -------------------------------------------------
add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${METIS_ROOT}/include
    ${GKLIB_PATH}
)

# -------------------------------------------------
# Link libraries
# -------------------------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
    metis 
    GKlib
)

