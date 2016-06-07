#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	char tmp[10] = {0};
	sprintf(tmp, "%d", 0);
	std::string tmpstr = tmp;	
	std::string default_console = "\033["+tmpstr+"m";
	for (int i = 30; i <= 37; i++)
	{
		sprintf(tmp, "%d", i);
		std::string tmpstr = tmp;	
		std::string color = "\033[0;"+tmpstr+"m";
		std::cout<<color<<"test "<<i<<std::endl;

		sprintf(tmp, "%d", i);
		tmpstr = tmp;	
		color = "\033[1"+tmpstr+"m";

		std::cout<<color<<"test "<<i<<" bold"<<std::endl;
		std::cout<<default_console<<std::endl;

	}

	std::cout << "Done" << std::endl;

	return 0;
}
