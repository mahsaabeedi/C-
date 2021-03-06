
#include "hl_fault.h"
#include "stdlib.h"
#include "stdio.h"
#include <string>
#include <iostream>
#include <ctime>

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
	io_printf("%s\n", name);
	//


	//display names of all nets in current level of module
	handle net_handle;
	net_handle = null;

	/*while (net_handle = acc_next_net(module_handle, net_handle))
	{
	io_printf("Net name is: %s\n", acc_fetch_fullname(net_handle));
	io_printf("Net value is: %s\n", acc_fetch_value(net_handle, "%b", null));
	}*/

	//an example for changing value of a net
	static s_setval_value value_s;// = {accBinStrVal};
	value_s.format = accScalarVal;
	static s_setval_delay delay_s = { { accRealTime },accInertialDelay };
	delay_s.time.real = 0.0;
	delay_s.model = accForceFlag;

	net_handle = null;

	handle input_net[1000] = { null };
	int index = 0;
	handle bit_handle;
	bit_handle = null;


	while (net_handle = acc_next_net(module_handle, net_handle)) {
		bit_handle = null;
		while (bit_handle = acc_next_bit(net_handle, bit_handle)) {

			input_net[index] = bit_handle;

			//io_printf("Net name is: %s\n", acc_fetch_fullname(net_handle));
			//io_printf("Net in array: %d\n", index);
			index++;
		}
		//net_handle = null;

	}

	//answer 1 inject fault 
	/*if (acc_fetch_fullname(bit_handle) == "SayehTest.U1.Databus_in[1]") {
	io_printf("Net name is: %s\n", acc_fetch_fullname(bit_handle));
	io_printf("Net value is: %s\n", acc_fetch_value(bit_handle, "%b", null));
	acc_fetch_value(bit_handle, "%%", &value_s);
	io_printf("Value of Values = %d \n", value_s.value.scalar);
	if (value_s.value.scalar == acc1)
	value_s.value.scalar = acc0;
	else
	value_s.value.scalar = acc1;

	acc_set_value(bit_handle, &value_s, &delay_s);

	io_printf("New Net value is: %s\n", acc_fetch_value(bit_handle, "%b", null));
	}*/

	/*else if (acc_fetch_fullname(bit_handle) == "SayehTest.U1.Instruction[3]") {
	io_printf("Net name is: %s\n", acc_fetch_fullname(bit_handle));
	io_printf("Net value is: %s\n", acc_fetch_value(bit_handle, "%b", null));
	acc_fetch_value(bit_handle, "%%", &value_s);
	io_printf("Value of Values = %d \n", value_s.value.scalar);
	if (value_s.value.scalar == acc1)
	value_s.value.scalar = acc0;
	else
	value_s.value.scalar = acc1;

	acc_set_value(net_handle, &value_s, &delay_s);

	io_printf("New Net value is: %s\n", acc_fetch_value(bit_handle, "%b", null));
	}

	else if (acc_fetch_fullname(bit_handle) == "SayehTest.U1.AorB") {
	io_printf("Net name is: %s\n", acc_fetch_fullname(bit_handle));
	io_printf("Net value is: %s\n", acc_fetch_value(bit_handle, "%b", null));
	acc_fetch_value(bit_handle, "%%", &value_s);
	io_printf("Value of Values = %d \n", value_s.value.scalar);
	if (value_s.value.scalar == acc1)
	value_s.value.scalar = acc0;
	else
	value_s.value.scalar = acc1;

	acc_set_value(bit_handle, &value_s, &delay_s);

	io_printf("New Net value is: %s\n", acc_fetch_value(bit_handle, "%b", null));
	}

	*/

	//answer 1 random fault inject

	//for (int i = 0; i < 1; i++) {
	//	int random_1 = rand() % index;
	//		io_printf("Net name is: %s\n", acc_fetch_fullname(input_net[random_1]));
	//		io_printf("Net value is: %s\n", acc_fetch_value(input_net[random_1], "%b", null));
	//		acc_fetch_value(input_net[random_1], "%%", &value_s);
	//		io_printf("Value of Values = %d \n", value_s.value.scalar);
	//		if (value_s.value.scalar == acc1)
	//			value_s.value.scalar = acc0;
	//		else
	//			value_s.value.scalar = acc1;

	//		acc_set_value(input_net[random_1], &value_s, &delay_s);

	//		io_printf("New Net value is: %s\n", acc_fetch_value(input_net[random_1], "%b", null));

	//}

	//answer 3 

	/*io_printf("********** part4\n");
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		int a = rand() % index;
		io_printf("********** %d\n", a);
		io_printf("Net name is: %s\n", acc_fetch_fullname(input_net[a]));
		io_printf("Net value is: %s\n", acc_fetch_value(input_net[a], "%b", null));
		acc_fetch_location( , "%%", &value_s);
		acc_fetch_value(input_net[a], "%%", &value_s);
		io_printf("Value of Values = %d \n", value_s.value.scalar);
		acc_fetch_fullname(input_net[a]);
		if (value_s.value.scalar == acc0)
			value_s.value.scalar = acc1;
		else
			value_s.value.scalar = acc1;
		acc_set_value(input_net[a], &value_s, &delay_s);
		io_printf("New Net value is: %s\n", acc_fetch_value(input_net[a], "%b", null));

	}
*/





