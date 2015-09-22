/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  This program is supposed to deploy a php framework for extremly fast
 *    				prototyping. Prototyping Websites.
 *
 *        Version:  1.0
 *        Created:  21/09/2015 17:57:12
 *       Revision:  none
 *       Compiler:  g++ std=c++11
 *
 *         Author:  Eshan Shafeeq
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include "Directory.h"
#include "Filestructure.h"


#define APP_NAME "TODO APP"
using namespace std;

void print_dirs(Directory d){
	cout << "ID : " << d.get_id();
	cout << " PID : " << d.get_p_id();
	cout << " NAME : " << d.get_name() << endl;
}

void generate_initial_structure(Filestructure fst){

	fst.add_directory(APP_NAME, "application");
	fst.add_directory(APP_NAME, "config");
	fst.add_directory(APP_NAME, "library");
	fst.add_directory(APP_NAME, "database");
	fst.add_directory(APP_NAME, "public");
	fst.add_directory(APP_NAME, "scripts");
	fst.add_directory(APP_NAME, "tmp");
	fst.add_directory("application", "controllers");
	fst.add_directory("application", "views");
	fst.add_directory("application", "models");
	fst.add_directory("tmp", "logs");
	fst.add_directory("tmp", "sessions");
	fst.add_directory("views", "items");

	fst.find_all_children();
	fst.print_dir(0, "");


}
int main(){
	vector<Directory> dirs;
	Filestructure fst = Filestructure(APP_NAME);

	generate_initial_structure(fst);

	return 0;
}

