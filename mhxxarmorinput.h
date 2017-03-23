#pragma once

#include <QtWidgets/QWidget>
#include<qtextcodec>
#include "ui_mhxxarmorinput.h"
#include "armorskillmodel.h"
#include "armorskilldelegate.h"
#include"armorinfo.h"
#include<array>

class MHXXArmorInput : public QWidget
{
    Q_OBJECT

public:
    MHXXArmorInput(QWidget *parent = Q_NULLPTR);
public slots:
        void startSave()
        {                
                int bt = ui.bladeRadio->isChecked() ? 1 :
                                (ui.gunnerRadio->isChecked() ? 2 : 
                                                                0);       
                ui.astv->model()->setData(QModelIndex(), bt, Qt::UserRole);

                emit saveStarted();
        }

        bool confirm(const std::vector<ArmorInfo>& results);

        void save(std::vector<ArmorInfo> results);


signals:
        void saveStarted(); 
private:
    Ui::MHXXArmorInputClass ui;
};
