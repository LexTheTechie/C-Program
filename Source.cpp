#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
/*Alexis Alexander
* CS 210-T5410
* 06/19/2021
*/

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	string spefItem;
	ifstream freqDat;
	string grocItem;
	int numPurchases;
	string Color1= "\033[1m\033[31m";
	string Color = "\033[0m";
	int clicked = 0;
	do {
		cout << endl << "1: Display list of items purchased" << endl << "2: Display number of purchases for a specific item" << endl << "3: Display histogram for items purchased" << endl << "4: Exit" << endl << "Please choose an option: 1,2,3 or 4" << endl;
		cin >> clicked;
		switch (clicked) {
		case 1:
			system("CLS");
			CallProcedure("ReadLines");
			break;
		case 2:
			system("CLS");
			cout << endl << "Please enter the grocery item" << endl;
			cin >> spefItem;
			cout << "Number of purchases: " << callIntFunc("SpecificItem", spefItem) << endl;
			break;
		case 3:
			system("CLS");                                         
			CallProcedure("CreateData"); 
			freqDat.open("frequency.dat");       

			freqDat >> grocItem;             //obtain first grocItem and corresponding num of purchases from dat file             
			freqDat >> numPurchases;                       
			while (!freqDat.fail()) {
				cout << Color;
				cout << "||" << setw(11) << left << grocItem << "||"<< setw(6);

				cout << Color1;
				//Print numPurchases in boxes
				for (int i = 0; i < numPurchases; i++) {
					cout << right << "[]";
				}
			
				cout << endl;
				freqDat >> grocItem;  //obtain next grocItem and purchase from file
				freqDat >> numPurchases;
			}

			freqDat.close(); // close freq.dat file
			cout << Color << endl; 
			break;

		case 4:
			cout << endl << "You are now exiting the program!" << endl;
			exit(0);
			break;
		default:
			cout << endl << "Please enter a valid selection . . ." << endl; //Prompt for user to enter valid selection if number that is not 1-3 is used. 
			break;
		}
	} while (clicked != 4);



}