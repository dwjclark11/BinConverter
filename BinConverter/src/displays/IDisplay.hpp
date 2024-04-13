#pragma once

namespace BinConverter {
	/*
	* @brief Simple Interface used for poly morphism amongst the Displays
	*/
	struct IDisplay
	{
		virtual void Draw() = 0;
		virtual void Update() = 0;
	};
}