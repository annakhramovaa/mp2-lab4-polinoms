#pragma once
#include "../include/polinom.h"
using namespace std;


Node::Node(double _koef, int _xyz, Node* _next = nullptr) {
	koef = _koef;
	xyz = _xyz;
	next = _next;
}


Polinom_Lst::Polinom_Lst(string pol) {
	this->head = nullptr;
	size = 0;
	Monom(pol);
}

Polinom_Lst::~Polinom_Lst() {}

size_t Polinom_Lst::Get_size() {
	return size;
}

void Polinom_Lst::push_back(double koef, int xyz) {
	if (head == nullptr) {
		head = new Node(koef, xyz);
	}
	else {
		Node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = new Node(koef, xyz);
	}
	size++;
}

void Polinom_Lst::Monom(string pol) {


	int i = 0;

	while (i != pol.size()) {
		int X = 0, Y = 0, Z = 0;
		string koef;
		if (pol[i] == '-') {
			koef += "-";
			i++;
		}
		if (pol[i] == '+') {
			i++;
		}
		while ((pol[i] != 'x') && (pol[i] != 'y') && (pol[i] != 'z')) {
			koef += pol[i];
			i++;
		}

		if (pol[i] == 'x') {
			if (pol[i + 1] == '^') {
				X = int(pol[i + 2]) - 48;
				i = i + 3;
			}
			else {
				X = 1;
				i = i + 1;
			}

		}
		if (pol[i] == 'y') {
			if (pol[i + 1] == '^') {
				Y = int(pol[i + 2]) - 48;
				i = i + 3;
			}
			else {
				Y = 1;
				i = i + 1;
			}

		}
		if (pol[i] == 'z') {
			if (pol[i + 1] == '^') {
				Z = int(pol[i + 2]) - 48;
				i = i + 3;
			}
			else {
				Z = 1;
				i = i + 1;
			}

		}
		int XYZ = X * 100 + Y * 10 + Z;
		push_back(Str_To_Double(koef), XYZ);
		cout << XYZ << "\n";

	}
}

double Polinom_Lst::Str_To_Double(string str) {
	cout << "str" << str << "\n";
	int i = 0;
	int pow = 1;
	double value = 0;
	int sign = 1;

	if (str[0] == '-') {
		sign = -1;
		i++;
	}
	for (; i < str.size() && str[i] != '.'; i++) {
		if (int(str[i]) >= 48 && int(str[i]) <= 57) {
			value = value * pow + (int(str[i]) - 48);
			pow = pow * 10;
		}
	}
	i++;
	pow = 10;

	for (; i < str.size(); i++) {
		if ((str[i]) >= '0' && (str[i]) <= '9') {
			value = value + (double(str[i]) - 48) / pow;
			pow = pow * 10;
		}
	}
	cout <<"val" << value << "\n";
	return sign * value;

}

Node* Polinom_Lst::at(int i) {
	Node* current = head;
	int count = 0;

	while (current != nullptr) {
		if (count == current->xyz)
			return current;
		current = current->next;
		count++;
	}
}

void Polinom_Lst::bubblesort() {
	for (Node* i = head; i != nullptr; i = i->next) {
		for (Node* j = i; j != nullptr; j = j->next) {
			if (j->xyz > i->xyz) {
				Node* tmp = j;
				j = i;
				i = tmp;
			}
		}
	}
}

void Polinom_Lst::show() {
	for (Node* i = head; i!=nullptr; i= i->next) {	
		if (i->koef > 0) cout << "+";
		cout << i->koef;
		cout << "x^";
		cout << i->xyz / 100;
		cout << "y^";
		cout << i->xyz / 10 %10;
		cout << "z^";
		cout << i->xyz % 10;

	}
}