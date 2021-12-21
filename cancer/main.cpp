/**
 * Mahya Shah
 * ARSLab - Carleton University

 */

#include <fstream>
#include <cadmium/modeling/dynamic_coupled.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>
#include "model/cancer_coupled.hpp"
#include "/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/cadmium-web-extension/include/web/web_results.hpp"

using namespace std;
using namespace cadmium;
using namespace cadmium::celldevs;

using TIME = float;

/*************** Loggers *******************/
static ofstream out_messages("../logs/cancer_outputs.txt");
struct oss_sink_messages{
    static ostream& sink(){
        return out_messages;
    }
};
static ofstream out_state("../logs/cancer_state.txt");
struct oss_sink_state{
    static ostream& sink(){
        return out_state;
    }
};

using state=logger::logger<logger::logger_state, dynamic::logger::formatter<TIME>, oss_sink_state>;
using log_messages=logger::logger<logger::logger_messages, dynamic::logger::formatter<TIME>, oss_sink_messages>;
using global_time_mes=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_messages>;
using global_time_sta=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_state>;

using logger_top=logger::multilogger<state, log_messages, global_time_mes, global_time_sta>;


int main(int argc, char ** argv) {
    if (argc < 2) {
        cout << "Program used with wrong parameters. The program must be invoked as follows:";
        cout << argv[0] << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME (default: 20)]" << endl;
        return -1;
    }

    sirds_coupled<TIME> test = sirds_coupled<TIME>("spatial_sird");
    std::string scenario_config_file_path = argv[1];
    test.add_lattice_json(scenario_config_file_path);
    test.couple_cells();

    std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> t = std::make_shared<sirds_coupled<TIME>>(test);

    cadmium::dynamic::engine::runner<TIME, logger_top> r(t, {0});
    float sim_time = (argc > 2)? atof(argv[2]) : 20;
    r.run_until(sim_time);

    std::vector<std::string> fields = {"totalcells","P1cells","P2cells","CSC","normalcells"};
    
    web::convert_cell_devs(fields,"/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/Cell-DEVS-Models/Cadmium-CellDEVS-SampleModels/cancer/config.json","/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/Cell-DEVS-Models/Cadmium-CellDEVS-SampleModels/logs/cancer_state.txt","/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/Cell-DEVS-Models/Cadmium-CellDEVS-SampleModels/logs/");
    return 0;
}
