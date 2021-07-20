#include "systemc.h"
#include <iomanip>
using namespace std;

SC_MODULE(mon)
{
  sc_in_clk Clk;
  sc_in<sc_logic> reset;
  sc_in<float> x,y;

  void monitor()
  {
	cout << setw(10) << "Time";
	cout << setw(2) << "reset";
	cout << setw(2) << "x";
	cout << setw(2) << "y" << endl;
	
	while (true) {
		cout << setw(10) << sc_time_stamp();
		cout << setw(2) << reset.read();
		cout << setw(2) << x.read();
		cout << setw(2) << y.read() << endl;
		wait();		
	}
  }
  SC_CTOR(mon)
  {
    SC_CTHREAD(monitor, Clk.pos());
  }
};