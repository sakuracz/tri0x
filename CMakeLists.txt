CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project(triax C CXX)

#set( CMAKE_SYSTEM_NAME Windows )
#set( CMAKE_SYSTEM_PROCESSOR i686 )
#set( WIN32 ON )

#if( WIN32 )
#    add_definitions( -D_WIN32 -D_AMD64_ -D_M_AMD64 )
#    set( _MSC_VER 1200 CACHE INTERNAL "Setting _WIN32_WINNT to 0x0500 for Windows 2000 APIs" )
#    set( _WIN32_WINNT 0x0500 CACHE INTERNAL "Setting _WIN32_WINNT to 0x0500 for Windows 2000 APIs" )
#    set(WINVER 0x0500 CACHE INTERNAL "Setting WINVER to 0x0500 for Windows 2000 APIs" )
#endif( WIN32 )

#set( WIN_INCLUDE_DIR "/media/Install/Program Files (x86)/Visual Studio 2013/Win SDK/Include" )
#set( VS_INCLUDE_DIR "/media/Install/Program Files (x86)/Visual Studio 2013/VC/include" )

#set( SOURCES main.cpp ${WIN_INCLUDE_DIR}/Windows.h )

#include_directories(AFTER SYSTEM ${WIN_INCLUDE_DIR} ${VS_INCLUDE_DIR} )

file( GLOB_RECURSE TRIAX_SOURCES "*.cpp" )
file( GLOB_RECURSE LIBWIN_SOURCES "libWin/*.cpp" )

add_executable(triax ${TRIAX_SOURCES} )

set_property(TARGET triax PROPERTY CXX_STANDARD 14)
#target_include_directories( triax PUBLIC $<BUILD_INTERFACE:${WIN_INCLUDE_DIR};${VS_INCLUDE_DIR}> )







