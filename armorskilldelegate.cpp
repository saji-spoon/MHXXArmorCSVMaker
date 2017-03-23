#include "armorskilldelegate.h"

QWidget* ArmorSkillDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

        switch(getCellType(index))
        {
        case CellType::Values:
        {
                QSpinBox* spinbox = new QSpinBox(parent);
                spinbox->setMinimum(-10);
                spinbox->setMaximum(30);
                return spinbox;
        }
        case CellType::Slot:
        {
                QSpinBox* spinbox = new QSpinBox(parent);
                spinbox->setMinimum(0);
                spinbox->setMaximum(3);
                return spinbox;
        }
        case CellType::ArmorNames:
        case CellType::SkillNames:
        {
                QLineEdit* line = new QLineEdit(parent);
                return line;
        }
        default:
        {
                QSpinBox* spinbox = new QSpinBox(parent);
                return spinbox;
                break;
        }
        }

}

void ArmorSkillDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
        switch (getCellType(index))
        {
        case CellType::Values:
        case CellType::Slot:
        {
                QSpinBox* spinbox = static_cast<QSpinBox*>(editor);
                const int val = index.model()->data(index, Qt::EditRole).toInt();
                spinbox->setValue(val);
                break;
        }
        case CellType::ArmorNames:
        case CellType::SkillNames:
        {
                QLineEdit* line = static_cast<QLineEdit*>(editor);
                const QString val = index.model()->data(index, Qt::EditRole).toString();
                line->setText(val);
                break;
        }
        default:
                break;
        }
}

void ArmorSkillDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{

        switch (getCellType(index))
        {
        case CellType::Values:
        case CellType::Slot:
        {
                QSpinBox* spinbox = static_cast<QSpinBox*>(editor);
                model->setData(index, spinbox->value(), Qt::EditRole);
                break;
        }
        case CellType::ArmorNames:
        case CellType::SkillNames:
        {
                QLineEdit* line = static_cast<QLineEdit*>(editor);
                model->setData(index, line->text(), Qt::EditRole);
                break;
        }
        default:
                break;
        }
}

void ArmorSkillDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
        editor->setGeometry(option.rect);
}
