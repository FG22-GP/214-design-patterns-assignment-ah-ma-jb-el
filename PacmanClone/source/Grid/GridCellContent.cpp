#include "PacmanCore.h"
#include "GridCellContent.h"
#include "GridCell.h"

void GridCellContent::SetCell(std::shared_ptr<GridCell> NewParent)
{
    const std::shared_ptr<GridCellContent> This = std::make_shared<GridCellContent>();
    if(ParentCell)
    {
        ParentCell->RemoveContent(This);
    }
    ParentCell = std::move(NewParent);
    if(ParentCell)
    {
        ParentCell->AddContent(This);
    }
}
