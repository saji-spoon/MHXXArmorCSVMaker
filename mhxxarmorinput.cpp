#include "mhxxarmorinput.h"

MHXXArmorInput::MHXXArmorInput(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ArmorSkillModel* mdl = new ArmorSkillModel(this);
    ArmorSkillDelegate* dlg = new ArmorSkillDelegate(this);

    ui.astv->setModel(mdl);
    ui.astv->setItemDelegate(dlg);

    connect(ui.popColumnButton, SIGNAL(clicked()), mdl, SLOT(popColumn()));
    connect(ui.pushColumnButton, SIGNAL(clicked()), mdl, SLOT(pushColumn()));
    connect(ui.registerButton, SIGNAL(clicked()), mdl, SLOT(save()));

}
