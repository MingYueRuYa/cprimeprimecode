
#include "delegate.h"
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPainter>

EditorDelegate::EditorDelegate(QObject *pParent)
    :QItemDelegate(pParent)
{
	
}

EditorDelegate::~EditorDelegate()
{

}

QWidget *EditorDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &pOption, const QModelIndex &pIndex) const
{
	if (pIndex.column() == 1) {
		QDateTimeEdit *editor = new QDateTimeEdit(pParent);
		editor->setDisplayFormat("yyyy/M/dd");
		editor->setCalendarPopup(true);
		return editor;
	}
	else if (pIndex.column() == 2) {
		QSpinBox *editor = new QSpinBox(pParent);	
		editor->setMinimum(140);
        editor->setMaximum(200);
		return editor;
	}
	else if (pIndex.column() == 3) {
		QComboBox *editor = new QComboBox(pParent);
		editor->addItem(tr("TianJing"));
		editor->addItem(tr("BeiJing"));
		editor->addItem(tr("ShanDong"));
		editor->addItem(tr("ShanXi"));
		editor->addItem(tr("JiangSu"));
		editor->addItem(tr("AnHui"));
		return editor;
	}
	else {
		return QItemDelegate::createEditor(pParent, pOption, pIndex);
	}
}

void EditorDelegate::setEditorData(QWidget *pEditor, const QModelIndex &pIndex) const
{
    if(pIndex.column() == 1)		// birthday
    {
        QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(pEditor);
        if (dateEditor) {
            dateEditor->setDate(QDate::fromString(pIndex.model()->data(pIndex, Qt::EditRole).toString(), "yyyy/M/d"));
        }
    }
    else if(pIndex.column() == 2)	// height
    {
        QSpinBox *spinEditor = qobject_cast<QSpinBox *>(pEditor);
        if(spinEditor)
            spinEditor->setValue(pIndex.model()->data(pIndex, Qt::EditRole).toInt());
    }
    else if(pIndex.column() == 3)	// province
    {
        QComboBox *comboBox = qobject_cast<QComboBox *>(pEditor);
        if(comboBox)
        {
            int i = comboBox->findText(pIndex.model()->data(pIndex, Qt::EditRole).toString());
            comboBox->setCurrentIndex(i);
        }
    }
    else
        return QItemDelegate::setEditorData(pEditor, pIndex);
}

void EditorDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &pIndex) const
{
    if(pIndex.column() == 1)		// birthday
    {
        QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(pEditor);
        if (dateEditor) {
            pModel->setData(pIndex, dateEditor->date().toString("yyyy/M/d"));
        }
    }
    else if(pIndex.column() == 2)	// height
    {
        QSpinBox *spinEditor = qobject_cast<QSpinBox *>(pEditor);
        if(spinEditor)
            pModel->setData(pIndex, QString("%1").arg(spinEditor->value()));
    }
    else if(pIndex.column() == 3)	// province
    {
        QComboBox *comboBox = qobject_cast<QComboBox *>(pEditor);
        if(comboBox)
        {
            pModel->setData(pIndex, comboBox->currentText());
        }
    }
    else
        return QItemDelegate::setModelData(pEditor, pModel, pIndex);
}

void EditorDelegate::updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &option, const QModelIndex &pIndex) const
{
    pEditor->setGeometry (option.rect);
}

void EditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    static int position = 10;
    if (index.column () == 1) {
        position += 10;
        painter->drawRect(0, position, 10, 10);
    }
    else {
        QItemDelegate::paint (painter, option, index);
    }

}


