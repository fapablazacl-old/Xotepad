
set (target "test-core")

set (sources 
	"test/TestCore.cpp" 
	"test/WindowsUtils.test.cpp" 
)

add_executable (${target} ${sources})
target_link_libraries (${target} core)
