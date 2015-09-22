/*
 * =====================================================================================
 *
 *       Filename:  Directory.h
 *
 *    Description:  Header file for Directory.cpp 
 *    				This class is supposed to hold the data about the
 *    				Directories in the project
 *
 *        Version:  1.0
 *        Created:  21/09/2015 17:42:21
 *       Revision:  none
 *       Compiler:  g++ std=c++11
 *
 *         Author:  Eshan Shafeeq
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <vector>
#include <string>

#define NO_PARENT -1
#define ROOT 0

	class Directory{
		private:
			int id;
			int p_id;
			std::string name;
			std::vector<int> children;

		public:
			Directory(){};
			Directory(int id, int p_id, std::string name){
				set_id(id); set_p_id(p_id); set_name(name); 
			}
			void set_id(int id){this->id = id;}
			int get_id(){return this->id;}
			void set_p_id(int p_id){this->p_id = p_id;}
			int get_p_id(){return this->p_id;}
			void set_name(std::string name){this->name = name;}
			std::string get_name(){return this->name;}
			void add_child(int id){this->children.push_back(id);}
			std::vector<int> get_children(){return children;}
			void setChildren(std::vector<int> children){this->children=children;}
	};
#endif
