//
//  main.cpp
//  TodoListCpp
//
//  Created by Cornelius Ohiani Mamman on 5/12/26.
//

#include "todolist.h"
#include <print>

void displayMenu()
{
    std::cout << "Todo List Application System \n";
    std::cout << " 1.  Add Task                      | 9.  Mark Task Completed           \n";
    std::cout << " 2.  View All Tasks                | 10. Mark Task Pending             \n";
    std::cout << " 3.  View Tasks by Status          | 11. Remove Task                   \n";
    std::cout << " 4.  View Tasks by Priority        | 12. Sort by Priority              \n";
    std::cout << " 5.  Search Tasks                  | 13. Sort by Status                \n";
    std::cout << " 6.  Edit Task                     | 14. Clear Completed Tasks         \n";
    std::cout << " 7.  Set Task Priority             | 15. Display Statistics            \n";
    std::cout << " 8.  Mark Task In Progress         | 16. Clear All Tasks               \n";
    std::cout << "                    0.  Exit           \n";
    std::cout << "\nChoose an option: ";
}

TodoList::Priority selectPriority()
{
    int choice;
    std::cout << "Select priority: (1(Low), 2(Medium), 3(High): ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice)
    {
    case 1:
        return TodoList::Priority::Low;
    case 2:
        return TodoList::Priority::Medium;
    case 3:
        return TodoList::Priority::High;
    default:
        std::cout << "Invalid choice. Setting to Medium.\n";
        return TodoList::Priority::Medium;
    }
}

TodoList::Status selectStatus()
{
    int choice;
    std::cout << "Select status: \n 1(Pending), 2(In Progress), 3(Completed): ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice)
    {
    case 1:
        return TodoList::Status::Pending;
    case 2:
        return TodoList::Status::InProgress;
    case 3:
        return TodoList::Status::Completed;
    default:
        std::cout << "Invalid choice. Setting to Pending." << std::endl;
        return TodoList::Status::Pending;
    }
}

void demonstrateFeatures(TodoList &todoList)
{
    std::cout << "\nDemonstrating features\n"
              << std::endl;

    // Add multiple tasks
    std::cout << "Adding sample tasks\n";
    todoList.addTask("Complete project report", "Finish quarterly report by Friday", TodoList::Priority::High);
    todoList.addTask("Buy groceries", "Milk, eggs, bread, and vegetables", TodoList::Priority::Low);
    todoList.addTask("Review pull requests", "Check 5 pending PRs", TodoList::Priority::Medium);
    todoList.addTask("Exercise", "30 minutes cardio at gym", TodoList::Priority::Medium);
    todoList.addTask("Schedule meeting", "With project stakeholders", TodoList::Priority::High);

    // Display all tasks
    std::cout << "\nDisplaying all tasks..." << std::endl;
    todoList.displayAll();

    // Display by status
    std::cout << "Tasks still pending..." << std::endl;
    todoList.displayByStatus(TodoList::Status::Pending);

    // Display by priority
    std::cout << "High priority tasks..." << std::endl;
    todoList.displayByPriority(TodoList::Priority::High);

    // Mark some tasks as in progress
    std::cout << "Marking tasks as in progress..." << std::endl;
    todoList.markInProgress(0);
    todoList.markInProgress(2);

    // Display updated status
    std::cout << "Tasks currently in progress..." << std::endl;
    todoList.displayByStatus(TodoList::Status::InProgress);

    // Complete some tasks
    std::cout << "Completing some tasks..." << std::endl;
    todoList.markCompleted(1);
    todoList.markCompleted(3);

    // Search for tasks
    std::cout << "Searching for 'project'..." << std::endl;
    todoList.search("project");

    // Display statistics
    std::cout << "Displaying statistics..." << std::endl;
    todoList.displayStatistics();

    // Sort by priority
    std::cout << "Sorting tasks by priority..." << std::endl;
    todoList.sortByPriority();
    todoList.displayAll();
}

