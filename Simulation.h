#ifndef SIMULATION_H
#define SIMULATION_H

#include <map>
#include <set>
#include <random>
#include <iostream>

class Simulation
{
	friend
		std::ostream& operator<<(std::ostream&, const Simulation&);
public:
	Simulation(unsigned long setTime) :setTrialTime(setTime)
	{}

	void Start(bool);
	void Start_Always_SR(bool);
	unsigned long URNum() const;

private:
	static std::uniform_int_distribution<int> distributor;
	static std::default_random_engine generator;

	unsigned long setTrialTime;
	unsigned long TrialTime = 0;

	std::map<unsigned, std::map<unsigned,unsigned>> result;

	std::pair < unsigned, unsigned >
		gacha();
	std::pair < unsigned, unsigned >
		gacha_WithoutEcho();
};

#endif