#include "equationsGUI.h"
#include "equation.h"
#include <QMessageBox>

equationsGUI::equationsGUI(Service* service, QWidget *parent)
    : QMainWindow(parent), service{service}
{
    ui.setupUi(this);

    connectSignalsAndSlots();
    populateList();
}

equationsGUI::~equationsGUI()
{}

void equationsGUI::connectSignalsAndSlots() {
    QObject::connect(ui.updateButton, &QPushButton::clicked, this, &equationsGUI::updateEquation);
    QObject::connect(ui.computeSolutionsButton, &QPushButton::clicked, this, &equationsGUI::computeSolutions);
}

void equationsGUI::populateList() {
    std::vector<Equation> allEquations = service->getAll();

    ui.allEquationsList->clear();
    for (Equation equation : allEquations) {
        QListWidgetItem* listItem = new QListWidgetItem{ QString::fromStdString(equation.toString()) };
        if (equation.hasRealSolution())
            listItem->setFont(QFont(QString("Arial"), -1, QFont::Bold, false));
        ui.allEquationsList->addItem(listItem);

    }
}

int equationsGUI::getSelectedIndex() const {
    auto selected = ui.allEquationsList->selectionModel()->selectedIndexes();
    if (selected.count() == 0)
        return -1;
    return selected[0].row();
}

void equationsGUI::updateEquation() {
    int rowSelected = getSelectedIndex();
    
    int aInput = atoi(ui.coefficientAInput->text().toStdString().c_str());
    int bInput = atoi(ui.coefficientBInput->text().toStdString().c_str());
    int cInput = atoi(ui.coefficientCInput->text().toStdString().c_str());

    service->updateByIndex(rowSelected, aInput, bInput, cInput);
    populateList();
}

void equationsGUI::computeSolutions() {
    int rowSelected = getSelectedIndex();

    std::pair<std::string, std::string> solutions = service->getSolutions(rowSelected);
    ui.firstSolution->setText(QString::fromStdString(solutions.first));
    ui.secondSolution->setText(QString::fromStdString(solutions.second));
}
