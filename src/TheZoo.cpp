#include <iostream>
#include <fstream>
#include <iomanip>
#include <jni.h>
#include <vector>
#include "Animal.h"
#include "Mammal.h"
#include "Oviparous.h"
using namespace std;
vector<Animal*> Animals;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
	JavaVM *jvm;                    // Pointer to the JVM (Java Virtual Machine)
	JNIEnv *env;                      // Pointer to native interface
									  //================== prepare loading of Java VM ============================
	JavaVMInitArgs vm_args;                        // Initialization arguments
	JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
	options[0].optionString = (char*) "-Djava.class.path="; // where to find java .class
	vm_args.version = JNI_VERSION_1_6;             // minimum Java version
	vm_args.nOptions = 1;                          // number of options
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false; // invalid options make the JVM init fail
										//=============== load and initialize Java VM and JNI interface =============
	jint rc = JNI_CreateJavaVM(&jvm, (void**) &env, &vm_args);  // YES !!
	delete options;    // we then no longer need the initialization options.
	if (rc != JNI_OK) {
		// TO DO: error processing...
		cin.get();
		exit (EXIT_FAILURE);
	}
	//=============== Display JVM version =======================================
	cout << "JVM load succeeded: Version ";
	jint ver = env->GetVersion();
	cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

	jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
	if (cls2 == nullptr) {
		cerr << "ERROR: class not found !";
	} else {                                  // if class found, continue
		cout << "Class MyTest found" << endl;
		jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V"); // find method
		if (mid == nullptr)
			cerr << "ERROR: method void createZooFile() not found !" << endl;
		else {
			env->CallStaticVoidMethod(cls2, mid);                 // call method
			cout << endl;
		}
	}

	jvm->DestroyJavaVM();
	cin.get();
}

void AddAnimal()    //code to add an animal to your vector (or array)
{
	string theTrackNumber;
	string theName;
	string theType;
	string theSubtype;
	int theEggs;
	int theNurse;
	string reply;

	cout << "Enter the Track Number to add:" << endl;
	getline(cin, theTrackNumber);
	cout << "Enter the name: " << endl;
	getline(cin, theName);
	cout << "Enter " << theName << "'s type: " << endl;
	getline(cin, theType);


	if (theType == "oviparous") {
		cout << "Enter " << theName << "'s subtype: " << endl;
		getline(cin, theSubtype);
		cout << "Enter number of eggs laid:" << endl;
		cin >> theEggs;
		cout << "Would you like to save or cancel?" << endl;
		cin >> reply;
		if (reply == "save") {
			Oviparous*tempVar = new Oviparous;
			tempVar->setTrackNum(theTrackNumber);
			tempVar->setName(theName);
			tempVar->setType(theType);
			tempVar->setSubtype(theSubtype);
			tempVar->setEggs(theEggs);
			tempVar->setNurse(0);
			Animals.push_back(tempVar);
			cout << theName << "'s information has been added." << endl;
		} else if (reply == "cancel") {
			return;
		}
	}

	else if (theType == "mammal") {
		cout << "Enter " << theName << "'s subtype: " << endl;
		getline(cin, theSubtype);
		cout << "Enter 1 for nursing or 0 for not nursing:" << endl;
		cin >> theNurse;
		cout << "Would you like to save or cancel?" << endl;
		cin >> reply;
		if (reply == "save") {
			Mammal*tempVar = new Mammal;
			tempVar->setTrackNum(theTrackNumber);
			tempVar->setName(theName);
			tempVar->setType(theType);
			tempVar->setSubtype(theSubtype);
			tempVar->setEggs(0);
			tempVar->setNurse(theNurse);
			Animals.push_back(tempVar);
			cout << theName << "'s information has been added." << endl;
		} else if (reply == "cancel") {
			return;
		}
	}

}

void RemoveAnimal() { //to remove an animal from your vector

	string theTrackNumber;
	string answer;

	cout << "List the Track Number to Remove Animal" << endl;
	cin >> theTrackNumber;
	cout << "Are you sure you want to remove animal number " << theTrackNumber
			<< "? Enter Yes or No." << endl;
	cin >> answer;
	if (answer == "No") {
		return;
	} else if (answer == "Yes") {
		bool deletedAnimal = false;
		for (size_t i = 0; i < Animals.size(); ++i) {
			if (Animals[i]->getTrackNum() == theTrackNumber) {
				delete Animals[i];
				Animals.erase(Animals.begin() + i);
				deletedAnimal = true;
				break;
			}
			if (deletedAnimal == false) {
				cout << "Error. Animal Number not found." << endl;
			}
		}
	} else {
		cout << "Invalid Response.  Returning to Main Menu.";
		return;
	}

}

