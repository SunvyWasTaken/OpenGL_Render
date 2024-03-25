project(DefaultApp)

set(DLL_NAME "MiniMotor")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

file(GLOB_RECURSE SOURCES "*.h" "*.cpp")

macro(GroupSources curdir)
    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
    ${PROJECT_SOURCE_DIR}/${curdir}/* ${PROJECT_SOURCE_DIR}/${curdir}/${curdir}/*)

    foreach(child ${children})

        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(${groupname} FILES
            ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        endif()
    endforeach()
endmacro()

# Execute the macro
GroupSources(src)

include_directories(${CMAKE_SOURCE_DIR}/${DLL_NAME}/Sources)

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)
find_package(ImGui-SFML CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})


target_link_libraries(${PROJECT_NAME} PRIVATE 
	${DLL_NAME}
        sfml-system sfml-graphics sfml-window
	ImGui-SFML::ImGui-SFML
)

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
