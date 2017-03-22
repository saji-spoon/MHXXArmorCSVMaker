#pragma once
#include<QStyledItemDelegate>
#include<qspinbox>
#include<QLineEdit>
#include"indexutil.h"

class ArmorSkillDelegate : public QStyledItemDelegate
{
public:
        ArmorSkillDelegate(QWidget* parent = nullptr)
                :QStyledItemDelegate(parent)
        {}

        QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

        void setEditorData(QWidget *editor, const QModelIndex &index) const override;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};