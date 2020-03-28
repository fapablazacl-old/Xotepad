
# Find Boost
find_package(Boost REQUIRED COMPONENTS system file_system)

# Scintilla
set (SCINTILLA_INCLUDE_PATH "${SCINTILLA_INSTALL_PATH}/include")
set (SCINTILLA_LIBRARY_PATH "${SCINTILLA_INSTALL_PATH}/lib")

# Enable Unicode builds (do this just for Windows Apps and Libraries)
add_definitions (-DUNICODE)
add_definitions (-D_UNICODE)

set (target "Xotepad")

set (sources 
	"sources/main.cpp"
	"sources/CScintilla.cpp" 
	"sources/CScintilla.hpp" 
	"sources/CMainWindow.cpp" 
	"sources/CMainWindow.hpp" 
	"sources/CEditorView.cpp" 
	"sources/CEditorView.hpp" 
	"sources/MainWindow.cpp" 
	"sources/MainWindow.hpp" 
	"sources/MainWindowModel.cpp" 
	"sources/MainWindowModel.hpp" 
	"sources/MainWindowPresenter.cpp" 
	"sources/MainWindowPresenter.hpp" 
	"sources/FileService.cpp" 
	"sources/FileService.hpp" 
	"sources/CXotepadApp.cpp" 
	"sources/CXotepadApp.hpp" 
	"sources/WindowsUtils.cpp" 
	"sources/WindowsUtils.hpp" 
)

add_executable(${target} WIN32 ${sources})

target_include_directories(${target} PRIVATE ${WIN32PP_INCLUDE_PATH} ${SCINTILLA_INCLUDE_PATH} ${Boost_INCLUDE_DIR})
target_link_directories(${target} PRIVATE ${SCINTILLA_LIBRARY_PATH} ${Boost_LIBRARY_DIR})

target_link_libraries(${target} comctl32 ${Boost_LIBRARIES})
