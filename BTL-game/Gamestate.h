#pragma once


#include "Game.h"

class CGameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(Game* game) = 0;
	virtual void Update(Game* game) = 0;
	virtual void Draw(Game* game) = 0;

	void ChangeState(Game* game, CGameState* state) {
		game->ChangeState(state);
	}

protected:
	CGameState() { }
};