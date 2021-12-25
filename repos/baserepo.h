#ifndef BASEREPO_H
#define BASEREPO_H

#include <vector>
#include <map>
#include <string>

template <typename T>
class BaseRepo
{
public:
    BaseRepo() = default;
    virtual ~BaseRepo() = default;

    virtual std::vector<int> find(const std::map<std::string, std::string> values) = 0;
    virtual std::vector<T> getAll() = 0;
    virtual T* get(int id) = 0;
    virtual void Create(T item) = 0;
    virtual void Update(T item) = 0;
    virtual void Delete(int id) = 0;

    virtual std::vector<T> getSorted(const int& sort) = 0;
    virtual std::vector<T> getFiltered(const std::map<std::string, std::string> filters) = 0;
};

#endif // BASEREPO_H
