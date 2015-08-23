#ifndef SUPERLABEL_H
#define SUPERLABEL_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class SuperLabel : public QPushButton,  public QLabel
{
    //Q_OBJECT
public:
    explicit SuperLabel(char *str);

signals:

public slots:

};

#endif // SUPERLABEL_H
