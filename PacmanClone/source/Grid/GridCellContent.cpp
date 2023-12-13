#include "PacmanCore.h"
#include "GridCellContent.h"
#include "GridCell.h"

void GridCellContent::SetCell(std::shared_ptr<GridCell> NewParent)
{
    if(ParentCell && NewParent)
    {
        std::shared_ptr<GridCellContent> This = ParentCell->RemoveContent(this);
        ParentCell = NewParent;
        if (This != nullptr)
            ParentCell->AddContent(This);
    }
    else
    {
        ParentCell = NewParent;
    }
}
