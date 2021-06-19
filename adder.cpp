#include "systemc.h"
#include "modules.h"

void adder::add_process() {

	sum.write(summandA.read() + summandB.read());
}