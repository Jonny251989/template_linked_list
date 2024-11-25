#include <string>
#include <iostream>

struct PNode {
	virtual PNode *nextptr() = 0;
	virtual void print( std::ostream& ) = 0;
};

template<typename T, typename ...Args>
struct Node : public PNode {
	T data;
	Node<Args...> *next;

	PNode *nextptr() override {
		return next;
	}

	void print( std::ostream& stream ) override {
		stream << data;
	}
};

template<typename T>
struct Node<T> : public PNode {			/* Вот здесь необходима специализация шаблона */
	T data;	

	PNode *nextptr() override {
		return nullptr;
	}

	void print( std::ostream& stream ) override {
		stream << data;
	}
};

std::ostream &operator<<(std::ostream &stream, PNode &node) {
	node.print(stream);
	return stream;
}

template<typename T, typename ...Args>
struct List {
	Node<T, Args...> *first;

	List(T value, Args... values) {
		this->first = add(value, values...);
	}

	template<typename T1, typename ...Args1>
	Node<T1, Args1...> * add(T1 value, Args1... args) {
		Node<T1, Args1...> * node = new Node<T1, Args1...>;
		node->data = value;
		node->next = add(args...);
		return node;
	}

	template<typename T1>
	Node<T1>* add(T1 value) {
		Node<T1> * node = new Node<T1>;
		node->data = value;
		return node;
	}

	template<typename T1, typename ...Args1>
	friend std::ostream& operator<<(std::ostream&, List<T1, Args1...> &);
};

template<typename T, typename ...Args>
std::ostream& operator<<(std::ostream& stream, List<T, Args...> &lst) {
	PNode *node = lst.first;
	while (node != nullptr) {
		stream << "[" << *node << "] ";
		node = node->nextptr();
	}
	return stream;
}

int main() {
	List<int, double, std::string> lst{1, 2.5, "Hello"};
	std::cout << lst << std::endl;
	return 0;
}