void LoadDataFromFile() { //load data from input file (generated using JNI) into vector/array.
	ifstream inFS;
	string theTrackNumber;
	string theName;
	string theType;
	string theSubtype;
	int theEggs;
	int theNurse;

	inFS.open("zoodata.txt");
	if (!inFS.is_open()) {
		cout << "Could not open file zoodata.txt." << endl;
		return; // 1 indicates error
	}

	for(size_t i =0; i < Animals.size();++i){
		delete Animals[i];
	}
	Animals.clear();

	while (!inFS.eof()) {
		inFS >> setw(6) >> theTrackNumber;
		inFS >> setw(15) >> theName;
		inFS >> setw(15) >> theType;
		inFS >> theSubtype;
		inFS >> theEggs;
		inFS >> theNurse;

		if (theType == "oviparous") {
			Oviparous*tempVar = new Oviparous;
			tempVar->setTrackNum(theTrackNumber);
			tempVar->setName(theName);
			tempVar->setType(theType);
			tempVar->setSubtype(theSubtype);
			tempVar->setEggs(theEggs);
			tempVar->setNurse(theNurse);
			Animals.push_back(tempVar);
		} else if (theType == "mammal") {
			Mammal*tempVar = new Mammal;
			tempVar->setTrackNum(theTrackNumber);
			tempVar->setName(theName);
			tempVar->setType(theType);
			tempVar->setSubtype(theSubtype);
			tempVar->setEggs(theEggs);
			tempVar->setNurse(theNurse);
			Animals.push_back(tempVar);
		}
		else{
			cout << "unrecognized type" << theType << endl;
		}
	}

		cout << "Closing file zoodata.txt." << endl;
		inFS.close(); // Done with file, so close it

}

void SaveDataToFile() { //store vector to file.
	ofstream outFS;

	outFS.open("zoodata.txt");

	if (!outFS.is_open()) {
		cout << "Could not open file myoutfile.txt." << endl;
		return;
	}

	for (size_t i = 0; i < Animals.size(); ++i) {
		outFS << setw(6) << Animals[i]->getTrackNum();
		outFS << setw(15) << Animals[i]->getName();
		outFS << setw(15) << Animals[i]->getType();
		if (Animals[i]->getType() == "mammal") {
			Mammal*m = dynamic_cast<Mammal*>(Animals[i]);
			outFS << setw(15) << m->getSubtype() << " ";
			outFS << m->getEggs() << " ";
			outFS << m->getNurse() << endl;
		} else {
			Oviparous*o = dynamic_cast<Oviparous*>(Animals[i]);
			outFS << setw(15) << o->getSubtype() << " ";
			outFS << o->getEggs() << " ";
			outFS << o->getNurse() << endl;
		}
	}

		outFS.close();

		return;
}

void DisplayAnimalData(){
	for (size_t i = 0; i < Animals.size(); ++i) {
			cout << setw(6) << Animals[i]->getTrackNum();
			cout << setw(15) << Animals[i]->getName();
			cout << setw(15) << Animals[i]->getType();
			if (Animals[i]->getType() == "mammal") {
				Mammal*m = dynamic_cast<Mammal*>(Animals[i]);
				cout << setw(15) << m->getSubtype();
				cout << m->getEggs() << " ";
				cout << m->getNurse() << endl;
			} else {
				Oviparous*o = dynamic_cast<Oviparous*>(Animals[i]);
				cout << setw(15) << o->getSubtype();
				cout << o->getEggs() << " ";
				cout << o->getNurse() << endl;
			}
	}
}

void DisplayMenu() {  // display menu to user to select from

	int menuSelect;

	cout << "*******************************************" << endl;
	cout << " Please select from the following options" << endl;
	cout << " 1. Load Animal Data" << endl;
	cout << " 2. Generate Data" << endl;
	cout << " 3. Display Animal Data" << endl;
	cout << " 4. Add Record" << endl;
	cout << " 5. Delete Record" << endl;
	cout << " 6. Save Animal Data" << endl;
	cout << " Select 0 to quit." << endl;
	cout << "********************************************" << endl;

	cin >> menuSelect;
	cin.get();

	while (menuSelect != 0) {
		if (menuSelect == 1) {
			LoadDataFromFile();
		} else if (menuSelect == 2) {
			GenerateData();
		} else if (menuSelect == 3) {
			DisplayAnimalData();
		} else if (menuSelect == 4) {
			AddAnimal();
		} else if (menuSelect == 5) {
			RemoveAnimal();
		} else if (menuSelect == 6) {
			SaveDataToFile();
		} else if (menuSelect != 0) {
			cout << "Error.  Please try again.";
		}

		if (menuSelect != 0) {
			cin >> menuSelect;
		}
	}
}

int main() {
	DisplayMenu();
	return 1;
}
