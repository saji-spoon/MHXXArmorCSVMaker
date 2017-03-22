#pragma once
#include<QModelIndex>

enum class CellType
{
        Blank,
        SkillNames,
        ArmorNames,
        Values
};

CellType getCellType(const QModelIndex& index);
