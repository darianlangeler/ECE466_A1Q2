#include "systemc.h"
#include "modules.h"

void reg::reg_process() {

	while(1) {
		if (reset.read() == SC_LOGIC_1) output.write(0);
		else {
			output.write( input.read() );		
		}
		
		wait();
	}
}