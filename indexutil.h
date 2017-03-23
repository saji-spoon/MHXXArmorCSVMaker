#pragma once
#include<QModelIndex>

enum class CellType
{
        Blank,
        SkillNames,
        ArmorNames,
        Values,
        Slot
};

CellType getCellType(const QModelIndex& index);
