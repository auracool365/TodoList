//
//  todolist.cpp
//  TodoListCpp
//
//  Created by Cornelius Ohiani Mamman on 5/13/26.
//

#include "todolist.h"

#include <sstream>
#include <ctime>

// Finds the first available empty slot in the task array.
size_t TodoList::findFirstEmpty() const
{
    for (size_t i = 0; i < MAX_TASKS; ++i)
    {
        if (!tasks[i].has_value())
        {
            return i;
        }
    }

    return MAX_TASKS;
}

// Adds a new task to the todo list.
bool TodoList::addTask(const std::string &title, const std::string &description, Priority priority)
{
    if (isFull())
    {
        std::cerr << "Error: Task list is full!" << std::endl;
        return false;
    }

    if (title.empty())
    {
        std::cerr << "Error: Task title cannot be empty!" << std::endl;
        return false;
    }

    size_t index = findFirstEmpty();

    if (index == MAX_TASKS)
    {
        std::cerr << "Error: No empty slot found!" << std::endl;
        return false;
    }

    tasks[index] = Task(title, description, priority);

    taskCount++;

    std::cout << "Task added successfully!" << std::endl;

    return true;
}

// Removes a task using its array index.
bool TodoList::removeTask(size_t index)
{
    if (index >= MAX_TASKS || !tasks[index].has_value())
    {
        std::cerr << "Error: Invalid task index!" << std::endl;
        return false;
    }

    tasks[index] = std::nullopt;

    taskCount--;

    std::cout << "Task removed successfully!" << std::endl;

    return true;
}

// Removes all completed tasks from the list.
size_t TodoList::clearCompleted()
{
    size_t removed = 0;

    for (size_t i = 0; i < MAX_TASKS; ++i)
    {
        if (tasks[i].has_value() && tasks[i]->status == Status::Completed)
        {
            tasks[i] = std::nullopt;
            ++removed;
        }
    }

    taskCount -= removed;

    std::cout << "Removed " << removed << " completed task(s)." << std::endl;

    return removed;
}

// Updates a task title and description.
bool TodoList::editTask(size_t index,
                        const std::string &newTitle,
                        const std::string &newDescription)
{
    if (index >= MAX_TASKS || !tasks[index].has_value())
    {
        std::cerr << "Error: Invalid task index!" << std::endl;
        return false;
    }

    if (newTitle.empty())
    {
        std::cerr << "Error: Task title cannot be empty!" << std::endl;
        return false;
    }

    tasks[index]->title = newTitle;

    if (!newDescription.empty())
    {
        tasks[index]->description = newDescription;
    }

    std::cout << "Task updated successfully!" << std::endl;

    return true;
}

// Changes the priority level of a task.
bool TodoList::setPriority(size_t index, Priority priority)
{
    if (index >= MAX_TASKS || !tasks[index].has_value())
    {
        std::cerr << "Error: Invalid task index!" << std::endl;
        return false;
    }

    tasks[index]->priority = priority;

    std::cout << "Priority updated successfully!" << std::endl;

    return true;
}

// Marks a task as currently in progress.
bool TodoList::markInProgress(size_t index)
{
    if (index >= MAX_TASKS || !tasks[index].has_value())
    {
        std::cerr << "Error: Invalid task index!" << std::endl;
        return false;
    }

    tasks[index]->status = Status::InProgress;

    std::cout << "Task marked as in progress!" << std::endl;

    return true;
}

// Marks a task as completed and stores completion time.
bool TodoList::markCompleted(size_t index)
{
    if (index >= MAX_TASKS || !tasks[index].has_value())
    {
        std::cerr << "Error: Invalid task index!" << std::endl;
        return false;
    }

    tasks[index]->status = Status::Completed;

    tasks[index]->completedAt = std::chrono::system_clock::now();

    std::cout << "Task marked as completed!" << std::endl;

    return true;
}

// Resets a task back to pending state.
bool TodoList::markPending(size_t index)
{
    if (index >= MAX_TASKS || !tasks[index].has_value())
    {
        std::cerr << "Error: Invalid task index!" << std::endl;
        return false;
    }

    tasks[index]->status = Status::Pending;

    tasks[index]->completedAt = std::nullopt;

    std::cout << "Task marked as pending!" << std::endl;

    return true;
}

// Retrieves a task safely using std::optional.
std::optional<TodoList::Task>
TodoList::getTask(size_t index) const
{
    if (index >= MAX_TASKS || !tasks[index].has_value())
    {
        return std::nullopt;
    }

    return tasks[index];
}

// Converts a priority enum to readable text.
std::string TodoList::priorityToString(Priority p) const
{
    switch (p)
    {
    case Priority::Low:
        return "Low";

    case Priority::Medium:
        return "Medium";

    case Priority::High:
        return "High";

    default:
        return "Unknown";
    }
}

// Converts a status enum to readable text.
std::string TodoList::statusToString(Status s) const
{
    switch (s)
    {
    case Status::Pending:
        return "Pending";

    case Status::InProgress:
        return "In Progress";

    case Status::Completed:
        return "Completed";

    default:
        return "Unknown";
    }
}

