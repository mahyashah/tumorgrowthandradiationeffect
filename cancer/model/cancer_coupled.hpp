/**
 * Mahya Shahmohammadi
 * ARSLab - Carleton University

 */

#ifndef CELLDEVS_CANCER_COUPLED_HPP
#define CELLDEVS_CANCER_COUPLED_HPP

#include <nlohmann/json.hpp>
#include <cadmium/celldevs/coupled/grid_coupled.hpp>
#include "state.hpp"
#include "vicinity.hpp"
#include "cells/cancer_cell.hpp"
#include "/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/cadmium-web-extension/include/web/web_results.hpp"

/**
 * We need to define a grid_coupled class that knows all the different types of cells that the scenario may have.
 * @tparam T type used to represent simulation time.
 */
template <typename T>
class sirds_coupled : public cadmium::celldevs::grid_coupled<T, sird, mc> {
public:

    explicit sirds_coupled(std::string const &id) : grid_coupled<T, sird, mc>(id){}

    /**

     */
    void add_grid_cell_json(std::string const &cell_type, cell_map<sird, mc> &map, std::string const &delay_id,
                            nlohmann::json const &config) override {
        if (cell_type == "sird") {
            // In this first example, we only have one cell type: the sir cell.
            // We only have to call the add_cell method with the corresponding cell type in the template
            auto conf = config.get<sird_cell_config>();
            this->template add_cell<sird_cell>(map, delay_id, conf);
        } else throw std::bad_typeid();
    }
};

#endif //CELLDEVS_CANCER_COUPLED_HPP
