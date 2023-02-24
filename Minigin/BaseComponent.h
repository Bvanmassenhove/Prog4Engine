#pragma once

class baseComponent
{
public:
	baseComponent() = default;
	virtual ~baseComponent() = default;

	baseComponent(const baseComponent& other) = delete;
	baseComponent(baseComponent&& other) = delete;
	baseComponent& operator=(const baseComponent& other) = delete;
	baseComponent& operator=(baseComponent&& other) = delete;
	
};