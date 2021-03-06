
#include "hl_fault.h"

extern "C" __declspec(dllexport) PLI_INT32 my_hlf()
{

	//This handle could be assign so that it points to head of a circuit
	handle module_handle;

	/*
	The ACC routine acc_initialize() shall initialize the environment for ACC routines and shall be called from
	the C language application program before the program invokes any other ACC routines.
	*/
	acc_initialize();
	io_printf("PLI_Start\n");

	//Using this command circuit_handle assigns to argument 1 of our function
	//for example assume we use $get_top(testbench.dut); then circuit_handle points to "dut"
	module_handle = acc_handle_tfarg(1); 

	//test
	PLI_BYTE8 * name;
	name = acc_fetch_fullname(module_handle);
	io_printf("%s\n",name);
	//
	
	
	//display names of all nets in current level of module
	handle net_handle;
	net_handle = null; 

	while( net_handle = acc_next_net( module_handle, net_handle ) ) 
	{
		io_printf("Net name is: %s\n", acc_fetch_fullname(net_handle) );
		io_printf("Net value is: %s\n", acc_fetch_value(net_handle,"%b", null));
	}

	//an example for changing value of a net
	static s_setval_value value_s;// = {accBinStrVal};
	value_s.format = accScalarVal;
	static s_setval_delay delay_s = {{accRealTime},accInertialDelay};
	delay_s.time.real= 0.0;
	delay_s.model = accForceFlag;

	net_handle = null; 
	

	while( net_handle = acc_next_net( module_handle, net_handle ) ) 
	{
		//print net name
		io_printf("Net name is: %s\n", acc_fetch_fullname(net_handle) );
		//print value of net
		io_printf("Net value is: %s\n", acc_fetch_value(net_handle,"%b", null));
		//move value of net to value_s
		acc_fetch_value (net_handle, "%%", &value_s);
		//print value of value_s
		io_printf("Value of Values = %d \n", value_s.value.scalar);
		//set value_s to another number
		if(value_s.value.scalar == acc0)
			value_s.value.scalar = acc1;
		else
			value_s.value.scalar = acc0;
		//set net value to value of value_s
		acc_set_value(net_handle, &value_s, &delay_s);
		//read value of net
		io_printf("New Net value is: %s\n", acc_fetch_value(net_handle,"%b", null));
	}
	
	//prints name of all child from top to down
	handle temp[100] = {null};
	temp[0] = module_handle;
	int i = 0;
	int j = 0;

	while(temp[i] != null)
	{
		io_printf("Current module is %s\n",acc_fetch_fullname(temp[i]));
		handle child;
		child = null;
		while(child = acc_next_child(temp[i], child))
		{
			io_printf("Module %s is a child of %s\n",acc_fetch_fullname(child),acc_fetch_fullname(temp[i]));
			j++;
			temp[j] = child;
		}
		
		i++;
	}
		
	/*
	Before  exiting  a  C  language  application  program  that  calls ACC  routines,  the ACC  routine  acc_close()
	should be called. This routine shall reset ACC routine configuration parameters back to their defaults, and it
	shall also free memory allocated by the ACC routines.
	*/
	acc_close();
	return 0;
}

 extern "C" __declspec(dllexport) s_tfcell veriusertfs[]=
{
	{usertask, 0, 0, 0, my_hlf, 0, "$my_hlf"},
	{0}
};