#include "Products.h"
#include <string>
#include <iostream>

Products::Products(
    std::string _product_id,
    std::string _product_name,
    std::string _product_category,
    std::string _product_subcategory,
    std::string _brand,
    std::string _supplier,
    double _unit_price,
    double _product_cost,
    double _product_rating
)
:   product_id(_product_id),
    product_name(_product_name), 
    product_category(_product_category), 
    product_subcategory(_product_subcategory),
    brand(_brand),
    supplier(_supplier),
    unit_price(_unit_price),
    product_cost(_product_cost),
    product_rating(_product_rating)
{

}


