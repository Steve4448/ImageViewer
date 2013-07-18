#include "imagegridlayout.h"
#include <QDebug>
#include "imageview.h"

ImageGridLayout::ImageGridLayout() {
	x = y = GAP;
}

void ImageGridLayout::update() {
	x = y = GAP;
	bool first = true;
	foreach(QObject* qO, parent()->children()) {
		ImageView* view = qobject_cast<ImageView*>(qO);
		if(!view)
			continue;
		if(!first)
			if((y += (view->size().height() + GAP)) + view->size().height() >= geometry().height()) {
				x += (view->size().width() + GAP);
				y = GAP;
			}
		view->moveAnimated(x, y);
		first = false;
	}
}

void ImageGridLayout::setGeometry(const QRect & r) {
	QLayout::setGeometry(r);
	update();
}

void ImageGridLayout::addItem(QLayoutItem *) {
	update();
}

int ImageGridLayout::count() const {
	return parent()->children().count() - 1;
}

Qt::Orientations ImageGridLayout::expandingDirections() const {
	return Qt::Horizontal | Qt::Vertical;
}

bool ImageGridLayout::hasHeightForWidth() const {
	return true;
}

int	ImageGridLayout::heightForWidth ( int ) const {
	return 0;
}

void ImageGridLayout::invalidate () {

}

QLayoutItem * ImageGridLayout::itemAt ( int ) const {
    return 0;
}

QSize ImageGridLayout::maximumSize () const {
	return QSize(x + DEFAULT_SIZE_X + GAP, y + GAP);
}

int	ImageGridLayout::minimumHeightForWidth ( int ) const {
	return 0;
}

QSize ImageGridLayout::minimumSize () const {
	return QSize(x + DEFAULT_SIZE_X + GAP, y + GAP);
}

QSize ImageGridLayout::sizeHint() const {
	return QSize(x + DEFAULT_SIZE_X + GAP, y + GAP);
}

QLayoutItem * ImageGridLayout::takeAt ( int ) {
    return 0;
}
