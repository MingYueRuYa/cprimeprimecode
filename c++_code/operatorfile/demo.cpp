#include <iostream>

int main()
{

  std::string str = "ledconfigure can get cards information, upgrade sender, upgrade receiver, set brightness, send config\n\n"
"warning: startup ledconfigure need root account or add \'sudo\' , ledserver and ledcilent must in same  folder, otherwise program may not run correctly.\n\n"
"Usuage:\n\n"
	"\t1. get the usage of ledconfigure program.\n\n"
	   "\t  syntax: ledconfigure -help or ledconfigure\n\n"
	   "\t  example:\n"
	   		"\t\t#sudo ledconfigure -help\n"
	"\t2. get cards information.\n"
	   "\t  syntax: ledconfigure -detectcards\n"
	   "\t  example:\n\n"
			"\t\t#sudo ledconfigure -detectcards\n\n"
			"\t\tif no cards detected, it shows: \"No cards detected !\", otherwise :\n"
			"\t\tdevice 1 info\n"
			"\t\tconnect type: usb\n"
			"\t\tconnect address:  276\n"
			"\t\tGUID index:  29\n";
	std::cout << str << std::endl;
  	return 0;

	}

