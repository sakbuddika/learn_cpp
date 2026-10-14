#pragma once
#include <string>

class Products {
    public:
        Products(
            std::string product_id,
            std::string product_name,
            std::string product_category,
            std::string product_subcategory,
            std::string brand,
            std::string supplier,
            double unit_price,
            double product_cost,
            double product_rating);

        std::string product_id;
        std::string product_name;
        std::string product_category;
        std::string product_subcategory;
        std::string brand;
        std::string supplier;
        double unit_price;
        double product_cost;
        double product_rating;
};