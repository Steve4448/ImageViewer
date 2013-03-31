#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QNetworkReply>
#include <QPixmap>
#include <QTimer>

struct ImageFrame {
	QPixmap pixelsNom;
	QPixmap thumbnail;
	int frameDelay;
};

class ImageView : public QWidget
{
		Q_OBJECT
	public:
		explicit ImageView(QNetworkReply*, QWidget *parent = 0);
		~ImageView();

		void paintEvent(QPaintEvent*);
		void mouseReleaseEvent(QMouseEvent*);
		void moveAnimated(int x, int y);
	private:
        int _x;
        int _y;
        int _width;
        int _height;
		QList<ImageFrame*> frames;

		QNetworkReply* imageData;
		QTimer frameTimer;
		int frameIndex;
		double percent;
		bool errored;
		bool drawHuge;

	public slots:
		void recievedData();
        void nextFrame();
		void progress(qint64, qint64);
		void downloadError(QNetworkReply::NetworkError);
};
#endif // IMAGEVIEW_H
