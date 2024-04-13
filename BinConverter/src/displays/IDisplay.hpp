#pragma once

namespace BinConverter {
	struct IDisplay
	{
		virtual void Draw() = 0;
		virtual void Update() = 0;
	};
}