/*
 * =====================================================================================
 *
 *       Filename:  Formgenerator.h
 *
 *    Description:  This class is used to generate form from simple text like script.
 *
 *        Version:  1.0
 *        Created:  21/09/2015 22:55:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Eshan Shafeeq
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef FORMGENERATOR_H
#define FORMGENERATOR_H

class Formgenerator{
	private:
		std::string scriptfile_name;
		std::string form_name;

	public:
		Formgenerator(std::string scname, std::string fname){
			this->scriptfile_name =scname;
			this->form_name = fname;
		}


}

#endif
