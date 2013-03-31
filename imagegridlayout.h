#ifndef IMAGEGRIDLAYOUT_H
#define IMAGEGRIDLAYOUT_H
#define GAP 5
#include <QLayout>

class ImageGridLayout : public QLayout
{
		Q_OBJECT
	public:
		explicit ImageGridLayout();
		void setGeometry(const QRect &);
        void addItem (QLayoutItem *);
		int count () const;
		Qt::Orientations expandingDirections () const;
		bool hasHeightForWidth () const;
        int	heightForWidth (int) const;
		void invalidate ();
        QLayoutItem * itemAt (int) const;
		QSize maximumSize () const;
        int	minimumHeightForWidth (int) const;
		QSize minimumSize () const;
		QSize sizeHint () const;
        QLayoutItem * takeAt (int);
		void update();
		int x;
		int y;
};

#endif // IMAGEGRIDLAYOUT_H
