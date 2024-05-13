#pragma once

// Component interface
struct BaseComponent
{
protected:
	static int nextID;
};

template<typename T> class Component : public BaseComponent
{
	// Assigns a unique ID to a component type.
	static int getID()
	{
		return nextID++;
	}
};