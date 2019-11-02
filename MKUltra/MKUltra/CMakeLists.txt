# CMakeList.txt : CMake project for MKUltra, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories (include)
include_directories (/usr/local/include)
link_directories (/usr/local/lib)

# Add source to this project's executable.
add_executable (MKUltra
	"app/synth.cpp"
	"app/envelope.cpp"
	"app/instrument.cpp"
	"app/oscillator.cpp"
)

target_link_libraries (MKUltra portaudio)

# TODO: Add tests and install targets if needed.
