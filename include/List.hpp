#pragma once
#include <iostream>
#include <functional>
#include <memory>



template <typename T>
class List {
private:
	struct Node {
		T data;
		std::unique_ptr<Node> next;
		Node* prev = nullptr;
		bool isHiddenNode = false;

		Node(const T& data = T{}) : data(data) {}
	};

	std::unique_ptr<Node> head;
	Node* tail = nullptr;

public:
	class const_iterator {
	protected:
		Node* current;
		const_iterator(Node* p) : current(p) {}
		friend class List<T>;

	public:
		const_iterator() : current(nullptr) {}

		const T& operator*() const { return current->data; }

		const_iterator& operator++() {
			current = current->next.get();
			return *this;
		}

		const_iterator  operator++(int) {
			const_iterator old = *this;
			++(*this);
			return old;
		}

		bool operator==(const const_iterator& rhs)const {
			return current == rhs.current;
		}
		bool operator!=(const const_iterator& rhs) cons {
			return !(*this == rhs);
		}
		Node* getNode()const { return current; }
	};

	class iterator : public const_iterator {
	protected:
		iterator(Node* p) : const_iterator(p) {}
		friend class List<T>;

	public:
		iterator() {}

		T& operator*() { return this->current->data; }
		const T& operator*() const { return const_iterator::operator*(); }

		iterator& operator++() {
			this->current = this->current->next.get();
			return *this;
		}

		iterator operator++ (int) {
			iterator old = *this;
			++(*this);
			return old;
		}
	};

List() {
	head = std::make_unique<Node>();
	head->isHiddenNode = true;

	Node* tailNode = new Node();
	tailNode->isHiddenNode = true;
	tail = tailNode;

	head->next = std::unique_ptr<Node>(tail);
	tail->prev = head.get();
}

~List() = default;

List(const List& other) : List() {
	for (Node* curr = other.head->next.get(); curr != other.tail; curr = curr->next.get()) {
		push_back(curr->data);
	}
}

List& operator=(const List& other) {
	if (this != &other) {
		clear();
		for (Node* curr = other.head->next.get(); curr != other.tail;curr = curr->next.get()) {curr = push_back(curr->data);
		}
	}
	return *this;
}
List(List&& other)noexcept
	:head(std::move(other.head)), tail(other.tail) {
	other.tail = nullptr;
}
List& operator=(List&& other)noexcept {
	if (this != &other) {
		clear();
		head = std::move(other.head);
		tail = other.tail;
		other.tail = nullptr;
	}
	return *this;
}
bool empty() const {
	return head->next.get() == tail;
}

	// iterator related methods, Note the use of the initializer
	// syntax to return back an iterator initialized from the
	// matching pointers in the list.
iterator begin() { return iterator{head->next.get()}; }
iterator end() { return iterator{tail}; }
const_iterator cbegin() const {return const_iterator{head->next.get()};}
const_iterator cend() const {return const_iterator{tail};}

  // The existence of iterators means we can add methods to
  // manipulate the contents of a list.
  
void clear() {
	head->next.reset();
	Node* tailNode = new Node();
	tailNode->isHiddenNode = true;
	tail = tailNode;
	head->next = std::unique_ptr<Node>(tail);
	tail->prev = head.get();

	// And the methods for the rest 

	void push_back(const T& data) {
		Node* prevNode = tail->prev;
		auto newNode = std::make_unique<Node>(data);
		newNode->prev = prevNode;

		Node* newNodeRaw = newNode.get();
		prevNode->next = std::move(newNode);
		tail->prev = newNodeRaw;
		newNodeRaw->next = std::unique_ptr<Node>(tail);
	}
	void push_front(const T & data) {
		auto newNode = std::make_unique<Node>(data);
		Node* first = head->next.get();

		newNode->prev = head.get();
		newNode->next = std::move(head->next);
		first->prev = newNode.get();
		head->next = std::move(newNode);
	}
	void pop_front() {
		if (!empty()) {
			auto removed = std::move(head->next);
			head->next= std::move(removed->next);
			if (head->next) head->next->prev = head.get();
		}
	}
	void pop_back() {
		if (!empty()) {
			Node* beforeTail = tail->prev;
			Node* newBeforeTail = beforeTail->prev;
			newBeforeTail->next = std::unique_ptr<Node>(tail);
			tail->prev = newBeforeTail;
		}
	}

	T& front() {
		return head->next->data;
	}
	T& back() {
		return tail->prev->data;
	}

	iterator insert(iterator itr, const T & value) {
		Node* current = itr.getNode();
		Node* prevNode = current->prev;

		auto newNode = std::make_unique<Node>(value);
		newNode->prev = prevNode;
		newNode->next = std::move(prevNode->next);

		Node* newNodeRaw = newNode.get();
		newNodeRaw->next->prev = newNodeRaw;
		prevNode->next = std::move(newNode);

		return iterator{ newNodeRaw };
	}
	iterator erase(iterator itr) {
		Node* current = itr.getNode();
		Node* prevNode = current->prev;
		std::unique_ptr<Node>& currentPtr = prevNode->next;

		currentPtr = std::move(current->next);
		if (currentPtr)
			currentPtr->prev = prevNode;

		return iterator{ currentPtr.get() };
	}
	void traverse(std::function<void(T&)>doIt) {
		for (Node* curr = head->next.get(); curr != tail; curr = curr->next.get()) {
			doIt(curr->data);
		}
	}
};
