#include "systemc.h"
#include <iostream>

//------------------
// ADDER MODULE
//------------------
SC_MODULE(adder) {
 sc_in <float> summandA, summandB;
 sc_out <float> sum;
 
 void add_process();
 
 SC_CTOR(adder) {
 SC_METHOD(add_process);
 sensitive << summandA << summandB;
 }
};

//------------------
// MULTIPLIER MODULE
//------------------
SC_MODULE(multiplier) {
 sc_in <float> multiplicandA, multiplicandB;
 sc_out <float> product;
 
 void multiply_process();
 
 SC_CTOR(multiplier) {
 SC_METHOD(multiply_process);
 sensitive << multiplicandA << multiplicandB;
 }
};

//------------------
// REGISTER MODULE
//------------------
SC_MODULE(reg) {
 sc_in <sc_logic> reset;
 sc_in <float> input;
 sc_out <float> output;
 sc_in_clk Clk;
 
 void reg_process();
 
 SC_CTOR(reg) {
 SC_CTHREAD(reg_process, Clk.pos());
 }
};