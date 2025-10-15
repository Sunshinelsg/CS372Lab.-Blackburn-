//
// File:   ExpTree.cpp
// Author: <Your Glorious Instructor>
// Purpose:
// Use the tree class from lecture to build an expression tree. By intent, we
// don't use inheritance here as we're using the Tree rather than extending it.
//
#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include "Tree.hpp"
using namespace std;

enum NodeTypes { NUMBER, OPERATOR};

// We define an ExpNode to represent a node in the expression tree. 
// It can either be a number (operand) or an operator (op).
// The new C++ feature here is the use of the spaceship operator (<=>) for comparison,
// which allows us to compare ExpNode objects based on their members.  Note that this requires
// C++20 or later.  The compiler sees this and generates the necessary comparison operators for us.
struct ExpNode {
    NodeTypes nodetype;
    double operand;
    string op;
    ExpNode(NodeTypes typ, double opd = 0, string opr = "") :nodetype(typ), operand(opd), op(opr) {}
    ExpNode(double opd): nodetype(NUMBER), operand(opd), op("") {}
    ExpNode(string op): nodetype(OPERATOR), operand(0.0), op(op) {}
	ExpNode() : nodetype(NUMBER), operand(0.0), op("") {}
    auto operator<=>(const ExpNode& rhs) const = default;
};
void printNode(ExpNode aNode) {
    if (aNode.nodetype == NUMBER) { std::cout << aNode.operand << " ";}
    else if (aNode.nodetype == OPERATOR) {std::cout << aNode.op << " "; }
    else { std::cout << "BAD NODE IN EXP TREE\n"; }
}

// We define a TreeOfExpNodes as a Tree of ExpNode objects. Cuts down on the line noise.
using TreeOfExpNodes = Tree<ExpNode>;
stack<TreeOfExpNodes> nodes;
stack<char> operations;

// This function builds an expression tree from an input stream.
TreeOfExpNodes & buildExpTree(istream &ins) {
    const char DECIMAL = '.';
    const char RIGHTPAREN = ')';
    TreeOfExpNodes leftOp;
    TreeOfExpNodes rightOp;
    string str;
    while (ins && ins.peek() != '\n') {
        if (isdigit(ins.peek()) || (ins.peek() == DECIMAL)) {
            double opd;
            ins >> opd;
            std::cout << "NUMBER: " << opd << " ";
            ExpNode * aNewNode = new ExpNode(opd);
            nodes.push( TreeOfExpNodes{ *aNewNode } );
        }
        else if (strchr("+-*/", ins.peek())!= nullptr) {
            char opc;
            ins >> opc;
            std::cout << "OP: " << opc << " ";
            operations.push( opc );
        }
        else if (ins.peek() == RIGHTPAREN) {
            std::cout << "RIGHTPAREN ";
            ins.ignore();
            rightOp = nodes.top();
            nodes.pop();
            leftOp = nodes.top();
            nodes.pop();
            str = "";
            str += operations.top();
			operations.pop();
            ExpNode * aNewNode = new ExpNode(str);
            nodes.push( TreeOfExpNodes(leftOp, *aNewNode, rightOp) );
        }
        else {
            ins.ignore();
        }
    }
    return nodes.top();
}

// This function computes the result of applying an operator to two operands.
double computeOp(string op, double leftrand, double rightrand) {
    double result = 0.0;
    if (op == "+") {
        result = leftrand + rightrand;
    }
    else if (op == "-") {
        result = leftrand - rightrand;
    }
    else if (op == "*") {
        result = leftrand * rightrand;
    }
    else if (op == "/") {
        result = leftrand / rightrand;
    }
    else {
        std::cerr << "Bad operator in expression, operator was " << op << std::endl;
    }
    return result;
}
//
// Algorithm:
// Do an in-order traversal of the tree (note: will
// need to adjust the return type of the function)
//
// If anExpTree is not empty
//    if anExpTree. root is an operand
//       return that value
//    else
//        A = evalExpTRee(anExpTree.left())
//        B = evalExpTree(anExpTree.right())
//        Op = anExpTree.root()
//        return A Op B
//
double evalExpTree(TreeOfExpNodes anExpTree) {
    if (!anExpTree.isEmpty()) {
        if (anExpTree.root().nodetype == NUMBER) {
            return anExpTree.root().operand;
		}
        else {
            // We have an operator node, so we need to evaluate the left and right subtrees
            // and then apply the operator to the results.
            if (anExpTree.left().isEmpty() || anExpTree.right().isEmpty()) {
                std::cerr << "Error: Operator node with empty subtree(s)." << std::endl;
                return 0; // or throw an exception
            }
            double A = evalExpTree(anExpTree.left());
            double B = evalExpTree(anExpTree.right());
            ExpNode opnode = anExpTree.root();
            return computeOp(opnode.op, A, B);
        }
    }
    else {
        return 0;
    }
}

// This function prompts the user for an expression, builds the expression tree,
// and then evaluates the expression tree, printing the results of the traversals.
// End results is the expression gets evaluated and the result is printed. And
// while we're at it, let's print the pre-order and in-order traversals of the expression tree
// so that we see the pre-fix and post-fix forms of the expression.
void doIt() {
    cout << "Enter an expression in infix format: ";
    TreeOfExpNodes expTree = buildExpTree(cin);
    cout << "Pre-order traversal of expression tree" << endl;
    expTree.preorder(printNode);
    cout << "In-order traversal of expression tree" << endl;
    expTree.inorder(printNode);
    double result = evalExpTree(expTree);
    std::cout << "Result of evaluated expression is: " << result << std::endl;
}

// The main function repeatedly prompts the user to enter an expression,
// which is an example of a REPL: Read-Eval-Print Loop. This is a common pattern in
// interactive programming environments, allowing users to enter expressions,
// evaluate them, and see the results immediately.
//
// Take note of how the input pressing is done. We read the input 
// until a newline character is encountered, 
// allowing for multi-character operators and numbers with decimal points.  But this does not
// handle whitespace well, so we ignore whitespace characters in the input stream.
int main(int argc, char *argv[]) {
    while (true) { 
        doIt();
		cout << "Do another (y/n)? ";
		char response;

		cin >> response;

        if (response != 'y' && response != 'Y') {
            break;
        }
        // Reset cin
        cin.clear(); // Clear any error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input in the buffer

    }
    return 0;
}
