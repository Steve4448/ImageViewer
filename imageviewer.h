#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHBoxLayout>
#include "imagegridlayout.h"

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QMainWindow
{
	Q_OBJECT

public:
	explicit ImageViewer(QWidget *parent = 0);
	~ImageViewer();

private:
	Ui::ImageViewer *ui;
	QNetworkAccessManager accessManager;
	QNetworkReply* contentDownloader;
	QStringList loadedUrls;
	ImageGridLayout* gridLayout;

public slots:
	void fetchImages();
	void finishedFetching();
};

#endif // IMAGEVIEWER_H
