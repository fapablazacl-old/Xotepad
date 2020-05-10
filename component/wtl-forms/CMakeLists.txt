
set (target "wtl-forms")
set (sources
	"sources/Form.cpp"
	"sources/Form.h"
	"sources/FormDSL.cpp"
	"sources/FormDSL.h"
	"sources/Layout.cpp"
	"sources/Layout.h" 
)

add_library(${target} ${sources})
