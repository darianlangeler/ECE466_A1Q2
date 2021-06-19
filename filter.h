#include "systemc.h"
#include "modules.h"


//------------------
// FILTER STRUCT DESC
//------------------
SC_MODULE(filter) {
 // External Ports 
 sc_in <float> x;
 sc_in <sc_logic> reset;
 sc_out <float> y;
 
 //Clock
 sc_in_clk Clk;
 
 //Internal Signals
 sc_signal <float> ab0_out, ab1_out, ab2_out, aa0_out; 
 sc_signal <float> mb0_out, mb1_out, mb2_out, mb3_out, ma0_out;
 sc_signal <float> rb1_out, rb2_out, rb3_out, ra0_out, ra1_out;

 //Instances
 adder add_b0, add_b1, add_b2, add_a0;
 multiplier mult_b0, mult_b1, mult_b2, mult_b3, mult_a0;
 reg reg_b1, reg_b2, reg_b3, reg_a0, reg_a1; 
 
 //Filter Coefficients
 sc_signal <float> cB0, cB1, cB2, cB3, cA0;
 
 SC_CTOR(filter):
 add_b0("add_b0"), add_b1("add_b1"), add_b2("add_b2"), 
 add_a0("add_a0"), mult_b0("mult_b0"), mult_b1("mult_b1"), 
 mult_b2("mult_b2"), mult_b3("mult_b3"), mult_a0("mult_a0"), 
 reg_b1("reg_b1"), reg_b2("reg_b2"), reg_b3("reg_b3"), 
 reg_a0("reg_a0"), reg_a1("reg_a1") {

 //Adders
 add_b0.summandA(mb0_out);				add_b0.summandB(ab1_out);		add_b0.sum(ab0_out);
 add_b1.summandA(mb1_out);				add_b1.summandB(ab2_out);		add_b1.sum(ab1_out);
 add_b2.summandA(mb2_out);				add_b2.summandB(mb3_out);		add_b2.sum(ab2_out);
 
 add_a0.summandA(ab0_out);				add_a0.summandB(ma0_out);		add_a0.sum(y);
 
 //Multipliers
 mult_b0.multiplicandA(x);				mult_b0.multiplicandB(cB0);	mult_b0.product(mb0_out);
 mult_b1.multiplicandA(rb1_out);		mult_b1.multiplicandB(cB1);	mult_b1.product(mb1_out);
 mult_b2.multiplicandA(rb2_out);		mult_b2.multiplicandB(cB2);	mult_b2.product(mb2_out);
 mult_b3.multiplicandA(rb3_out);		mult_b3.multiplicandB(cB3);	mult_b3.product(mb3_out);
 
 mult_a0.multiplicandA(ra1_out);		mult_a0.multiplicandB(cA0);	mult_a0.product(ma0_out);
 
 //Registers
 reg_b1.Clk(Clk);
 reg_b1.reset(reset);					reg_b1.input(x);					reg_b1.output(rb1_out);
 reg_b2.Clk(Clk); 
 reg_b2.reset(reset);					reg_b2.input(rb1_out);			reg_b2.output(rb2_out);
 reg_b3.Clk(Clk);
 reg_b3.reset(reset);					reg_b3.input(rb2_out);			reg_b3.output(rb3_out);
 
 reg_a0.Clk(Clk); 
 reg_a0.reset(reset);					reg_a0.input(y);					reg_a0.output(ra0_out);
 reg_a1.Clk(Clk); 
 reg_a1.reset(reset);					reg_a1.input(ra0_out);			reg_a1.output(ra1_out);
 
 //Write Filter Coefficients
 cB0.write(0.1667);
 cB1.write(-0.5);
 cB2.write(0.5);
 cB3.write(-0.1667);
 
 cA0.write(-0.3333);
 }
};