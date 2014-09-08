#include "Builder.h" 
#include "Product.h" 
#include "Director.h" 
#include <iostream> 
using namespace std; 


int main(int argc,char* argv[]) 
{ 
	Director* d = new Director(new ConcreteBuilder()); 
	d->Construct(); 
	
	 /*ConcreteBuilder p ;
	 p.GetProduct();*/

	system("pause");
	return 0; 
} 