#include"indexutil.h"

CellType getCellType(const QModelIndex& index)
{
        const int ir = index.row();
        const int ic = index.column();

        if (ir >= 1 && ic >= 1)
        {
                return CellType::Values;
        }
        else if (ir != 0)//column == 0
        {
                return CellType::ArmorNames;
        }
        else if (ic != 0)//row == 0
        {
                return CellType::SkillNames;
        }
        else
        {
                return CellType::Blank;
        }
}