#pragma once

#include <QtWidgets/QWidget>
#include "ui_mhxxarmorinput.h"
#include "armorskillmodel.h"
#include "armorskilldelegate.h"

class MHXXArmorInput : public QWidget
{
    Q_OBJECT

public:
    MHXXArmorInput(QWidget *parent = Q_NULLPTR);

private:
    Ui::MHXXArmorInputClass ui;
};
