#include "stdafx.h"
#include "ControlGroup.h"

ControlGroup::ControlGroup()
{
}

void ControlGroup::AddControl(UIControl* control)
{
	this->controls.push_back(control);
}

void ControlGroup::OnDraw()
{
	for (int i = 0; i < controls.size(); i++)
		controls[i]->OnDraw();
}

void ControlGroup::OnUpdate()
{
	for (int i = 0; i < controls.size(); i++)
		controls[i]->OnUpdate();
}

void ControlGroup::OnEvent(GameEvent::Event* evt)
{
	for (int i = 0; i < controls.size(); i++)
		controls[i]->OnEvent(evt);

	//Check click
	if (evt->type == GameEvent::EVENT_TYPE::GEVENT_MOUSECLICK)
	{
		GameEvent::MouseClickEvent clickevt = *(GameEvent::MouseClickEvent*)evt;

		if (clickevt.button == GameEvent::MOUSEBUTTON::LEFT && clickevt.pressed == true)
		{
			for (int i = 0; i < controls.size(); i++)
			{
				if (clickevt.x >= controls[i]->bounds.left
					&& clickevt.x <= controls[i]->bounds.right
					&& clickevt.y >= controls[i]->bounds.top
					&& clickevt.y <= controls[i]->bounds.bottom)
				{
					controls[i]->focused = true;

					for (int j = 0; j < controls.size(); j++)
						if (j != i)
							controls[j]->focused = false;
				}
			}
		}
	}
}

ControlGroup::~ControlGroup()
{
}
