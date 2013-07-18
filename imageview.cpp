#include "imageview.h"
#include <QImageReader>
#include <QPainter>
#include <QDebug>

ImageView::ImageView(QNetworkReply* data, QWidget *parent) : QWidget(parent) {
	imageData = data;
	frameIndex = percent = 0;
	frameTimer.setSingleShot(true);
	errored = false;
	drawHuge = false;
	setMinimumSize(100, 100);
	data->setParent(this);
    _width = width();
    _height = height();
	connect(data, SIGNAL(finished()), this, SLOT(recievedData()));
	connect(data, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(progress(qint64,qint64)));
	connect(data, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(downloadError(QNetworkReply::NetworkError)));
}

void ImageView::recievedData() {
	QImageReader imageReader(imageData);
	if(imageData->error())
		goto errorcleanup;

	while(imageReader.canRead()) {
		ImageFrame* frame = new ImageFrame;
		frame->pixelsNom = QPixmap::fromImageReader(&imageReader);
		if(frame->pixelsNom.size() == QSize(0, 0))
			goto errorcleanup;
		frame->thumbnail = frame->pixelsNom.scaled(QSize(100, 100), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		if(frame->thumbnail.size() == QSize(0, 0))
			goto errorcleanup;
		frame->frameDelay = imageReader.nextImageDelay();
		frames.append(frame);
	}
	if(frames.size() > 1) {
		frameTimer.start(frames.at(0)->frameDelay);
		connect(&frameTimer, SIGNAL(timeout()), this, SLOT(nextFrame()));
	}
	repaint();
	goto cleanup;
errorcleanup:
	while(!frames.isEmpty())
	delete frames.takeFirst();
	errored = true;
cleanup:
	imageData->deleteLater();
}

void ImageView::nextFrame() {
	frameTimer.start(frames.at(++frameIndex >= frames.size() ? (frameIndex = 0) : frameIndex)->frameDelay);
	repaint();
}

void ImageView::paintEvent(QPaintEvent*) {
	QPainter p(this);
	if(errored) {
		p.setPen(Qt::darkRed);
		p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter | Qt::AlignHCenter, "Error Downloading.");
	} else {
		p.setPen(Qt::darkBlue);
		if(frames.isEmpty()) {
			p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter | Qt::AlignHCenter, QString("Downloading\n%1%").arg((int)(percent * 100.0)));
		} else {
			QPixmap image;
			if(drawHuge)
				image = frames.at(frameIndex)->pixelsNom;
			else
				image = frames.at(frameIndex)->thumbnail;
			p.drawPixmap(0, 0, width(), height(), image);
		}
	}
	p.setPen(Qt::gray);
	p.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void ImageView::progress(qint64 cur, qint64 tot) {
	if(tot == 0) {
		errored = true;
		repaint();
		return;
	}
	percent = (double)cur / (double)tot;
	repaint();
}

void ImageView::mouseReleaseEvent(QMouseEvent*) {
	if(!frames.isEmpty() && !drawHuge) {
		drawHuge = true;
		_width = frames.at(frameIndex)->pixelsNom.width();
		_height = frames.at(frameIndex)->pixelsNom.height();
	} else {
		drawHuge = false;
		_width = 100;
		_height = 100;
	}
	repaint();
}

void ImageView::moveAnimated(int x, int y){
	_x = x;
	_y = y;
    move(x, y); //FIXME: temporary replacement of a previous library usage.
}

void ImageView::downloadError(QNetworkReply::NetworkError qNE) {
	qDebug() << QString("%1 failed to load. Error # %2").arg(imageData->url().toString()).arg(qNE);
	errored = true;
}

ImageView::~ImageView(){ // cleanup resources
	foreach(ImageFrame* frame, frames)
		delete frame;
}
