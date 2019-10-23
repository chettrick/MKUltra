# CMakeList.txt : CMake project for MKUltra, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories (include)
# Add source to this project's executable.
add_executable (MKUltra
	"app/MKUltra.cpp"
)

# TODO: Add tests and install targets if needed.