//answer4
handle temp[100] = { null };
temp[0] = module_handle;
handle bit_input4[1000] = { null };
int index4 = 0;
int i4 = 0;
int j4 = 0;
srand(time(NULL));
int random_1 = rand() % (542 - 245 + 1) + 245;
int random_2 = rand() % (542 - 245 + 1) + 245;
int random_3 = rand() % (542 - 245 + 1) + 245;
int random_4 = rand() % (542 - 245 + 1) + 245;
int random_5 = rand() % (542 - 245 + 1) + 245;

while (temp[i4] != null)
{
	//io_printf("Current module is %s\n", acc_fetch_fullname(temp4[i4]));
	handle child;
	child = null;
	while (child = acc_next_child(temp[i4], child))
	{
		j4++;
		temp[j4] = child;
		net_handle = null;
		while (net_handle = acc_next_net(temp[j4], net_handle)) {
			bit_handle = null;
			while (bit_handle = acc_next_bit(net_handle, bit_handle)) {
				index4++;
				if (index4 == random_1 || index4 == random_2 || index4 == random_3 || index4 == random_4 || index4 == random_5) {
					io_printf("Net name is: %s\n", acc_fetch_fullname(bit_handle));
					io_printf("Net value is: %s\n", acc_fetch_value(bit_handle, "%b", null));
					acc_fetch_value(bit_handle, "%%", &value_s);
					io_printf("Value of Values = %d \n", value_s.value.scalar);
					acc_fetch_fullname(bit_handle);
					if (value_s.value.scalar == acc0)
						value_s.value.scalar = acc1;
					else
						value_s.value.scalar = acc1;
					acc_set_value(bit_handle, &value_s, &delay_s);
					io_printf("New Net value is: %s\n", acc_fetch_value(bit_handle, "%b", null));	
				}

			}

		}
	}
	i4++;
}




//answer 5 
//prints name of all child from top to down

	//handle temp[100] = { null };
	//temp[0] = module_handle;
	//int i = 0;
	//int j = 0;

	//handle bit_input5[1000] = { null };
	//int index_bit = 0;
	//while (temp[i] != null)
	//{
	//	io_printf("Current module is %s\n", acc_fetch_fullname(temp[i]));
	//	handle child;
	//	child = null;
	//	while (child = acc_next_child(temp[i], child))
	//	{
	//		io_printf("temp i =   %s\n", acc_fetch_fullname(temp[i]));
	//		io_printf("Module %s is a child of %s\n", acc_fetch_fullname(child), acc_fetch_fullname(temp[i]));
	//		j++;
	//		temp[j] = child;
	//		io_printf(" j = %d \n", j);
	//		io_printf("temp j =  %s \n", acc_fetch_fullname(temp[j]));


	//		 //j=2: ctrl; j=4 AL ; j=5 RF; j=6 IR ; j=7 SR; j=8 WP;
	//		if (j == 10) {
	//			bit_input5[1000] = { null };
	//			index_bit = 0;
	//			net_handle = null;
	//			while (net_handle = acc_next_net(temp[j], net_handle)) {
	//				io_printf("Net name is: %s\n", acc_fetch_fullname(net_handle));
	//				bit_handle = null;
	//				while (bit_handle = acc_next_bit(net_handle, bit_handle)) {
	//					bit_input5[index_bit] = bit_handle;
	//					index_bit++;
	//					io_printf("bit name is: %s\n", acc_fetch_fullname(bit_handle));
	//				}
	//			}
	//			srand(time(NULL));
	//			for (int i = 0; i < 1; i++) {
	//				int a = rand() % index_bit;
	//				io_printf("Net name is: %s\n", acc_fetch_fullname(bit_input5[a]));
	//				io_printf("Net value is: %s\n", acc_fetch_value(bit_input5[a], "%b", null));
	//				acc_fetch_value(bit_input5[a], "%%", &value_s);
	//				io_printf("Value of Values = %d \n", value_s.value.scalar);
	//				acc_fetch_fullname(bit_input5[a]);
	//				if (value_s.value.scalar == acc0)
	//					value_s.value.scalar = acc1;
	//				else
	//					value_s.value.scalar = acc1;
	//				acc_set_value(bit_input5[a], &value_s, &delay_s);
	//				io_printf("New Net value is: %s\n", acc_fetch_value(bit_input5[a], "%b", null));
	//			}


	//		}
	//	}

	//	i++;
	//}


	//Before  exiting  a  C  language  application  program  that  calls ACC  routines,  the ACC  routine  acc_close()
	//should be called. This routine shall reset ACC routine configuration parameters back to their defaults, and it
	//shall also free memory allocated by the ACC routines.

	acc_close();
	return 0;
}

extern "C" __declspec(dllexport) s_tfcell veriusertfs[] =
{
	{ usertask, 0, 0, 0, my_hlf, 0, "$my_hlf" },
	{ 0 }
};
