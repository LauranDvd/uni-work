#include "adminWindow.h"
#include <QtWidgets/QApplication>
#include "txtEventRepository.h"
#include "userService.h"
#include "htmlShortlist.h"
#include "userWindow.h"
#include <qdialog.h>
#include "startupModeChoice.h"
#include "monthsChartWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    StartupModeChoice modeChoiceWindow{};
    modeChoiceWindow.show();

    return a.exec();
}
