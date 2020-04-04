
# Find Boost
find_package(Boost REQUIRED COMPONENTS system file_system)

set (target "core")

set (sources 
	"sources/MainWindow.cpp" 
	"sources/MainWindow.hpp" 
	"sources/MainWindowModel.cpp" 
	"sources/MainWindowModel.hpp" 
	"sources/MainWindowPresenter.cpp" 
	"sources/MainWindowPresenter.hpp" 
	"sources/FileService.cpp" 
	"sources/FileService.hpp" 
	"sources/WindowsUtils.cpp" 
	"sources/WindowsUtils.hpp" 
	"sources/LexerConfigurationService.cpp" 
	"sources/LexerConfigurationService.hpp" 
	"sources/Document.cpp" 
	"sources/Document.hpp" 
	"sources/FindReplaceDialog.cpp" 
	"sources/FindReplaceDialog.hpp" 
)

add_library (${target} ${sources})

target_include_directories (${target} PRIVATE ${Boost_INCLUDE_DIR})
target_link_directories (${target} PRIVATE ${Boost_LIBRARY_DIR})

target_link_libraries (${target} ${Boost_LIBRARIES})
