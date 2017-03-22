#include"ArmorSkillModel.h"

ArmorSkillModel::ArmorSkillModel(QObject* parent)
        :QAbstractTableModel(parent),
        m_armorSkillTable(SKILLTABLE_ROW*SKILLTABLE_COLUMN, 0),
        m_skillNames(4, ""),
        m_armorNames(SKILLTABLE_ROW, "")
{

}


int ArmorSkillModel::rowCount(const QModelIndex &parent) const
{
        return SKILLTABLE_ROW +1;
}

int ArmorSkillModel::columnCount(const QModelIndex &parent) const
{
        return m_skillNames.size()+1;
}

QVariant ArmorSkillModel::data(const QModelIndex &index, int role) const
{
        const int ic = index.column();
        const int ir = index.row();

        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:

                switch (getCellType(index))
                {
                case CellType::Values:
                {
                        const int sdIdx = storeDataIndex(index);
                        return m_armorSkillTable[sdIdx];
                }
                case CellType::SkillNames:
                        return m_skillNames[index.column() - 1];
                case CellType::ArmorNames:
                        return m_armorNames[index.row() - 1];
                default:
                        return QVariant();
                        break;
                }                
	default:
                return QVariant();
        }

}
bool ArmorSkillModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
        if(!(index.row() < rowCount()) || !(index.column() < columnCount()))
        {
                return false;
        }

        if (role != Qt::EditRole) return false;

        switch (getCellType(index))
        {
        case CellType::Values:
                m_armorSkillTable[storeDataIndex(index)] = value.toInt();
                break;
        case CellType::SkillNames:
                m_skillNames[index.column() - 1] = value.toString();
                break;
        case CellType::ArmorNames:
                m_armorNames[index.row() - 1] = value.toString();
                break;
        default:
                break;
        }


        return false;
}

QVariant ArmorSkillModel::headerData(int section, Qt::Orientation orientation, int role) const
{
        QString rowLabel[SKILLTABLE_ROW + 1] =
        {
                "",
                "Head",
                "Body",
                "Arm",
                "West",
                "Leg"
        };

        switch(role)
        {
        case Qt::DisplayRole:
                if(orientation == Qt::Horizontal)
                {
                        return (section == 0) ? "" : "Skill" + QString::number(section);

                }
                else if(orientation == Qt::Vertical)
                {
                        return (section < (SKILLTABLE_ROW + 1)) ? rowLabel[section] : "";
                }
                
                break;
        }

        return QVariant();
}

Qt::ItemFlags ArmorSkillModel::flags(const QModelIndex & index) const
{
        if (index.row() == 0 && index.column() == 0) return Qt::ItemIsEnabled;

        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void ArmorSkillModel::save()
{
        std::ofstream headFile("work/MHXX_EQUIP_HEAD.csv", std::ios::app);

        if (!headFile) 
        {
                std::cout << "Save failed\n";
                return;
        }

        headFile << "append,append";

}