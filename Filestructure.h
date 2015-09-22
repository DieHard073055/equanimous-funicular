/*
 * =====================================================================================
 *
 *       Filename:  Filestructure.h
 *
 *    Description:  This file will be used to keep the filestructure data
 *
 *        Version:  1.0
 *        Created:  21/09/2015 19:45:26
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Eshan Shafeeq
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include <iostream>
#include <sys/stat.h>
#include <vector>
#include <string>
#include "Directory.h"


class Filestructure{
	private:
		std::string project_name;
		std::vector<Directory> dir;
		int dir_count;
	public:
		Filestructure(std::string project_name){
			this->project_name = project_name;

			this->dir.push_back(Directory(ROOT, NO_PARENT, project_name));
			this->dir_count = ROOT+1;
		}

		void find_all_children(){
			for(int i=0;i<this->dir.size();i++){
				if(dir[i].get_p_id() != NO_PARENT){
					dir[dir[i].get_p_id()].add_child(dir[i].get_id());
				}
			}
		}
		int get_dir_by_name(std::string name){
			for(int i=0;i<this->dir.size();i++){
				if(dir[i].get_name() == name){
					return i;
				}
			}
			return NO_PARENT;
		}
		bool add_directory(std::string pname, std::string name){
			int id = get_dir_by_name(pname);
			if(id != NO_PARENT){
				this->dir.push_back(Directory(this->dir_count++, id, name));
				return true;
			}
			return false;
		}
		std::vector<Directory> get_file_structure(){
			//To hold the file structure data
			return this->dir;
		}

		bool has_children(int id){
			if(dir[id].get_children().size() > 0){
				return true;
			}
			return false;
		}
		void print_dir(int id, std::string before){
			std::cout << before << dir[id].get_name() << "/" << std::endl;
			if(has_children(id)){
				int children = (this->dir[id].get_children()).size();
				for(int i=0;i<children; i++){
					print_dir(dir[id].get_children()[i], before + "\t");
				}
			}
		}
};


#endif
