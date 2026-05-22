//
//  todolist.h
//  TodoListCpp
//
//  Created by Cornelius Ohiani Mamman on 5/12/26.
//

#ifndef todolist_h
#define todolist_h

#include <iostream>
#include <array>
#include <string>
#include <optional>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <stdexcept>

class TodoList
{
public:
    enum class Priority
    {
        Low = 1,
        Medium = 2,
        High = 3
    };

    enum class Status
    {
        Pending,
        InProgress,
        Completed
    };

    struct Task
    {
        std::string title;
        std::string description;
        Priority priority;
        Status status;
        std::chrono::system_clock::time_point createdAt;
        std::optional<std::chrono::system_clock::time_point> completedAt;

        Task() = default;

        Task(const std::string &t,
             const std::string &d = "",
             Priority p = Priority::Medium)
            : title(t),
              description(d),
              priority(p),
              status(Status::Pending),
              createdAt(std::chrono::system_clock::now()),
              completedAt(std::nullopt)
        {
        }

        // Explicitly enable copy/move operations
        Task(const Task &) = default;
        Task(Task &&) = default;

        Task &operator=(const Task &) = default;
        Task &operator=(Task &&) = default;

        ~Task() = default;
    };

private:
    static constexpr size_t MAX_TASKS = 100;

    // Properly initialized
    std::array<std::optional<Task>, MAX_TASKS> tasks{};

    size_t taskCount = 0;

    size_t findFirstEmpty() const;

public:
    TodoList() = default;
    ~TodoList() = default;

    bool addTask(const std::string &title,
                 const std::string &description = "",
                 Priority priority = Priority::Medium);

    bool removeTask(size_t index);

    size_t clearCompleted();

    bool editTask(size_t index, const std::string &newTitle, const std::string &newDescription = "");

    bool setPriority(size_t index, Priority priority);

    bool markInProgress(size_t index);

    bool markCompleted(size_t index);

    bool markPending(size_t index);

    std::optional<Task> getTask(size_t index) const;

    void displayAll() const;

    void displayByStatus(Status status) const;

    void displayByPriority(Priority priority) const;

    void search(const std::string &keyword) const;

    void sortByPriority();

    void sortByStatus();

    size_t getCountByStatus(Status status) const;

    size_t getCountByPriority(Priority priority) const;

    size_t getTotalTasks() const
    {
        return taskCount;
    }

    size_t getRemainingTasks() const;

    void clearAll();

    bool isEmpty() const
    {
        return taskCount == 0;
    }

    bool isFull() const
    {
        return taskCount >= MAX_TASKS;
    }

    double getCompletionPercentage() const;

    void displayStatistics() const;

private:
    std::string priorityToString(Priority p) const;

    std::string statusToString(Status s) const;

    std::string formatTime(const std::chrono::system_clock::time_point &tp) const;
};


#endif /* todolist_h */
