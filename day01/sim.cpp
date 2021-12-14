#include "Vverilog.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char** argv, char** env) {
	VerilatedContext* contextp = new VerilatedContext;
	contextp->commandArgs(argc, argv);
	Verilated::traceEverOn(true);
	Vverilog* top = new Vverilog{contextp};
	VerilatedVcdC *m_trace = new VerilatedVcdC;
	top->trace(m_trace, 5);
	m_trace->open("waveform.vcd");

	// reset
	top->clk = 0;
	top->rst = 0;
	top->eval();

	top->rst = 1;
	top->eval();
	top->rst = 0;

	int out = 0;
	size_t simTime = 0;

	auto simulateClock = [&](auto inp) -> void {
		top->inp = inp;
		top->clk = 1;
		top->eval();
		m_trace->dump(simTime++);

		out = top->out;
		top->clk = 0;
		top->eval();
		m_trace->dump(simTime++);
	};

	// Open File and run
	std::ifstream dat_ein;
	dat_ein.open("../input");
	std::string line;
	while(std::getline(dat_ein, line)) {
		simulateClock(std::stoi(line));
	}

	dat_ein.close();


	std::cout << "Output was: " << out << "\n";

	m_trace->close();

	delete top;
	delete contextp;
	delete m_trace;
	return 0;
}
