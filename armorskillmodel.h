#pragma once
#include<QAbstractTableModel>
#include<QFont>
#include<QTime>
#include<QTimer>
#include<vector>
#include<iostream>
#include<fstream>
#include"indexutil.h"
#include<QMessageBox>
#include"armorinfo.h"
#include<algorithm>

class ArmorSkillModel : public QAbstractTableModel
{
        Q_OBJECT
public:
        ArmorSkillModel(QObject* parent);
                
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;

public slots:
        void popColumn()
        {
                if (columnCount() <= 3) return;

                beginRemoveColumns(QModelIndex(), columnCount()-1, columnCount()-1);
                m_skillNames.pop_back();
                endRemoveColumns();
        }

        void pushColumn()
        {
                if (columnCount() >= 10) return;

                beginInsertColumns(QModelIndex(), columnCount(), columnCount());
                m_skillNames.push_back("");
                endInsertColumns();
        }

        void save();

        void clear();

signals:
        void resultPrepared(std::vector<ArmorInfo>);

private:
        std::vector<QString> m_armorNames;
        std::vector<int> m_slots;
        std::vector<QString> m_skillNames;

        std::vector<int> m_armorSkillTable;

        static const int SKILLTABLE_ROW = 5;
        static const int SKILLTABLE_COLUMN = 10;
        int m_battleType;
        

        int storeDataIndex(int row, int column)const
        {
                return column + row * SKILLTABLE_COLUMN;
        }

        int storeDataIndex(const QModelIndex& index)const
        {
                return storeDataIndex(index.row()-1, index.column()-2);
        }

        ArmorInfo getArmorResult(int armorIdx);


        


};