#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Forward declaration
class DialogNode;

// Structure for a response option
struct Response {
    std::string text;
    std::shared_ptr<DialogNode> nextNode; // Pointer to the next dialog node
};

// Class representing a dialog node
class DialogNode {
public:
    std::string dialogText;
    std::vector<Response> responses;

    // Constructor
    DialogNode(std::string text) : dialogText(std::move(text)) {}

    // Display the dialog and choices
    void display() {
        std::cout << dialogText << "\n";
        for (size_t i = 0; i < responses.size(); i++) {
            std::cout << i + 1 << ". " << responses[i].text << "\n";
        }
    }

    // Navigate to the next node
    std::shared_ptr<DialogNode> getNextNode() {
        if (responses.empty()) {
            return nullptr;
        }

        int choice;
        while (true) {
            std::cout << "Choose an option: ";
            std::cin >> choice;

            if (choice >= 1 && choice <= static_cast<int>(responses.size())) {
                return responses[choice - 1].nextNode;
            } else {
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

// Function to create a sample dialog tree
std::shared_ptr<DialogNode> createDialogTree() {
    auto start = 
      std::make_shared<DialogNode>("Welcome, traveler! What brings you here?");
    auto askAboutTown = 
      std::make_shared<DialogNode>("This is Eldoria, a peaceful village.");
    auto askForHelp = 
      std::make_shared<DialogNode>("We need help with bandits nearby.");
    auto goodbye = 
       std::make_shared<DialogNode>("Safe travels, stranger!");

    // Adding response options
    start->responses = {
        {"Tell me about this town.", askAboutTown},
        {"Do you need any help?", askForHelp},
        {"Goodbye.", goodbye}
    };

    askAboutTown->responses = {
        {"That sounds nice.", goodbye},
        {"Do you need any help?", askForHelp}
    };

    askForHelp->responses = {
        {"I will help you!", goodbye},
        {"That sounds dangerous.", goodbye}
    };

    return start;
}

// Main function
int main() {
    std::shared_ptr<DialogNode> currentNode = createDialogTree();

    while (currentNode) {
        currentNode->display();
        currentNode = currentNode->getNextNode();
    }

    std::cout << "Conversation ended.\n";
    return 0;
}
