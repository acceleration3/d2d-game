#include "GameEvent.h"

class Screen
{

public:
	virtual void OnDraw() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEvent(GameEvent::Event* evt) = 0;
}