#include"indexutil.h"

CellType getCellType(const QModelIndex& index)
{
        const int ir = index.row();
        const int ic = index.column();

        if (ir >= 1 && ic >= 2)
        {
                return CellType::Values;
        }
        else if(ir >= 1 && ic == 1)
        {
                return CellType::Slot;
        }
        else if (ir >= 1 && ic == 0)
        {
                return CellType::ArmorNames;
        }
        else if (ir == 0 && ic >= 2)
        {
                return CellType::SkillNames;
        }
        else
        {
                return CellType::Blank;
        }
}