#ifndef WAREHOUSEREPO_H
#define WAREHOUSEREPO_H

#include "baserepo.h"

class Warehouse;

class WarehouseRepo : public BaseRepo<Warehouse>
{
public:
    enum WAREHOUSE_FILTERS{
        IDUp,
        IDDown
    };

    WarehouseRepo();
    std::vector<int> find(const std::map<std::string, std::string> values) override;
    std::vector<Warehouse> getAll() override;
    Warehouse* get(int id) override;
    void Create(Warehouse item) override;
    void Update(Warehouse item) override;
    void Delete(int id) override;

    std::vector<Warehouse> getSorted(const int& sort) override;
};

#endif // WAREHOUSEREPO_H
