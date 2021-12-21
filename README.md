# tumorgrowthandradiationeffect
Cadmium
First you need to have cadmium installed in your computer ( You can use this link if you need to setup your environment: http://www.sce.carleton.ca/courses/sysc-5104/lib/exe/fetch.php?media=cadmium.pdf)
Delete the existed CMakeLists.txt in ell-DEVS-Model/Cadmium-CellDEVS-SampleModels forlder.
Then clone the repositories of this project from GtHub to the Cell-DEVS-Model/Cadmium-CellDEVS-SampleModels forlder.
Instead of the procedures included in the manual for visualization attached here as instructions.docx for creating the message.log, structure.json and style.json I included the path to the web_results in the main file, coupled file. You should change this to your directory: #include "/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/cadmium-web-extension/include/web/web_results.hpp"
and change the following line at the end of the main file according to your directory:  web::convert_cell_devs(fields,"/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/Cell-DEVS-Models/Cadmium-CellDEVS-SampleModels/cancer/config.json","/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/Cell-DEVS-Models/Cadmium-CellDEVS-SampleModels/logs/cancer_state.txt","/home/mahya/CADMIUM2/Cadmium-Simulation-Environment/Cell-DEVS-Models/Cadmium-CellDEVS-SampleModels/logs/");
Then open the terminal in the cancer file and write the command below:
cd ..
make
cd bin
./cancer ../cancer/config.json

The outputs  and the message.log, structure.json and style.json are generated in the log file.
Drop the message.log, structure.json and style.json files to this link https://staubibr.github.io/app-simple/index.html and then Then follow the rest of the steps explained in the instruction file.
