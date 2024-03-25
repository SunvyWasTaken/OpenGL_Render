project (MiniMotor)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

include_directories(
    ${PROJECT_SOURCE_DIR}/Sources
    ${PROJECT_SOURCE_DIR}/Sources/Components/Public
    ${PROJECT_SOURCE_DIR}/Sources/Core/Public
    ${PROJECT_SOURCE_DIR}/Sources/Library/Public
    ${PROJECT_SOURCE_DIR}/Sources/Objects/Public
)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "*.h" "*.cpp" "*.hxx")

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
GroupSources(Sources)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE /wd4251 )

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics )
find_package(ImGui-SFML CONFIG REQUIRED)

add_compile_definitions(LITE_BUILD_DLL)

#ajout une compilation definition DEBUG pour la configuration debug
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-graphics sfml-window
	    ImGui-SFML::ImGui-SFML
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
