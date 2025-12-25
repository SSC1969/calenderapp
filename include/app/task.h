#pragma once
#include <chrono>
#include <string>

class Task {
  public:
    std::string name;
    std::optional<std::string> description;

    int getId() const { return this->id; }
    void setId(int id) { this->id = id; }

    std::string getStart() const {
        return std::format("{:%F %R}", this->start_point);
    }
    void setStart(std::string start) {
        std::stringstream stss(start);
        stss >> std::chrono::parse("%F %R", this->start_point);
    }
    void setStartFromPoint(std::chrono::system_clock::time_point start) {
        this->start_point = start;
    }

    std::optional<std::string> getDuration() const {
        if (duration == std::chrono::duration<double>::zero()) {
            return {};
        }
        return std::format("{:%T}", this->duration);
    }
    void setDuration(std::optional<std::string> duration) {
        if (!duration) {
            return;
        }
        std::stringstream stss(duration.value());
        stss >> std::chrono::parse("%T", this->duration);
    }

    bool getCompleted() const { return this->completed; }
    void setCompleted(bool completed) { this->completed = completed; }

    friend std::ostream &operator<<(std::ostream &os, const Task &t) {
        return os << "[" << t.id << "](" << t.name << ", "
                  << t.description.value_or("none") << ", "
                  << t.start_point << ", " << t.duration << ", "
                  << t.completed << ")";
    }

  private:
    std::chrono::system_clock::time_point start_point =
        std::chrono::system_clock::now();
    std::chrono::duration<double> duration =
        std::chrono::duration<double>::zero();
    bool completed = false;

    int id = -1;
};
