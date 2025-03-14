#include <QApplication>
#include "BankAppGUI.h"


int main(int argc, char *argv[]) {
    // Inizializza l'applicazione Qt
    QApplication app(argc, argv);

    // Crea e mostra l'interfaccia grafica
    BankAppGUI window;
    window.show();

    // Avvia il ciclo dell'applicazione Qt
    return app.exec();
}
