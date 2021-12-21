/**
 * Mahya Shahmohammadi
 * ARSLab - Carleton University

 */

#ifndef CELLDEVS_CANCER_CELL_HPP
#define CELLDEVS_CANCER_CELL_HPP

#include <cmath>
#include <nlohmann/json.hpp>
#include <cadmium/celldevs/cell/grid_cell.hpp>
#include "../state.hpp"
#include "../vicinity.hpp"
#include <ctime>

using namespace cadmium::celldevs;

/**
 * Configuration for basic Susceptible-Infected-Recovered model for Cadmium Cell-DEVS
 */
struct sird_cell_config {
    float migP1;    /// in this example, migP1 is provided using a configuration structure
    float migP2;
    float migCSC;
    float recovP1;     /// in this example, recovP1 is provided using a configuration structure
    float recovP2;     /// in this example, recovP2 is provided using a configuration structure
    float radiorecovp1;    /// in this example, radiorecovP1 is provided using a configuration structure
    float radiorecovp2;     /// in this example, radiorecovP2 is provided using a configuration structure
    float radiorecovcsc;    /// in this example, radiorecovcsc is provided using a configuration structure
    
   // int currentTime;
 
};

/**
 * We need to implement the from_json method for the desired cell configuration struct.
 * Otherwise, Cadmium will not be able to understand the JSON configuration file.
 * @param j Chunk of JSON file that represents a cell state
 * @param s cell configuration struct to be filled with the configuration shown in the JSON file.
 */
void from_json(const nlohmann::json& j, sird_cell_config &c) {
    j.at("migP1").get_to(c.migP1);
    j.at("migP2").get_to(c.migP2);
    j.at("migCSC").get_to(c.migCSC);
    j.at("recovP1").get_to(c.recovP1);
    j.at("recovP2").get_to(c.recovP2);
    j.at("radiorecovP1").get_to(c.radiorecovp1);
    j.at("radiorecovP2").get_to(c.radiorecovp2);
    j.at("radiorecovcsc").get_to(c.radiorecovcsc);
}

/**

 */
template <typename T>
/// sird_cell inherits the grid_cell class. As specified by the template, cell state uses the sir struct, and vicinities the mc struct
class [[maybe_unused]] sird_cell : public grid_cell<T, sird, mc> {
public:
    // We must specify which attributes of the base class we are going to use
    using grid_cell<T, sird, mc>::simulation_clock;
    using grid_cell<T, sird, mc>::state;
    using grid_cell<T, sird, mc>::map;
    using grid_cell<T, sird, mc>::neighbors;
    
    time_t sttime;
    
    sird_cell_config cell_config;

    sird_cell() : grid_cell<T, sird, mc>() {}

    [[maybe_unused]] sird_cell(cell_position const &cell_id, cell_unordered<mc> const &neighborhood, sird initial_state,
                                cell_map<sird, mc> const &map_in, std::string const &delay_id, sird_cell_config config) :
            grid_cell<T, sird, mc>(cell_id, neighborhood, initial_state, map_in, delay_id), cell_config(config) {
            
            
            sttime=time(NULL);
    }

    /**

     */
    [[nodiscard]] sird local_computation() const override {
        //startradio = true;
        sird res = state.current_state;  // first, we make a copy of the cell's current state and store it in the variable res
        float new_p1 = new_P1(res);  // to compute the percentage of new infections, we implement an auxiliary method.
        float new_p2 = new_P2(res);  // to compute the percentage of new infections, we implement an auxiliary method.
        float new_csc = new_CSC(res);  // to compute the percentage of new infections, we implement an auxiliary method.
        
        
        
        /*

        */
        
        
        
        
        
        
        res.stradio++;
        
        
        
        
//        res.P1cells = std::min(std::round(std::max((res.P1cells + new_p1),(float)0) * 100) / 100,(float)100);
        res.P1cells = std::max(std::min(std::round((res.P1cells + new_p1) * 100) / 100,(float)20),(float)0);
//        res.P2cells = std::min(std::round(std::max((res.P2cells + new_p2),(float)0) * 100) / 100,(float)100);
        res.P2cells = std::max(std::min(std::round((res.P2cells + new_p2) * 100) / 100,(float)30),(float)0);
        
//        res.CSC = std::min(std::round((res.CSC + new_csc)  / 100),(float)100);
        res.CSC = std::max(std::min(std::round((res.CSC + new_csc)* 100)  / 100,(float)50),(float)0);
        
        
        
        
        
                
        res.normalcells = res.totalcells - std::max(res.P1cells,(float)0) - std::max(res.P2cells,(float)0) - std::max(res.CSC,(float)0);
        
        
        
        
        return res;
    }

    /**

     */
    T output_delay(sird const &cell_state) const override {
        return 1;  // in this example, the delay is always 1 simulation tick.
    }

    /**

     */
    [[nodiscard]] float new_P1(sird const &c_state) const {
        float sumP1 = 0;
        //cell_config.recovP1++;

        for(auto neighbor: neighbors) {
            sird n = state.neighbors_state.at(neighbor);
            mc v = state.neighbors_vicinity.at(neighbor);
            sumP1 += (n.P1cells * (float) cell_config.migP1 * v.evacuation) - (n.P1cells * (float) cell_config.recovP1) - radioeffect(n.CSC,(float) cell_config.radiorecovp1,n.stradio) ;
        }
        return sumP1;
        
        //return std::min(sumP1,(float)0);
        

    }

    [[nodiscard]] float new_P2(sird const &c_state) const {
        float sumP2 = 0;
        //return 2;


        for(auto neighbor: neighbors) {
            sird n = state.neighbors_state.at(neighbor);
            mc v = state.neighbors_vicinity.at(neighbor);
            sumP2 += ((float)n.P2cells * (float) cell_config.migP2 * (float)v.evacuation) - (n.P2cells * (float) cell_config.recovP2) - radioeffect(n.CSC,(float) cell_config.radiorecovp2,n.stradio) ;
        }
        return sumP2;
        
        //return std::max(sumP2,(float)0);
        

    }

    [[nodiscard]] float new_CSC(sird const &c_state) const {
        float sumCSC = 0;
        //return 20;

        for(auto neighbor: neighbors) {
            sird n = state.neighbors_state.at(neighbor);
            mc v = state.neighbors_vicinity.at(neighbor);
            sumCSC += ((float)n.CSC * (float) cell_config.migCSC * (float)v.evacuation) - radioeffect(n.CSC,(float) cell_config.radiorecovcsc,n.stradio) ;
        }
        return sumCSC;
        //return std::max(std::min(sumCSC,(float)100),(float)0.0);
        

    }

	//static int t123=0;
	[[nodiscard]] float radioeffect(float currentValCSC,float radioRate,float stradio) const {
	//return 0.0;
		if(currentValCSC>=40 || stradio>10)
		{
			
		float rslt = (radioRate);

			return rslt;
			

		}

		return 0.0;
		
	
		

    	}


};
#endif //CELLDEVS_CANCER_CELL_HPP
