#include "systemc.h"
#include "modules.h"

void multiplier::multiply_process() {

	product.write(multiplicandA.read() * multiplicandB.read());
}