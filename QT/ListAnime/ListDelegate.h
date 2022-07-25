#ifndef LISTDELEGATE_H
#define LISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class ListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ListDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    void drawSelectRect(QPainter* painter, QRect rectSelect, bool bFill) const;
    QImage *pmsgIcon;


protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // LISTDELEGATE_H
