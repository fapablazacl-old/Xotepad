
#include "LexerConfigurationService.hpp"


LexerConfiguration LexerConfigurationService::getConfiguration(const std::string &languageId) const {
    if (languageId == "c++") {
        LexerConfiguration config;

        config.lexer = Lexer::Clike;

        config.keywords = {
            "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", 
            "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char",
            "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", 
            "continue", "decltype", "default", "delete", "do",
            "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", 
            "for", "friend", "goto", "if", "inline", "int", "import", "long",
            "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", 
            "or", "or_eq", "private", "protected", "public",
            "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static", 
            "static_assert", "static_cast", "struct",
            "switch", "synchronized", "template", "this", "thread_local", 
            "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned",
            "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
        };

        config.tokenStyle = {
            {CLIKE_COMMENT, Color{0, 125, 0}}, 
            {CLIKE_COMMENTLINE, Color{0, 125, 0}}, 
            {CLIKE_COMMENTDOC, Color{0, 125, 0}}, 
            {CLIKE_NUMBER, Color{0, 0, 0}}, 
            {CLIKE_WORD, Color{0, 0, 255}},
            {CLIKE_STRING, {125, 0, 0}}, 
            {CLIKE_CHARACTER, {125, 0, 0}}, 
            {CLIKE_UUID, {0, 0, 0}}, 
            {CLIKE_PREPROCESSOR, {160, 0, 255}}, 
            {CLIKE_OPERATOR, {0, 0, 0}}, 
            {CLIKE_IDENTIFIER, {0, 0, 0}}, 
            {CLIKE_STRINGEOL, {0, 0, 0}}, 
            {CLIKE_VERBATIM, {0, 0, 0}}, 
            {CLIKE_REGEX, {0, 0, 0}}, 
            {CLIKE_COMMENTLINEDOC, {0, 0, 0}}, 
            {CLIKE_WORD2, {0, 0, 0}}, 
            {CLIKE_COMMENTDOCKEYWORD, {0, 0, 0}}, 
            {CLIKE_COMMENTDOCKEYWORDERROR, {0, 0, 0}}, 
            {CLIKE_GLOBALCLASS, {0, 0, 0}}, 
            {CLIKE_STRINGRAW, {0, 0, 0}}, 
            {CLIKE_TRIPLEVERBATIM, {0, 0, 0}}, 
            {CLIKE_HASHQUOTEDSTRING, {0, 0, 0}}, 
            {CLIKE_PREPROCESSORCOMMENT, {0, 0, 0}}, 
            {CLIKE_PREPROCESSORCOMMENTDOC, {0, 0, 0}}, 
            {CLIKE_USERLITERAL, {0, 0, 0}}, 
            {CLIKE_TASKMARKER, {0, 0, 0}}, 
            {CLIKE_ESCAPESEQUENCE, {0, 0, 0}}
        };

        return config;
    }

    if (languageId == "cmake") {
        LexerConfiguration config;

        config.lexer = Lexer::CMake;

        config.keywords = {
            // These commands are always available.
            "break",
            "cmake_host_system_information",
            "cmake_minimum_required",
            "cmake_parse_arguments",
            "cmake_policy",
            "configure_file",
            "continue",
            "else",
            "elseif",
            "endforeach",
            "endfunction",
            "endif",
            "endmacro",
            "endwhile",
            "execute_process",
            "file",
            "find_file",
            "find_library",
            "find_package",
            "find_path",
            "find_program",
            "foreach",
            "function",
            "get_cmake_property",
            "get_directory_property",
            "get_filename_component",
            "get_property",
            "if",
            "include",
            "include_guard",
            "list",
            "macro",
            "mark_as_advanced",
            "math",
            "message",
            "option",
            "return",
            "separate_arguments",
            "set",
            "set_directory_properties",
            "set_property",
            "site_name",
            "string",
            "unset",
            "variable_watch",
            "while",
            
            // These commands are available only in CMake projects.
            "add_compile_definitions",
            "add_compile_options",
            "add_custom_command",
            "add_custom_target",
            "add_definitions",
            "add_dependencies",
            "add_executable",
            "add_library",
            "add_link_options",
            "add_subdirectory",
            "add_test",
            "aux_source_directory",
            "build_command",
            "create_test_sourcelist",
            "define_property",
            "enable_language",
            "enable_testing",
            "export",
            "fltk_wrap_ui",
            "get_source_file_property",
            "get_target_property",
            "get_test_property",
            "include_directories",
            "include_external_msproject",
            "include_regular_expression",
            "install",
            "link_directories",
            "link_libraries",
            "load_cache",
            "project",
            "remove_definitions",
            "set_source_files_properties",
            "set_target_properties",
            "set_tests_properties",
            "source_group",
            "target_compile_definitions",
            "target_compile_features",
            "target_compile_options",
            "target_include_directories",
            "target_link_directories",
            "target_link_libraries",
            "target_link_options",
            "target_precompile_headers",
            "target_sources",
            "try_compile",
            "try_run",

            // These commands are available only in CTest scripts.
            "ctest_build",
            "ctest_configure",
            "ctest_coverage",
            "ctest_empty_binary_directory",
            "ctest_memcheck",
            "ctest_read_custom_files",
            "ctest_run_script",
            "ctest_sleep",
            "ctest_start",
            "ctest_submit",
            "ctest_test",
            "ctest_update",
            "ctest_upload",
            
            // These commands are deprecated and are only made available to maintain backward compatibility. 
            // The documentation of each command states the CMake version in which it was deprecated. Do not use these commands in new code.
            "build_name",
            "exec_program",
            "export_library_dependencies",
            "install_files",
            "install_programs",
            "install_targets",
            "load_command",
            "make_directory",
            "output_required_files",
            "qt_wrap_cpp",
            "qt_wrap_ui",
            "remove",
            "subdir_depends",
            "subdirs",
            "use_mangled_mesa",
            "utility_source",
            "variable_requires",
            "write_file",

            // commands defined by Qt
            "qt5_add_big_resources", 
            "qt5_add_binary_resources", 
            "qt5_add_resources", 
            "qt5_generate_moc", 
            "qt5_import_plugins", 
            "qt5_wrap_cpp", 
            "qt5_wrap_ui", 
            "qt5_add_dbus_adaptor", 
            "qt5_add_dbus_interface", 
            "qt5_add_dbus_interfaces", 
            "qt5_generate_dbus_interface", 
            "qt5_add_translation", 
            "qt5_create_translation", 
        };

        config.tokenStyle = {
            {CMAKE_DEFAULT, Color{0, 0, 0}},
            {CMAKE_COMMENT, Color{0, 125, 0}},
            {CMAKE_STRINGDQ, Color{200, 0, 0}},
            {CMAKE_STRINGLQ, Color{200, 0, 0}},
            {CMAKE_STRINGRQ, Color{200, 0, 0}},
            {CMAKE_COMMANDS, Color{0, 0, 255}},
            {CMAKE_PARAMETERS, Color{0, 0, 0}},
            {CMAKE_VARIABLE, Color{0, 0, 0}},
            {CMAKE_USERDEFINED, Color{0, 0, 0}},
            {CMAKE_WHILEDEF, Color{0, 0, 255}},
            {CMAKE_FOREACHDEF, Color{0, 0, 255}},
            {CMAKE_IFDEFINEDEF, Color{0, 0, 255}},
            {CMAKE_MACRODEF, Color{0, 0, 255}},
            {CMAKE_STRINGVAR, Color{0, 0, 0}},
            {CMAKE_NUMBER, Color{0, 0, 0}}
        };

        return config;
    }

    if (languageId == "gl") {
        LexerConfiguration config;

        config.lexer = Lexer::Clike;

        // keywords
        config.keywords = {
            "attribute const uniform varying",
            "layout",
            "centroid flat smooth noperspective",
            "patch sample",
            "break continue do for while switch case default",
            "if else",
            "subroutine",
            "in out inout",
            "float double int void bool true false",
            "invariant",
            "discard return",
            "mat2 mat3 mat4 dmat2 dmat3 dmat4",
            "mat2x2 mat2x3 mat2x4 dmat2x2 dmat2x3 dmat2x4",
            "mat3x2 mat3x3 mat3x4 dmat3x2 dmat3x3 dmat3x4",
            "mat4x2 mat4x3 mat4x4 dmat4x2 dmat4x3 dmat4x4",
            "vec2 vec3 vec4 ivec2 ivec3 ivec4 bvec2 bvec3 bvec4 dvec2 dvec3 dvec4",
            "uint uvec2 uvec3 uvec4",
            "lowp mediump highp precision",
            "sampler1D sampler2D sampler3D samplerCube",
            "sampler1DShadow sampler2DShadow samplerCubeShadow",
            "sampler1DArray sampler2DArray",
            "sampler1DArrayShadow sampler2DArrayShadow",
            "isampler1D isampler2D isampler3D isamplerCube",
            "isampler1DArray isampler2DArray",
            "usampler1D usampler2D usampler3D usamplerCube",
            "usampler1DArray usampler2DArray",
            "sampler2DRect sampler2DRectShadow isampler2DRect usampler2DRect",
            "samplerBuffer isamplerBuffer usamplerBuffer",
            "sampler2DMS isampler2DMS usampler2DMS",
            "sampler2DMSArray isampler2DMSArray usampler2DMSArray",
            "samplerCubeArray samplerCubeArrayShadow isamplerCubeArray usamplerCubeArray",
            "struct",
        
            // The following are the keywords reserved for future use. Using them will result in an error:
            "common partition active",
            "asm",
            "class union enum typedef template this packed",
            "goto",
            "inline noinline volatile public static extern external interface",
            "long short half fixed unsigned superp",
            "input output",
            "hvec2 hvec3 hvec4 fvec2 fvec3 fvec4",
            "sampler3DRect",
            "filter",
            "image1D image2D image3D imageCube",
            "iimage1D iimage2D iimage3D iimageCube",
            "uimage1D uimage2D uimage3D uimageCube",
            "image1DArray image2DArray",
            "iimage1DArray iimage2DArray uimage1DArray uimage2DArray",
            "image1DShadow image2DShadow",
            "image1DArrayShadow image2DArrayShadow",
            "imageBuffer iimageBuffer uimageBuffer",
            "sizeof cast",
            "namespace using",
            "row_major"
        };

        config.tokenStyle = {
            {CLIKE_COMMENT, Color{0, 125, 0}}, 
            {CLIKE_COMMENTLINE, Color{0, 125, 0}}, 
            {CLIKE_COMMENTDOC, Color{0, 125, 0}}, 
            {CLIKE_NUMBER, Color{0, 0, 0}}, 
            {CLIKE_WORD, Color{0, 0, 255}},
            {CLIKE_STRING, {125, 0, 0}}, 
            {CLIKE_CHARACTER, {125, 0, 0}}, 
            {CLIKE_UUID, {0, 0, 0}}, 
            {CLIKE_PREPROCESSOR, {160, 0, 255}}, 
            {CLIKE_OPERATOR, {0, 0, 0}}, 
            {CLIKE_IDENTIFIER, {0, 0, 0}}, 
            {CLIKE_STRINGEOL, {0, 0, 0}}, 
            {CLIKE_VERBATIM, {0, 0, 0}}, 
            {CLIKE_REGEX, {0, 0, 0}}, 
            {CLIKE_COMMENTLINEDOC, {0, 0, 0}}, 
            {CLIKE_WORD2, {0, 0, 0}}, 
            {CLIKE_COMMENTDOCKEYWORD, {0, 0, 0}}, 
            {CLIKE_COMMENTDOCKEYWORDERROR, {0, 0, 0}}, 
            {CLIKE_GLOBALCLASS, {0, 0, 0}}, 
            {CLIKE_STRINGRAW, {0, 0, 0}}, 
            {CLIKE_TRIPLEVERBATIM, {0, 0, 0}}, 
            {CLIKE_HASHQUOTEDSTRING, {0, 0, 0}}, 
            {CLIKE_PREPROCESSORCOMMENT, {0, 0, 0}}, 
            {CLIKE_PREPROCESSORCOMMENTDOC, {0, 0, 0}}, 
            {CLIKE_USERLITERAL, {0, 0, 0}}, 
            {CLIKE_TASKMARKER, {0, 0, 0}}, 
            {CLIKE_ESCAPESEQUENCE, {0, 0, 0}}
        };

        return config;
    }

    return {
        Lexer::Text, {""}, {}
    };
}
