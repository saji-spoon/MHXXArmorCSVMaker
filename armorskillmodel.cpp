#include"ArmorSkillModel.h"

#define DEBUG_MODEL_ON

ArmorSkillModel::ArmorSkillModel(QObject* parent)
        :QAbstractTableModel(parent),
        m_armorSkillTable(SKILLTABLE_ROW*SKILLTABLE_COLUMN, 0),
        m_skillNames(4, ""),
        m_armorNames(SKILLTABLE_ROW, ""),
        m_slots(SKILLTABLE_ROW, 0)
{
#ifdef DEBUG_MODEL_ON
        m_armorNames =
        {
                QString::fromLocal8Bit("ナルガXヘルム"),
                QString::fromLocal8Bit("ナルガXメイル"),
                QString::fromLocal8Bit(""),
                QString::fromLocal8Bit("ナルガXフォールド"),
                QString::fromLocal8Bit("ナルガXグリーヴ")
        };

        m_skillNames = 
        {
                QString::fromLocal8Bit("達人"),
                QString::fromLocal8Bit("回避距離"),
                QString::fromLocal8Bit("回避性能"),
                QString::fromLocal8Bit(""),
        };

        m_armorSkillTable[storeDataIndex(0, 0)] = 3;
        m_armorSkillTable[storeDataIndex(0, 1)] = 3;
        m_armorSkillTable[storeDataIndex(0, 2)] = 3;
        m_armorSkillTable[storeDataIndex(1, 0)] = 4;
        m_armorSkillTable[storeDataIndex(1, 1)] = 2;
        m_armorSkillTable[storeDataIndex(1, 2)] = 1;
        m_armorSkillTable[storeDataIndex(3, 0)] = 3;

	m_slots = {1, 1, 0, 1, 3};

#endif

}


int ArmorSkillModel::rowCount(const QModelIndex &parent) const
{
        return SKILLTABLE_ROW +1;
}

int ArmorSkillModel::columnCount(const QModelIndex &parent) const
{
        return m_skillNames.size()+2;
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
                case CellType::Slot:
                        return m_slots[index.row() - 1];
                        break;
                case CellType::SkillNames:
                        return m_skillNames[index.column() - 2];
                case CellType::ArmorNames:
                        return m_armorNames[index.row() - 1];
                default:
                        if (index.column() == 1) return QString::fromLocal8Bit("スロ");
                        return QVariant();
                        break;
                }                
	default:
                return QVariant();
        }

}
bool ArmorSkillModel::setData(const QModelIndex & index, const QVariant & value, int role)
{

        if(role == Qt::UserRole)
        {
                m_battleType = value.toInt();
                return true;
        }

        if (role != Qt::EditRole) return false;

        switch (getCellType(index))
        {
        case CellType::Values:
                m_armorSkillTable[storeDataIndex(index)] = value.toInt();
                break;
        case CellType::Slot:
                m_slots[index.row() - 1] = value.toInt();
                break;
        case CellType::SkillNames:
                m_skillNames[index.column() - 2] = value.toString();
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
                        return (section <= 1) ? "" : "Skill" + QString::number(section-1);

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
        if (index.row() == 0 && index.column() <= 1) return Qt::ItemIsEnabled;

        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

ArmorInfo ArmorSkillModel::getArmorResult(int armorIdx)
{

        ArmorInfo result;

        if (m_armorNames[armorIdx].isEmpty())
        {
                //No result 
                result.name = "";
                return result;
        }

        result.name = m_armorNames[armorIdx];
        result.battleType = (armorIdx == 0) ? 0 : m_battleType;
        result.slot = m_slots[armorIdx];

        {
                int row = armorIdx;
                int count = 0;

                for (int column = 0; column < columnCount(); ++column)
                {
                        const int sp = m_armorSkillTable[storeDataIndex(row, column)];
                        if (sp != 0 && !m_skillNames[column].isEmpty())
                        {
                                result.skills[count] = { m_skillNames[column], sp };
                                ++count;
                        }
                        if (count == 3) break;
                }

                for (; count < 3; ++count)
                {
                        result.skills[count] = { "", 0 };
                }
        }
        return result;
}

void ArmorSkillModel::save()
{
        std::vector<ArmorInfo> results(SKILLTABLE_ROW);

        for (int armorIdx = 0; armorIdx < results.size(); ++armorIdx)
        {
                results[armorIdx] = getArmorResult(armorIdx);
        }

        //威圧の逆髪,0,0,7,1,6,99,0,35,66,5,5,5,5,5,本気,4,肉食,4,気配,-4,,,,,地下闘技場入場券,1,獰猛化巨獣毛,1,恐暴竜の頭殻,2,炎王龍のたてがみ,4

        emit resultPrepared(results);


}

void ArmorSkillModel::clear()
{
        std::fill(m_armorNames.begin(), m_armorNames.end(), "");
        std::fill(m_armorSkillTable.begin(), m_armorSkillTable.end(), 0);
        std::fill(m_skillNames.begin(), m_skillNames.end(), "");
        std::fill(m_slots.begin(), m_slots.end(), 0);

        QModelIndex topLeft = index(0, 0);
        QModelIndex bottomRight = index(rowCount()-1, columnCount()-1);

        emit dataChanged(topLeft, bottomRight);
}
