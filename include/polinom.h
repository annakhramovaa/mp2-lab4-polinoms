#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Node {
	double koef;
	int xyz;
	Node* next;
	Node(double _koef, int _xyz, Node* _next);
};

class Polinom_Lst {
private:
	Node* head;
	size_t size;
public:
	Polinom_Lst(string pol);
	~Polinom_Lst();
	size_t Get_size();
	void push_back(double koef, int xyz);
	void Monom(string pol);
	double Str_To_Double(string str);
	Node* at(int i);
	void bubblesort();
};