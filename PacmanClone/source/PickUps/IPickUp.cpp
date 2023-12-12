#include "PacmanCore.h"
#include "IPickUp.h"
#include "Grid\GridCell.h"

IPickUp::IPickUp(std::shared_ptr<GridCell> NewParent)
{
	SetCell(NewParent);
	EventCallback = NewParent->OnContentEnters.AddListener(
		[this](std::shared_ptr<GridCellContent> NewContent) {
		this->CheckNewCellContent(NewContent);
		});
}

void IPickUp::CheckNewCellContent(std::shared_ptr<GridCellContent> NewContent)
{
}

void IPickUp::UnbindEvent()
{
	if (auto Parent = GetCell())
	{
		Parent->OnContentEnters.RemoveListener(EventCallback);
	}
}
