#include <mpi.h>
#include <string>
#include <vector>
#include <boost/program_options.hpp>

#include "utils/ReadData.h"
#include "utils/WriteData.h"

int main(int argc, char** argv)
{
  MPI_Init(NULL, NULL);
  
  namespace po = boost::program_options;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("file", po::value<std::string>(), "Input file")
    ("json", po::value<std::string>(), "Fides JSON data model file")        
    ("output", po::value<std::string>(), "Output file")
    ("index", po::value<int>(), "Dataset index")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  auto data = xenia::utils::ReadData(vm);
  int index = vm["index"].as<int>();

  if (index < data.GetNumberOfPartitions())
    xenia::utils::WriteData(data, vm["output"].as<std::string>());
  else
    std::cerr<<"Error: index out of range."<<std::endl;

  MPI_Finalize();
  return 0;
}
