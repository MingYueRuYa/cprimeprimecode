#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSpinBox>
#include <QWidget>
#include <QStyleOptionViewItem>

class EditorDelegate : public QItemDelegate
{
	Q_OBJECT

public:
        EditorDelegate(QObject *pParent = 0);

		~EditorDelegate();

        QWidget *createEditor(QWidget *pParent, const QStyleOptionViewItem &pOption, const QModelIndex &pIndex) const;

        void setEditorData(QWidget *pEditor, const QModelIndex &pIndex) const;

        void setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &pIndex) const;

        void updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &option, const QModelIndex &pIndex) const;

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif //DELEGATE_H