// Formats a time_point into a human-readable string.
std::string TodoList::formatTime(
    const std::chrono::system_clock::time_point &tp) const
{
    auto time = std::chrono::system_clock::to_time_t(tp);

    std::tm buffer{};

#ifdef __APPLE__
    localtime_r(&time, &buffer);
#else
    buffer = *std::localtime(&time);
#endif

    std::stringstream ss;

    ss << std::put_time(&buffer, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

// Displays every task in the todo list.
void TodoList::displayAll() const
{
    if (isEmpty())
    {
        std::cout << "No tasks in the list." << std::endl;

        return;
    }

    std::cout << "\nTodo List\n";

    for (size_t i = 0; i < MAX_TASKS; ++i)
    {
        if (tasks[i].has_value())
        {
            const auto &task = tasks[i].value();

            std::cout
                << "[" << i << "] "
                << task.title
                << "\nPriority: "
                << priorityToString(task.priority)
                << "\nStatus: "
                << statusToString(task.status)
                << "\nCreated: "
                << formatTime(task.createdAt)
                << "\n";

            if (!task.description.empty())
            {
                std::cout << "Description: " << task.description << "\n";
            }

            std::cout << "\n";
        }
    }
}

// Displays tasks filtered by status.
void TodoList::displayByStatus(Status status) const
{
    bool found = false;

    for (size_t i = 0; i < MAX_TASKS; ++i)
    {
        if (tasks[i].has_value() && tasks[i]->status == status)
        {
            std::cout << "[" << i << "] " << tasks[i]->title << std::endl;

            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No tasks found." << std::endl;
    }
}

// Displays tasks filtered by priority.
void TodoList::displayByPriority(Priority priority) const
{
    bool found = false;

    for (size_t i = 0; i < MAX_TASKS; ++i)
    {
        if (tasks[i].has_value() && tasks[i]->priority == priority)
        {
            std::cout << "[" << i << "] " << tasks[i]->title << std::endl;

            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No tasks found." << std::endl;
    }
}

// Searches for tasks using a keyword match.
void TodoList::search(const std::string &keyword) const
{
    bool found = false;

    for (size_t i = 0; i < MAX_TASKS; ++i)
    {
        if (tasks[i].has_value())
        {
            const auto &task = tasks[i].value();

            if (task.title.find(keyword) != std::string::npos || task.description.find(keyword) != std::string::npos)
            {
                std::cout << "[" << i << "] " << task.title << std::endl;

                found = true;
            }
        }
    }

    if (!found)
    {
        std::cout << "No matching tasks found." << std::endl;
    }
}

// Sorts tasks from highest to lowest priority.
void TodoList::sortByPriority()
{
    std::array<std::optional<Task>, MAX_TASKS> tempTasks{};

    size_t index = 0;

    for (int p = 3; p >= 1; --p)
    {
        for (size_t i = 0; i < MAX_TASKS; ++i)
        {
            if (tasks[i].has_value() && static_cast<int>(tasks[i]->priority) == p)
            {
                tempTasks[index++] = tasks[i];
            }
        }
    }

    // tasks = tempTasks;
    std::copy(tempTasks.begin(), tempTasks.end(), tasks.begin());

    std::cout << "Tasks sorted by priority." << std::endl;
}

// Sorts tasks based on workflow status.
void TodoList::sortByStatus()
{
    std::array<std::optional<Task>, MAX_TASKS> tempTasks{};

    size_t index = 0;

    std::array<Status, 3> statusOrder = { Status::InProgress, Status::Pending, Status::Completed};

    for (const auto &status : statusOrder)
    {
        for (size_t i = 0; i < MAX_TASKS; ++i)
        {
            if (tasks[i].has_value() && tasks[i]->status == status)
            {
                tempTasks[index++] = tasks[i];
            }
        }
    }

    // tasks = tempTasks;
    std::copy(tempTasks.begin(), tempTasks.end(), tasks.begin());

    std::cout << "Tasks sorted by status." << std::endl;
}

// Counts tasks with a specific status.
size_t TodoList::getCountByStatus(Status status) const
{
    size_t count = 0;

    for (size_t i = 0; i < MAX_TASKS; ++i)
    {
        if (tasks[i].has_value() && tasks[i]->status == status)
        {
            count++;
        }
    }

    return count;
}

// Counts tasks with a specific priority.
size_t TodoList::getCountByPriority(Priority priority) const
{
    size_t count = 0;

    for (size_t i = 0; i < MAX_TASKS; ++i)
    {
        if (tasks[i].has_value() && tasks[i]->priority == priority)
        {
            count++;
        }
    }

    return count;
}

// Returns the number of unfinished tasks.
size_t TodoList::getRemainingTasks() const
{
    return getCountByStatus(Status::Pending) + getCountByStatus(Status::InProgress);
}

// Removes every task from the todo list.
void TodoList::clearAll()
{
    tasks.fill(std::nullopt);

    taskCount = 0;

    std::cout << "All tasks cleared." << std::endl;
}

// Calculates the percentage of completed tasks.
double TodoList::getCompletionPercentage() const
{
    if (taskCount == 0)
    {
        return 0.0;
    }

    return (static_cast<double>(getCountByStatus(Status::Completed)) / taskCount) * 100.0;
}

// Displays task statistics and completion progress.
void TodoList::displayStatistics() const
{
    std::cout
        << "\nStatistics:\n";

    std::cout
        << "Total Tasks: "
        << getTotalTasks()
        << std::endl;

    std::cout
        << "Pending: "
        << getCountByStatus(Status::Pending)
        << std::endl;

    std::cout
        << "In Progress: "
        << getCountByStatus(Status::InProgress)
        << std::endl;

    std::cout
        << "Completed: "
        << getCountByStatus(Status::Completed)
        << std::endl;

    std::cout
        << "Remaining: "
        << getRemainingTasks()
        << std::endl;

    std::cout
        << std::fixed
        << std::setprecision(2);

    std::cout
        << "Completion Rate: "
        << getCompletionPercentage()
        << "%"
        << std::endl;
}
