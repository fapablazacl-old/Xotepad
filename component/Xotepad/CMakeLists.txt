
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
)

add_executable(${target} WIN32 ${sources})

target_link_libraries(${target} comctl32)
