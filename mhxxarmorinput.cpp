#include "mhxxarmorinput.h"

MHXXArmorInput::MHXXArmorInput(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    ArmorSkillModel* mdl = new ArmorSkillModel(this);
    ArmorSkillDelegate* dlg = new ArmorSkillDelegate(this);

    ui.astv->setModel(mdl);
    ui.astv->setItemDelegate(dlg);
    ui.astv->setColumnWidth(1, 45);

    connect(ui.popColumnButton, SIGNAL(clicked()), mdl, SLOT(popColumn()));
    connect(ui.pushColumnButton, SIGNAL(clicked()), mdl, SLOT(pushColumn()));
    connect(ui.registerButton, SIGNAL(clicked()), this, SLOT(startSave()));
    connect(ui.clearButton, SIGNAL(clicked()), mdl, SLOT(clear()));
    connect(this, SIGNAL(saveStarted()), mdl, SLOT(save()));
    connect(mdl, SIGNAL(resultPrepared(std::vector<ArmorInfo>)), this, SLOT(save(std::vector<ArmorInfo>)));


}
bool MHXXArmorInput::confirm(const std::vector<ArmorInfo>& results)
{
        QString message = "";
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("Shift-JIS"));

        message += QString::fromLocal8Bit("ˆÈ‰º‚Ì“à—e‚Åo—Í‚µ‚Ü‚·‚©H\n");

        for (const auto& result : results)
        {
                if (result.name.isEmpty())
                {
                        message += QString::fromLocal8Bit("\n");
                        continue;
                }

                message += result.name + " ";
                message += ((result.battleType == 0) ? QString::fromLocal8Bit("—¼") : ((result.battleType == 1) ? QString::fromLocal8Bit("Œ•") : "ƒK"));
                message += "S" + QString::number(result.slot) + " ";
                for (const auto& skill : result.skills)
                {
                        if (skill.name.isEmpty()) continue;
                        message += skill.name + ((skill.sp > 0) ? "+" : "") + QString::number(skill.sp);
                        message += " / ";
                }
                message += "\n";
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "confirm",
                message,
                QMessageBox::Yes | QMessageBox::No);

        return reply == QMessageBox::Yes;
}
void MHXXArmorInput::save(std::vector<ArmorInfo> results)
{
        std::array<std::ofstream, 5> files;
        std::array<std::string, 5> filenames =
        {
                "work/MHXX_EQUIP_HEAD.csv",
                "work/MHXX_EQUIP_BODY.csv",
                "work/MHXX_EQUIP_ARM.csv",
                "work/MHXX_EQUIP_WST.csv",
                "work/MHXX_EQUIP_LEG.csv"
        };

        for (int i = 0; i < filenames.size(); ++i)
        {
                files[i].open(filenames[i], std::ios::app);

                if (!files[i])
                {
                        std::cout << "Save failed:" << filenames[i] << "\n";
                        return;
                }
        }

        if (!confirm(results)) return;

        for (auto& result = results.begin(); result != results.end(); ++result)
        {
                int armorIdx = std::distance(results.begin(), result);

                if (result->name.isEmpty()) continue;//No Result

                files[armorIdx] << result->name.toLocal8Bit().data()/*Name*/ << ",0,"/*ForM*/
                        << result->battleType/*BorG*/ << ",8,"
                        << result->slot/*Slot*/ << ",1,1,0," << ((result->battleType == 2) ? "75,75" : "150,150") << ",0,0,0,0,0,";

                for (const auto& skill : result->skills)
                {
                        if (skill.name.isEmpty())
                        {
                                files[armorIdx] << ",,";
                        }
                        else
                        {
                                files[armorIdx] << skill.name.toLocal8Bit().data() << "," << skill.sp << ",";
                        }
                }

                files[armorIdx] << ",,,,‘fÞ,1,‘fÞ,1,‘fÞ,1,‘fÞ,1"
                        << "\n";
        }



}