#include "systemc.h"
#include "filter.h"
#include "stim.h"
#include "mon.h"

int sc_main(int argc, char* argv[])
{
  sc_signal<sc_logic> resetSig;
  sc_signal<float> xSig, ySig;
  sc_clock TestClk("TestClock", 10, SC_NS, 0.5, 1, SC_NS); 
  
  stim Stim1("Stimulus");
  Stim1.x(xSig);
  Stim1.reset(resetSig);
  Stim1.Clk(TestClk);
    
  filter DUT("filter");
  DUT.x(xSig);
  DUT.reset(resetSig);
  DUT.y(ySig);
  DUT.Clk(TestClk);

  mon Monitor1("Monitor");
  Monitor1.x(xSig);
  Monitor1.y(ySig);
  Monitor1.reset(resetSig);
  Monitor1.Clk(TestClk);
  
  sc_trace_file* Tf = sc_create_vcd_trace_file("filter_traces");
  Tf->set_time_unit(1, SC_NS);
  sc_trace(Tf, xSig  , "x" );
  sc_trace(Tf, ySig  , "y" );
  sc_trace(Tf, resetSig  , "reset" );


  sc_start(130, SC_NS);  // run for 130 ns
  sc_close_vcd_trace_file(Tf);
  
  return 0;
}