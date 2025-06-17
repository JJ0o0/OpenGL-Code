#include "window/window.h"

int main() {
    Window wnd(800, 600, "J0o0ll Janela");
    wnd.Init();

    while (!wnd.ShouldClose()) {
        wnd.Update();
    }

    return 0;
}