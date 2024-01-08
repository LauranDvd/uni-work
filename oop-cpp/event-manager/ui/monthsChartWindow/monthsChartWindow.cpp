#include "monthsChartWindow.h"
#include "adminService.h"
#include "utilities.h"

MonthsChartWindow::MonthsChartWindow(AdminService* service, QWidget* parent) : service{service}, QWidget{parent} {
	ui.setupUi(this);
	makeThePlot();
}

MonthsChartWindow::~MonthsChartWindow() {
}

void MonthsChartWindow::makeThePlot() {
	auto plot = ui.monthsPlot;

	plot->setBackground(QBrush(QColor("navy")));

	QCPBars* monthBar;
	monthBar = new QCPBars(plot->xAxis, plot->yAxis);
	monthBar->setName(QString::fromStdString("Events"));
	monthBar->setPen(QPen(QColor(randomColorString().c_str())));
	monthBar->setBrush(QColor(randomColorString().c_str()));
	
	QVector<double> ticks;
	QVector<QString> labels;
	for (int i = 1; i <= 12; i++) {
		ticks << i;
		labels << QString::fromStdString(monthFromIntToString(i));
	}

	QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
	textTicker->addTicks(ticks, labels);
	plot->xAxis->setTicker(textTicker);
	plot->xAxis->setTickLabelRotation(60);
	plot->xAxis->setSubTicks(false);
	plot->xAxis->setTickLength(0, 10);
	plot->xAxis->setRange(0, 13);
	plot->xAxis->setBasePen(QPen(Qt::white));
	plot->xAxis->setTickPen(QPen(Qt::white));
	plot->xAxis->setTickLabelColor(Qt::white);
	plot->xAxis->setLabelColor(Qt::white);

	plot->yAxis->setRange(0, 10);
	plot->yAxis->setPadding(5); 
	plot->yAxis->setLabel("Number of events");
	plot->yAxis->setBasePen(QPen(Qt::white));
	plot->yAxis->setTickPen(QPen(Qt::white));
	plot->yAxis->setTickLabelColor(Qt::white);
	plot->yAxis->setLabelColor(Qt::white);
	plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));

	QVector<double> data;
	for (int i = 0; i < 12; i++) {
		int countEventsInThatMonth = service->numberOfEventsInMonth(i + 1);
		data << countEventsInThatMonth;
	}
	monthBar->setData(ticks, data);

	plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
}
