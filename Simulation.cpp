#include <time.h>
#include "Simulation.h"


std::uniform_int_distribution<int> Simulation::distributor(1, 1000);

std::default_random_engine Simulation::generator(time(NULL));

std::pair<unsigned,unsigned>
Simulation::gacha()
{
	if (TrialTime % 2000 == 0)
		generator = std::default_random_engine(time(NULL));
	unsigned int URNum = 0, SRNum = 0;
	for (int i = 0; i != 11; ++i)
	{
		int res = distributor(generator);
		if (res <= 10)
			++URNum;
		else if (res <= 100)
			++SRNum;
	}
	std::cout << "NO. " << TrialTime << " result:"
		<< URNum << " UR, " << SRNum << " SR." << std::endl;

	++TrialTime;
	return std::pair<unsigned, unsigned>(URNum, SRNum);
}

std::pair<unsigned, unsigned>
Simulation::gacha_WithoutEcho()
{
	if (TrialTime % 2000 == 0)
		generator = std::default_random_engine(time(NULL));
	unsigned int URNum = 0, SRNum = 0;
	for (int i = 0; i != 11; ++i)
	{
		int res = distributor(generator);
		if (res <= 10)
			++URNum;
		else if (res <= 100)
			++SRNum;
	}
	++TrialTime;
	return std::pair<unsigned, unsigned>(URNum, SRNum);
}

void
Simulation::Start(bool Silenceflag = false)
{
	while (TrialTime!=setTrialTime)
	{
		decltype(gacha()) res;
		if (Silenceflag)
			res = gacha_WithoutEcho();
		else
		    res = gacha();
		++(result[res.first][res.second]);
	}
}

void
Simulation::Start_Always_SR(bool Silenceflag = false)
{
	while (TrialTime != setTrialTime)
	{
		decltype(gacha()) res;
		if (Silenceflag)
			res = gacha_WithoutEcho();
		else
			res = gacha();
		if (res.first == 0 && res.second == 0)
			++(result[0][1]); //Simulate the condition that you always get a SR card.
		else
			++(result[res.first][res.second]);
	}
}

std::ostream&
operator<<(std::ostream& os, const Simulation &sim)
{
	std::cout << "Trial Result:" << std::endl
		<< "Simple Number: " << sim.TrialTime <<std::endl;
	
	for (auto UR_iter = sim.result.begin();
		UR_iter != sim.result.end();
		++UR_iter)
	{
		for (auto SR_iter = UR_iter->second.begin();
			SR_iter != UR_iter->second.end();
			++SR_iter)
			std::cout << UR_iter->first << " UR and "
			<< SR_iter->first << " SR happened "
			<< SR_iter->second << " times."
			<< " Frequency is " << (static_cast<double>(SR_iter->second) / sim.TrialTime * 100)
			<<"%" << std::endl;
	}
	auto ur_num = sim.URNum();
	std::cout << "Getting UR event happened " << ur_num << " times."
		<< " Frequency is " << (static_cast<double>(ur_num) / sim.TrialTime * 100) << "%" << std::endl;
	return os;
}

unsigned long
Simulation::URNum() const
{
	unsigned long sum = 0;
	for (auto UR_iter = result.find(1);
		UR_iter != result.end();
		++UR_iter)
	{
		for (auto SR_iter = UR_iter->second.begin();
			SR_iter != UR_iter->second.end();
			++SR_iter)
		{
			sum += (SR_iter->second);
		}
	}
	return sum;
}