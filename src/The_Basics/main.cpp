#include <QApplication>
#include "MainWindow.h"
#include "loginScreen.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginScreen log;
   
    // --- checking if user is login ---
    if (log.exec() != QDialog::Accepted)
    {
        return 0;}
    

    MainWindow w(log.username());
    w.resize(800, 500);
    w.show();
    return app.exec();
    
    
}