void interactiveMode(TodoList &todoList)
{
    int choice = -1;

    while (choice != 0)
    {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            std::cout << "\nAdd New Task" << std::endl;
            std::string title, description;
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter task description (optional): ";
            std::getline(std::cin, description);
            auto priority = selectPriority();
            todoList.addTask(title, description, priority);
            break;
        }

        case 2:
            std::cout << "\nAll Tasks" << std::endl;
            todoList.displayAll();
            break;

        case 3:
        {
            std::cout << "\nSelect status to view:" << std::endl;
            auto status = selectStatus();
            todoList.displayByStatus(status);
            break;
        }

        case 4:
        {
            std::cout << "\nSelect priority to view:" << std::endl;
            auto priority = selectPriority();
            todoList.displayByPriority(priority);
            break;
        }

        case 5:
        {
            std::string keyword;
            std::cout << "Enter search keyword: ";
            std::getline(std::cin, keyword);
            todoList.search(keyword);
            break;
        }

        case 6:
        {
            size_t index;
            std::cout << "Enter task ID to edit: ";
            std::cin >> index;
            std::cin.ignore();
            std::string newTitle, newDesc;
            std::cout << "Enter new title: ";
            std::getline(std::cin, newTitle);
            std::cout << "Enter new description (optional): ";
            std::getline(std::cin, newDesc);
            todoList.editTask(index, newTitle, newDesc);
            break;
        }

        case 7:
        {
            size_t index;
            std::cout << "Enter task ID to update priority: ";
            std::cin >> index;
            std::cin.ignore();
            auto priority = selectPriority();
            todoList.setPriority(index, priority);
            break;
        }

        case 8:
        {
            size_t index;
            std::cout << "Enter task ID to mark as in progress: ";
            std::cin >> index;
            std::cin.ignore();
            todoList.markInProgress(index);
            break;
        }

        case 9:
        {
            size_t index;
            std::cout << "Enter task ID to mark as completed: ";
            std::cin >> index;
            std::cin.ignore();
            todoList.markCompleted(index);
            break;
        }

        case 10:
        {
            size_t index;
            std::cout << "Enter task ID to mark as pending: ";
            std::cin >> index;
            std::cin.ignore();
            todoList.markPending(index);
            break;
        }

        case 11:
        {
            size_t index;
            std::cout << "Enter task ID to remove: ";
            std::cin >> index;
            std::cin.ignore();
            todoList.removeTask(index);
            break;
        }

        case 12:
            todoList.sortByPriority();
            todoList.displayAll();
            break;

        case 13:
            todoList.sortByStatus();
            todoList.displayAll();
            break;

        case 14:
            todoList.clearCompleted();
            break;

        case 15:
            todoList.displayStatistics();
            break;

        case 16:
        {
            std::string confirm;
            std::cout << "Are you sure you want to clear all tasks? (yes/no): ";
            std::getline(std::cin, confirm);
            if (confirm == "yes")
            {
                todoList.clearAll();
            }
            break;
        }

        case 0:
            std::cout << "Exiting... Goodbye!" << std::endl;
            break;

        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
}

int main()
{
    std::println("Hello World, I am so happy"); // testing C++23
    TodoList todoList;

    std::cout << "Oasis Todo List Application\n";

    int mode;

    std::cout << "Select mode:" << std::endl;
    std::cout << "1. Demo Mode (Showcase features)" << std::endl;
    std::cout << "2. Interactive Mode (Todo List Operations)" << std::endl;
    std::cout << "Enter mode(1 or 2): ";
    std::cin >> mode;
    std::cin.ignore();

    if (mode == 1)
    {
        demonstrateFeatures(todoList);
    }
    else if (mode == 2)
    {
        interactiveMode(todoList);
    }
    else
    {
        std::cout << "Invalid mode selected. Exiting." << std::endl;
    }

    return 0;
}

