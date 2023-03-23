#pragma once
#include <iostream>

class Command
{
protected:

public:
	explicit Command() {};
	virtual ~Command() = default;
	virtual void Excecute() = 0;
private:

};

class Jump : public Command
{
public:
	void Excecute() override { std::cout << "jump\n"; };
};