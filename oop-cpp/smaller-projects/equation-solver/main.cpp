#include "equationsGUI.h"
#include <QtWidgets/QApplication>
#include "fileRepository.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileRepository* repository = new FileRepository{ "data.txt" };
    Service* service = new Service{ repository };
    equationsGUI* gui = new equationsGUI{ service };
    
    gui->show();

    return a.exec();
}
