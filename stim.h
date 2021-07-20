#include "systemc.h"
#include <iomanip>

SC_MODULE(stim)
{
  sc_out<sc_logic> reset;
  sc_out<float> x;
  sc_in_clk Clk;

  void stimgen()
  {
    reset.write(SC_LOGIC_1);
    wait();
    reset.write(SC_LOGIC_0);
    x.write(1);
    wait();
    x.write(0);
    //sc_stop();
  }
  SC_CTOR(stim)
  {
    SC_CTHREAD(stimgen, Clk.pos());
  }
};