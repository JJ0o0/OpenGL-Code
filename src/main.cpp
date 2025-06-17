#include "window/window.h"

int main() {
    Window wnd(800, 600, "J0o0ll Janela"); // Criando a janela.
    wnd.Init(); // Inicializando.

    // Caso a janela não deve fechar.
    while (!wnd.ShouldClose()) {
        wnd.Update(); // Atualizar a janela.
    }

    // Aqui, é chamado o deconstrutor da janela e fechado o programa com sucesso.
    return 0;
}