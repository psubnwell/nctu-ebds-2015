#include <iostream>
#include <fstream>
using namespace std;

int main(){
	int cout;
	char filename[] = "counter.txt";

	fstream file;
	file.open(filename, ios::in);

	if(!file.is_open())
		cout << "file not open correctly" <<endl;
	file >> count;
	count++;
	file.close();

	file.open(filename, ios::trumc);
	file.close();

	file.open(filename, ios::out);
	file << count;
	file.close();

	cout << "ContentType:text/html;\n\n";
	cout << "You are the "<< count <<" 'st one visiting this website." <<endl <<endl;
}