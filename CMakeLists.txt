cmake_minimum_required(VERSION 3.12)
project(example)
option(FS_INCLUDE_FT "Include FreeType library (UI)" OFF)
add_subdirectory(engine)

add_executable(example
	"main.cpp"
)
target_link_libraries(example
	firesteel
	glad
	imgui
	glm
	assimp
)
target_compile_features(example PUBLIC cxx_std_17)
target_include_directories(example PUBLIC includes)
target_include_directories(example PUBLIC engine/external/glfw)
set_target_properties(example PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)