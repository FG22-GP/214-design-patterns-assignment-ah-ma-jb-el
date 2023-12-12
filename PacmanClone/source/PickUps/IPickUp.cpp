#include "PacmanCore.h"
#include "IPickUp.h"
#include "Grid\GridCell.h"
#include "ZakuMan\ZakuMan.hpp"

void IPickUp::BindToCell(std::shared_ptr<GridCell> Cell)
{
	EventCallback = Cell->OnContentEnters.AddListener(
		[this](std::shared_ptr<GridCellContent> NewContent) {
		this->CheckNewCellContent(NewContent);
		});
}

void IPickUp::CheckNewCellContent(std::shared_ptr<GridCellContent> NewContent)
{
	std::cout << "Checking new cell content" << std::endl;
	std::shared_ptr<ZakuMan> CastContent = std::dynamic_pointer_cast<ZakuMan>(NewContent);
	if (CastContent != nullptr)
	{
		std::cout << "Found Pacman" << std::endl;
		UnbindEvent();
		OnPickUp();
	}
}

void IPickUp::UnbindEvent()
{
	if (auto Parent = GetCell())
	{
		Parent->OnContentEnters.RemoveListener(EventCallback);
	}
}
