cmake_minimum_required(VERSION 3.0)

PROJECT(glCode)

macro( add_module )
    foreach( modname ${ARGV} )
    	file( GLOB incfls ../../include/${modname}/*.h)
    	add_library( ${modname} SHARED  ${srcfiles} ${incfls} )
	set( inclfiles ../../include/${modname} ../../include/${moddeps} )
   	target_include_directories( ${modname} PUBLIC ${inclfiles}  )
	target_link_libraries( ${modname} ${moddeps} )
	set_target_properties(  ${modname}
				PROPERTIES
				RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )
    endforeach(modname)
endmacro( add_module )

macro( add_GL_module )
    find_package( OpenGL REQUIRED )
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set( modname  ${ARGV} )
    set( modname  ${ARGV} )
    set( linkdir  ${CMAKE_CONFIGURATION_TYPES} )
    link_directories( ${linkdir}  )
    add_module( ${modname} )
    target_link_libraries( ${modname} ${OPENGL_LIBRARIES} )
endmacro( add_GL_module )

macro( add_GLUT_module )
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set( modname  ${ARGV} )
    set( linkdir  ${CMAKE_CONFIGURATION_TYPES} )
    link_directories( ${linkdir}  )
    add_module( ${modname} )
    #link_libraries(  ${modname} "freeglut.lib" )
   
endmacro( add_GLUT_module )

macro( add_exec )
    foreach( modname ${ARGV} )
    	file( GLOB incfls ../../include/${modname}/*.h)
    	add_executable( ${modname} WIN32 ${srcfiles} ${incfls} )
	set( inclfiles ../../include/${modname} ../../include/${moddeps} )
   	target_include_directories( ${modname} PUBLIC ${inclfiles}  )
	target_link_libraries( ${modname} ${moddeps} )
	set_target_properties(  ${modname}
				PROPERTIES
				RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )
    endforeach( modname )
endmacro( add_exec )

macro( add_console_exec )
    foreach( modname ${ARGV} )
    	file( GLOB incfls ../../include/${modname}/*.h)
    	add_executable( ${modname} ${srcfiles} ${incfls} )
	set( inclfiles ../../include/${modname} ../../include/${moddeps} )
   	target_include_directories( ${modname} PUBLIC ${inclfiles}  )
	target_link_libraries( ${modname} ${moddeps} )
	set_target_properties(  ${modname}
				PROPERTIES
				RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )
    endforeach( modname )
endmacro( add_console_exec )

set ( modules glMod glutMod testApp )
foreach ( module ${modules} ) 
	add_subdirectory( src/${module} )
endforeach(module)

