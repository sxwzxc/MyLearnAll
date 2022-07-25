#include "ListDelegate.h"
#include <QPainter>

ListDelegate::ListDelegate()
{
    pmsgIcon = new QImage("C:\\Users\\sxw\\Pictures\\qx.png");
    pmsgIcon = &pmsgIcon->scaled(50, 50);
}

void ListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    drawSelectRect(painter, option.rect, true);
    QRect rectItem = option.rect; /* 获取项矩形区域 */
    QPen treePen;
    treePen.setWidth(1);
    painter->setPen(treePen);
    QFont font;
    font.setPixelSize(20);
    painter->setFont(font);
    QString deviceID = index.data(Qt::UserRole + 1).toString();
    painter->drawText(rectItem.x() + 44, rectItem.y() + 53 - (index.data(Qt::UserRole + 1).toInt() * 5 / 6), 124, index.data(Qt::UserRole + 1).toInt(),
        Qt::AlignLeft | Qt::AlignTop, deviceID);
    QString text2 = index.data(Qt::DisplayRole).toString();
    painter->drawText(rectItem.x() + 44, rectItem.y() + 53 - (index.data(Qt::UserRole + 1).toInt() / 2), 124, (index.data(Qt::UserRole + 1).toInt() - 28) * 2,
        Qt::AlignLeft | Qt::AlignTop, text2);

    //painter->drawImage(rectItem.x() + 0, rectItem.y() + 53 - (index.data(Qt::UserRole + 1).toInt() / 2), msgIcon, 124, (index.data(Qt::UserRole + 1).toInt() - 28) * 2
    //);
    QImage msgIcon("C:\\Users\\sxw\\Pictures\\little.png");
    //painter->drawImage(rectItem.x() + 3, rectItem.y() + 53 - (index.data(Qt::UserRole + 1).toInt()), msgIcon, 0, 0, 50, (index.data(Qt::UserRole + 1).toInt() - 28) * 2);

}

void ListDelegate::drawSelectRect(QPainter* painter, QRect rectSelect, bool bFill) const
{
    if (bFill)
        painter->fillRect(rectSelect, QColor(12, 174, 255, 39));
    rectSelect.adjust(4, 4,
        -4, -4);
    painter->save();
    QPen bkPen;
    bkPen.setWidth(1);
    bkPen.setColor(QColor("#0CAEFF"));
    painter->setPen(bkPen);
    painter->drawPolyline(QVector<QPoint>{
        rectSelect.topLeft(), rectSelect.topRight(), rectSelect.bottomRight(),
            rectSelect.bottomLeft(), rectSelect.topLeft()});
    painter->restore();
}

QSize ListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    int high = index.data(Qt::UserRole + 1).toInt();
    return QSize(256, high);
}
