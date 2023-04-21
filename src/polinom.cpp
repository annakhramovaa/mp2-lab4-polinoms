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
	Sort();
}

Polinom_Lst::~Polinom_Lst() {
	for (Node* i = head->next; i != nullptr; i = head->next) {
		delete head;
		head = i;
	}
}

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

	}
}

double Polinom_Lst::Str_To_Double(string str) {
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

Polinom_Lst::Polinom_Lst() {
	this->head = nullptr;
	size = 0;
}



void Polinom_Lst::Sort() {
	Node* a, * b, * p, * h = nullptr;

	for (Node* i = head; i != nullptr; ) {
		a = i;
		i = i->next;
		b = h;
		for (p = nullptr; (b != nullptr) && (a->xyz < b->xyz); ) {
			p = b;
			b = b->next;
		}

		if (p == nullptr) {
			a->next = h;
			h = a;
		}
		else {
			a->next = b;
			p->next = a;
		}
	}
	if (h != nullptr)
		head = h;
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

Polinom_Lst Polinom_Lst::operator*(const double val) {
	Polinom_Lst b;
	for (Node* i = head; i != nullptr; i = i->next) {
		b.push_back(val * i->koef, i->xyz);

	}
	return b;
}


Polinom_Lst Polinom_Lst::operator+(const Polinom_Lst& b) {
	Node* first = this->head;
	Node* second = b.head;
	Polinom_Lst third;
	while (first != nullptr && second != nullptr) {
		if (first->xyz > second->xyz) {
			third.push_back(first->koef, first->xyz);
			first = first->next;
			cout << 1;
		}

		else if (first->xyz < second->xyz) {
			third.push_back(second->koef, second->xyz);
			second = second->next;
			cout << 2;
		}

		else if (first->xyz == second->xyz) {
			third.push_back(first->koef + second->koef, first->koef);
			first = first->next;
			second = second->next;
			cout << 3;
		}
		else {
			cout << "error";
		}
	}
	if ((first != nullptr) && (second != nullptr)) {
		while (first != nullptr) {
			third.push_back(first->koef, first->xyz);
			first = first->next;
			cout << 4;
		}
	}

	if ((first != nullptr) && (second != nullptr)) {
		while (second != nullptr) {
			third.push_back(second->koef, second->xyz);
			second = second->next;
			cout << 5;
		}
	}
	return third;
}

bool Polinom_Lst::operator==(Polinom_Lst& b) {
	Node* first = this->head;
	Node* second = b.head;
	if (this->size == b.size) {
		for (Node* i = head; i != nullptr; i = i->next) {
			if ((first->xyz == second->xyz) && (first->koef == second->koef))  return true;
		}
		return false;
	}
	else return false;
}

bool Polinom_Lst::operator!=(Polinom_Lst& b) {
	return !(*this == b);
}

Polinom_Lst Polinom_Lst::operator-(Polinom_Lst& b) {
	return *this + (b * (-1));
}

Polinom_Lst& Polinom_Lst::operator=(Polinom_Lst& b) {
	if (this == &b) return *this;
	this->~Polinom_Lst();
	this->size = b.size;
	for (Node* i = head; i != nullptr; i = i->next) {
		this->push_back(i->koef, i->xyz);
	}
	return *this;
}

Polinom_Lst::Polinom_Lst(Polinom_Lst& b) {
	this->size = b.size;
	if (b.head != nullptr) {
		Node* tmp = b.head;
		while (tmp != nullptr) {
			this->push_back(tmp->koef, tmp->xyz);
			tmp = tmp->next;
		}
	}
}

Polinom_Lst Polinom_Lst::operator*(Polinom_Lst& b) {
	Polinom_Lst third;
	for (Node* i = head; i != nullptr; i = i->next) {
		Polinom_Lst tmp;
		for (Node* j = b.head; j != nullptr; j = j->next) {

			tmp.push_back(i->koef * j->koef, i->xyz + j->xyz);
		}
		third = third + tmp;
	}
	return third;
}

