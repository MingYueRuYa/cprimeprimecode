#ifndef SIGNALMAP_H
#define SIGNALMAP_H

#include <QSignalMapper>
#include <QWidget>

class signalmap : public QWidget
 {
     Q_OBJECT

 public:
     signalmap(QStringList texts, QWidget *parent = 0);

 protected slots:
     void doClicked(const QString &text);

 private:
     QSignalMapper *signalMapper;
 };

#endif // SIGNALMAP_H
