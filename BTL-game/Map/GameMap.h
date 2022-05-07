#pragma once
#include"Layer.h"
#include<vector>

class GameMap
{
public:
	GameMap() {};
	void Update()
	{
		for (int i = 0; i < m_MapLayers.size(); i++)
		{
			m_MapLayers[i]->Update();

		}
	}
	void Render()
	{
		for (int i = 0; i < m_MapLayers.size(); i++)
		{
			m_MapLayers[i]->Render();

		}
	}
	std::vector<Layer*> GetMapLayers()
	{
		return m_MapLayers;
	}

private:
	std::vector<Layer*> m_MapLayers;
};