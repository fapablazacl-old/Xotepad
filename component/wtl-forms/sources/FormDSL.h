
#pragma once

#include <vector>

namespace dsl {
    struct Rect {
        int left = 0, top = 0;
        int width = 0, height = 0;
    };

    struct Window {
        enum Type {
            CTRL_CUSTOM = 0,
            CTRL_LABEL,
            CTRL_BUTTON,
            CTRL_TEXTBOX,
            CTRL_CHECKBOX,
            CTRL_OPTIONBOX,
            CTRL_LIST,
            CTRL_COMBOBOX,
            CTRL_GROUPBOX
        };

        const char * const className = nullptr;
        const Type type;

        int id = 0;
        const char * caption = nullptr;
        Rect rect = {};

        std::vector<Window> children;
        
        explicit Window(const char * const className_) : className(className_), type(CTRL_CUSTOM) {}
        explicit Window(const Type type_) : className(nullptr), type(type_) {}
    };


    class WindowBuilder {
    public:
        explicit WindowBuilder(const char *className) : window(className) {}

        explicit WindowBuilder(const Window::Type type) : window(type) {}

        Window build() const {
            return window;
        }


        WindowBuilder& caption(const char *value) {
            window.caption = value;

            return *this;
        }


        WindowBuilder& position(const int left, const int top) {
            window.rect.left = left;
            window.rect.top = top;

            return *this;
        }


        WindowBuilder& size(const int width, const int height) {
            window.rect.width = width;
            window.rect.height = height;

            return *this;
        }


        WindowBuilder& child(const WindowBuilder &childBuilder) {
            window.children.push_back(childBuilder.build());

            return *this;
        }

    public:
        static WindowBuilder label() {
            return WindowBuilder{Window::CTRL_LABEL};
        }

        static WindowBuilder button() {
            return WindowBuilder{Window::CTRL_BUTTON};
        }
        
        static WindowBuilder textBox() {
            return WindowBuilder{Window::CTRL_TEXTBOX};
        }
                
        static WindowBuilder checkBox() {
            return WindowBuilder{Window::CTRL_CHECKBOX};
        }

        static WindowBuilder optionBox() {
            return WindowBuilder{Window::CTRL_OPTIONBOX};
        }

        static WindowBuilder list() {
            return WindowBuilder{Window::CTRL_LIST};
        }

        static WindowBuilder comboBox() {
            return WindowBuilder{Window::CTRL_COMBOBOX};
        }
        
        static WindowBuilder groupBox() {
            return WindowBuilder{Window::CTRL_GROUPBOX};
        }

    private:
        Window window;
    };

    /*
    enum LAYOUT_SIZE_POLICY {
        LSP_NONE = 0x00,
        LSP_EXPAND_VERTICALLY = 0x01,
        LSP_EXPAND_HORIZONTALLY = 0x02,
        LSP_EXPAND = LSP_EXPAND_VERTICALLY | LSP_EXPAND_HORIZONTALLY
    };

    struct Layout {
        Window *window = nullptr;

        int leftMargin, topMargin;
        int rightMargin, bottomMargin;
    };
    */

    /*
    findReplaceUI
        .groupBox()
            .caption("Find/Replace parameters")
            .left(10).width(10)
            .top(10).height(270);
    */

    //this->CreateChild(findReplaceGroupBox,  10, 10, 270, 80, L"Find/Replace parameters", WS_VISIBLE | BS_GROUPBOX);
    //this->CreateChild(findWhatLabel,        30, 30, 100, 20, L"Find what", WS_VISIBLE);
    //this->CreateChild(findWhatEdit,         150, 30, 100, 20, L"", WS_VISIBLE | WS_TABSTOP, WS_EX_CLIENTEDGE);
    //this->CreateChild(replaceWithCheckBox,  30, 55, 100, 20, L"Replace with", WS_VISIBLE | BS_AUTOCHECKBOX);
    //this->CreateChild(replaceWithEdit,      150, 55, 100, 20, L"", WS_VISIBLE | WS_TABSTOP, WS_EX_CLIENTEDGE);


    template <typename ...Children>
    class Form {

    };

    template <typename Validator>
    class TextBox {
    };


    class Button {
    };


    class Label {
    };
}
