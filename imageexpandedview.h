#ifndef IMAGEEXPANDEDVIEW_H
#define IMAGEEXPANDEDVIEW_H

#include <QDockWidget>

namespace Ui {
	class ImageExpandedView;
}

class ImageExpandedView : public QDockWidget
{
		Q_OBJECT
		
	public:
		explicit ImageExpandedView(QWidget *parent = 0);
		~ImageExpandedView();
		
	private:
		Ui::ImageExpandedView *ui;
};

#endif // IMAGEEXPANDEDVIEW_H
