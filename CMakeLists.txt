cmake_minimum_required(VERSION 3.16)
project(flugel_engine)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>/${CMAKE_SYSTEM_NAME}/lib")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>/${CMAKE_SYSTEM_NAME}/lib")
#set(CMAKE_PDB_OUTPUT_DIRECTORY     "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>/${CMAKE_SYSTEM_NAME}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/$<CONFIG>/${CMAKE_SYSTEM_NAME}")

if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE $<$<OR:$<CONFIG:release>,$<CONFIG:minsizerel>>:TRUE>)
  #set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<OR:$<CONFIG:debug>,$<CONFIG:relwithdebinfo>>:Debug>")
endif()

set(FLUGEL_USE_SDL2 OFF)
set(FLUGEL_USE_GLFW ON)
add_subdirectory(flugel)
add_subdirectory(sandbox)