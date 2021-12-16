#include "Vday02.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char** argv, char** env) {
	auto contextp = std::make_unique<VerilatedContext>();
	contextp->commandArgs(argc, argv);
	Verilated::traceEverOn(true);
	auto top = std::make_unique<Vday02>(contextp.get());
	auto m_trace = std::make_unique<VerilatedVcdC>();
	top->trace(m_trace.get(), 5);
	m_trace->open("waveform.vcd");


	// Datatype
	enum movement : uint8_t {
		FORWARD = 0,
		UP = 1,
		DOWN = 2
	};

	// Reset
	top->clk = 0;
	top->rst = 0;
	top->eval();

	top->rst = 1;
	top->eval();
	top->rst = 0;


	size_t simTime = 0;
	auto simulateCycle = [&](movement move, uint32_t distance) -> uint32_t {
		top->cmd = move;
		top->distance = distance;
		top->clk = 1;
		top->eval();
		m_trace->dump(simTime++);


		top->clk = 0;
		top->eval();
		m_trace->dump(simTime++);

		return top->out;
	};


	// Read file
	std::ifstream dat_ein;
	dat_ein.open("../input");

	std::string strCmd;
	movement cmd;
	uint32_t value;
	uint32_t retVal;

	while(dat_ein >> strCmd >> value) {
		if(strCmd == "forward") {
			cmd = FORWARD;
		} else if(strCmd == "up") {
			cmd = UP;
		} else if(strCmd == "down") {
			cmd = DOWN;
		} else {
			std::cout << "unknown identifier \"" << strCmd << "\"\n";
			return -1;
		}

		retVal = simulateCycle(cmd, value);
	}

	std::cout << "Result is: " << retVal << "\n";

	// Close Stuff
	dat_ein.close();

	return 0;
}
