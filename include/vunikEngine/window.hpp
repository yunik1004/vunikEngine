#pragma once

#include <string>
#include <vunikEngine/init.hpp>

namespace vunikEngine {
    class Window {
    friend class Init;

    public:
        Window (void);
        ~Window (void);

        bool createWindow (int width, int height, std::string title);

		void render (void);

    private:
        static bool init (void);
        static void deinit (void);

        void* window = nullptr;
    };
}
