#include <vunikEngine/init.hpp>
#include <vunikENgine/window.hpp>

namespace vunikEngine {
    bool Init::init (void) {
        if (!Window::init()) {
            return false;
        }
        return true;
    }

    void Init::deinit (void) {
        Window::deinit();
    }
}
