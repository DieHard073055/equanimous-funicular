/*
 * =====================================================================================
 *
 *       Filename:  Fileprocessor.h
 *
 *    Description:  Supposed to read the dws file and process it
 *
 *        Version:  1.0
 *        Created:  22/09/2015 13:50:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Eshan Shafeeq
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Fileprocessor{
	public:
		std::vector<std::string> readfile(std::string filename){
			std::ifstream rf (filename);
			std::vector<std::string> out;
			std::string line;
			if(rf.is_open()){
				while(getline(rf, line)){
					out.push_back(line);
				}
				rf.close();
			}
			return out;
		}
		std::string vector_to_string(std::vector<std::string> raw){
			std::string out="";
			for( std::vector<std::string>::iterator it = raw.begin();
				it != raw.end(); it++
			){
				out+= *it+"\n";
			}
			return out;
		}
		void write_to_file(std::string filename, std::string data){
			std::ofstream outfile (filename);
		  if (outfile.is_open()){
		    outfile << data;
		    outfile.close();
		  }
		}
		std::string generate_form(std::vector<std::string> raw){
			std::string form_data="";
			std::string title="";
			std::string php_file, php_out;

			for(int i=0;i<raw.size();i++){
				std::vector<std::string> in;
				switch(get_identifiers_int(raw[i])){
					case 0:
						title += get_php_function("get_title", "\""+clean_statement(get_identifier_str(raw[i]), raw[i])+"\"");
						title +="\n\n";
					break;
					case 2:
						in.push_back(raw[i++]);
						int type = 1;
						while(type == 1){
							in.push_back(raw[i++]);
							type = get_identifiers_int(raw[i]);
						}
						form_data += process_statement(in);
						i--;
					break;
				}
			}
			form_data = form_data.substr(0, form_data.length()-3);
			form_data = "array(" + form_data + ")";
			form_data = get_php_function("get_form_data", form_data) + "\n\n";


			//read php template file
			php_out = "<?php\nclass model{\n";
			php_file = vector_to_string(readfile("php_template"));
			php_out += title + form_data + "\n}" + php_file;
			return  php_out;
		}

	/*private functions*/
	private:
		std::string clean_statement(std::string identifier, std::string line){
			return line.substr(identifier.length(), line.length());
		}
		int get_identifiers_int(std::string line){
			std::string identifiers[] = {"*", "--", "-"};
			for(int i=0;i<sizeof(identifiers);i++){
				std::size_t pos = line.find(identifiers[i]);
				if(pos != std::string::npos){
					return i;
				}
			}
			return -1;
		}
		std::string get_identifier_str(std::string line){
			std::string identifiers[] = {"*", "--", "-"};
			for(int i=0;i<sizeof(identifiers);i++){
				std::size_t pos = line.find(identifiers[i]);
				if(pos != std::string::npos){
					return identifiers[i];
				}
			}
			return "";
		}

		std::string get_php_function(std::string function_name, std::string return_text){
			return "function " + function_name + "(){\nreturn " + return_text + ";\n}";
		}
		std::string get_php_array(std::vector<std::string> data){
			std::string out;
			out = "array(\n";
			for (std::vector<std::string>::iterator it = data.begin();
			 it != data.end(); it++) {
				 std::string temp = *it;
				 if(temp.find("array(") != std::string::npos){
					 out += temp;
				 }else if(temp.find("=") != std::string::npos){
					 out += "\"" + temp.substr(0, temp.find("=")) + "\" =>";

					 out += "\"" + temp.substr(temp.find("=")+1, temp.length()) + "\",\n";
				 }else{
					 out += "\"" + temp + "\",\n";
				 }
			 }
			 out = out.substr(0, out.length()-2);
			 return out+"\n)";
		}


		std::string process_statement(std::vector<std::string> raw){

			std::string out;

			std::vector<std::string> to_array;
			int i=raw.size()-1;
			int type = 1;

			while (type == 1){
				to_array.push_back(clean_statement(get_identifier_str(raw[i]), raw[i]));
				raw.erase(raw.begin() + i);
				type = get_identifiers_int(raw[--i]);
			}

			out = get_php_array(to_array);
			to_array.clear();

			for( std::vector<std::string>::iterator it = raw.begin();
				it != raw.end(); it++
			){
				to_array.push_back(clean_statement(get_identifier_str(*it), *it));
			}
			to_array.push_back(out);
			out = get_php_array(to_array);


			return out+"),\n\n";
		}

};

#endif
