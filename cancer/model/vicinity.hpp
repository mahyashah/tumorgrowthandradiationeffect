/**
 * Mahya Shah
 * ARSLab - Carleton University

 */

#ifndef CELLDEVS_CANCER_VICINITY_HPP
#define CELLDEVS_CANCER_VICINITY_HPP

#include <nlohmann/json.hpp>

/**
 * IN OUR EXAMPLE, VICINITY BETWEEN CELLS WILL BE REPRESENTED WITH AN OBJECT OF THE MC STRUCT
 */
struct mc {
    float evacuation;     /// evacuation factor from 0 to 1 (i.e. how easy it is to move from one cell to another)

    mc() : evacuation(0) {}  // a default constructor is required
    mc(float c) : evacuation(c) {}
};

/**
 * We need to implement the from_json method for the desired cells vicinity struct.
 * Otherwise, Cadmium will not be able to understand the JSON configuration file.
 * @param j Chunk of JSON file that represents a cell state
 * @param v cells vicinity struct to be filled with the configuration shown in the JSON file.
 */
[[maybe_unused]] void from_json(const nlohmann::json& j, mc &v) {
    j.at("evacuation").get_to(v.evacuation);

}

#endif //CELLDEVS_CANCER_VICINITY_HPP
