/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#include "config.h"
#include "pwmdialog.h"

PWMDialog::PWMDialog(QWidget *pParent)
    :QDialog(pParent)
{
    mTipLabel = new QLabel(this);
    mTipLabel->setText(tr("You have content not to save."));
    mTipLabel->setAlignment(Qt::AlignCenter);
    mOkButton = new QPushButton(this);
    mOkButton->setText(tr("save"));
    connect(mOkButton, SIGNAL(clicked()), this, SLOT(DoOk()));
    mCancelButton= new QPushButton(this);
    mCancelButton->setText(tr("cancel"));
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(DoCancel()));

    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    QVBoxLayout *vLineEditBoxLayout = new QVBoxLayout(this);
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);

    vLineEditBoxLayout->addWidget(mTipLabel);
    hBoxLayout->addSpacerItem(new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hBoxLayout->addWidget(mOkButton);
    hBoxLayout->addWidget(mCancelButton);

    vBoxLayout->addLayout(vLineEditBoxLayout);
    vBoxLayout->addLayout(hBoxLayout);
    setWindowTitle(APPLICATION_NAME);

    setFixedSize(300, 100);
    //模态窗口
    setModal(true);
}

PWMDialog::~PWMDialog()
{

}

void PWMDialog::DoOk()
{
    accept();
}

void PWMDialog::DoCancel()
{
    reject();
}
