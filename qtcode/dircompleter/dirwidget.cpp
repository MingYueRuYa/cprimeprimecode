#include "dirwidget.h"

DirWidget::DirWidget()
{
   model = new QDirModel();
   tree = new QTreeView();
   tree->setModel (model);
   index = model->index(QDir::currentPath ());
   tree->expand (index);
   tree->scrollTo (index);
   //tree->header()->set

   completer = new QCompleter(this);
   completer->setModel(model);
   dirEdit = new QLineEdit(this);
   dirEdit->setText(QDir::currentPath ());
   dirEdit->setCompleter(completer);
   connect(dirEdit, SIGNAL(editingFinished()), this, SLOT(pathChanged()));

   layout = new QVBoxLayout();
   layout->addWidget(tree);
   layout->addWidget(dirEdit);
   setLayout(layout);

   resize(640, 480);
   setWindowTitle(tr("directory look"));
}

DirWidget::~DirWidget()
{
}

void DirWidget::pathChanged ()
{
    index = model->index (dirEdit->text ());
    tree->expand (index);
    tree->scrollTo (index);
}


