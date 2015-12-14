#ifndef DIRWIDGET_H
#define DIRWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QModelIndex>
#include <QDirModel>
#include <QLineEdit>
#include <QCompleter>
#include <QTreeView>

class DirWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DirWidget();

    virtual ~DirWidget();

signals:

private slots:
        void pathChanged();

private:
        QModelIndex index;
        QVBoxLayout *layout;
        QDirModel *model;
        QTreeView *tree;
        QLineEdit *dirEdit;
        QCompleter *completer;
};

#endif // DIRWIDGET_H
