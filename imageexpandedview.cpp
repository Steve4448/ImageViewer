#include "imageexpandedview.h"
#include "ui_imageexpandedview.h"

ImageExpandedView::ImageExpandedView(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::ImageExpandedView)
{
	ui->setupUi(this);
}

ImageExpandedView::~ImageExpandedView()
{
	delete ui;
}
