/**
 * Mahya Shah
 * ARSLab - Carleton University

 */

#ifndef CELLDEVS_CANCER_STATE_HPP
#define CELLDEVS_CANCER_STATE_HPP

#include <nlohmann/json.hpp>

/**
 * IN OUR EXAMPLE, CELLS' STATE WILL BE REPRESENTED WITH AN OBJECT OF THE SIR STRUCT
 */
struct sird {
    unsigned int totalcells;    /// Number of individuals that live in the cell
    float P1cells;          /// Percentage (from 0 to 1) of people that are P1cells to the disease
    float P2cells;             /// Percentage (from 0 to 1) of people that are P2cells
    float normalcells;            /// Percentage (from 0 to 1) of people that already normalcells from the disease
    float CSC;             /// Percentage (from 0 to 1) of people that CSC due to the disease
    float stradio;             /// Percentage (from 0 to 1) of people that CSC due to the disease
    sird() : totalcells(0), P1cells(1), P2cells(0), normalcells(0), CSC(0) {}  // a default constructor is required
    sird(unsigned int pop, float s, float i, float r, float d) : totalcells(pop), P1cells(s),
                                                                P2cells(i), normalcells(r), CSC(d) {}
};

/**

 */
inline bool operator != (const sird &x, const sird &y) {
    return x.totalcells != y.totalcells ||
           x.P1cells != y.P1cells || x.P2cells != y.P2cells ||
           x.normalcells != y.normalcells || x.CSC != y.CSC;
}

/**
 
 */
std::ostream &operator << (std::ostream &os, const sird &x) {
    //os << "<" << x.totalcells << "," << x.P1cells << "," << x.P2cells << "," << x.CSC  << "," << x.normalcells << ">";
    os  << x.totalcells << "," << x.P1cells << "," << x.P2cells << "," << x.CSC  << "," << x.normalcells;//<< ", " << x.stradio;
    return os;
}

/**

 */
[[maybe_unused]] void from_json(const nlohmann::json& j, sird &s) {
    j.at("totalcells").get_to(s.totalcells);
    j.at("P1cells").get_to(s.P1cells);
    j.at("P2cells").get_to(s.P2cells);
    j.at("normalcells").get_to(s.normalcells);
    j.at("CSC").get_to(s.CSC);
    j.at("stradio").get_to(s.stradio);
    
}

#endif //CELLDEVS_CANCER_STATE_HPP
