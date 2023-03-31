#include "../include/polinom.h"
#include <iostream>

int main() 
{
	Polinom_Lst a("3xy^2-52y^3+2.2xyz");
	Polinom_Lst b("4xyz+2y+9x");
	a.show();
	cout << "\n";
	b.show();
	///*cout << "\n";
	//(a * 5).show();*/
	//cout << "\n";
	//(a + b).show();
	//a = b;
	//a.show();
}