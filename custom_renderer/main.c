/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  04/02/2013 08:42:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  laminic (), laminic@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <glib.h>
#include "boy.h"
#include "man.h"

int main(int argc, const char *argv[])
{
	Boy *tom, *peter;
	Man *green, *brown;

	g_type_init();

	tom = boy_new_with_name("Tom");
	tom->cry();
	boy_info(tom);

	peter = boy_new_with_name_and_age("Peter", 10);
	peter->cry();
	boy_info(peter);

	green = man_new();
	boy_set_name(BOY(green), "Green");
	boy_set_age(BOY(green), 28);
	man_set_job(green, "Doctor");
	green->bye();
	man_info(green);

	brown = man_new_with_name_age_and_job("Brown", 30, "Teacher");
	brown->bye();
	man_info(brown);
	return 0;
}
