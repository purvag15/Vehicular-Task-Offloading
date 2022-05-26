#include "veins_inet/vfognetsim/mecoMessages/VeinsInetAppForMeco.h"

#include "veins_inet/vfognetsim/mecoMessages/MIPSAdvertisementByMeco_m.h"

#include "veins_inet/vfognetsim/rsuMessages/MIPSAckByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskAssignmentByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskCompletionAckByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskCompletionMsgByRSU_m.h"
#include "veins_inet/vfognetsim/rsuMessages/TaskRequestAckByRSU_m.h"

#include "veins_inet/vfognetsim/vehicleMessages/TaskCompletionAckByVehicle_m.h"
#include "veins_inet/vfognetsim/vehicleMessages/TaskRequestByVehicle_m.h"
#include "veins_inet/vfognetsim/mecoMessages/CollectRequests_m.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include<string>

#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include<fstream>
#include<iostream>
#include <ctime>
#include <string>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <valarray>
#include <vector>

#include "vector_ops.hpp" // Custom header file for vector operations
#include <bits/stdc++.h>
using namespace std;

using namespace inet;

Define_Module(VeinsInetAppForMeco);

VeinsInetAppForMeco::VeinsInetAppForMeco()
{
}

bool VeinsInetAppForMeco::startApplication()
{
        auto callback = [this]() {
        };
        timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(20, SIMTIME_S)));
    return true;
}

bool VeinsInetAppForMeco::stopApplication()
{
    return true;
}

VeinsInetAppForMeco::~VeinsInetAppForMeco()
{
}

#define rand_01 ((float)rand() / (float)RAND_MAX)

float F_il = rand_01 + 0.5;
const int numofpart = 10000;
const int numofdims = 3 * numofpart;

float info[numofpart * 4];

using namespace std;

float util[4] = {0},cap[4] = {0,500,600,700};

//calculate qos for PSO
float calc_qos(int j,int ai,float bi,float fi)
{
    float ci = info[j]/1000;    //input size
    float ei_l = info[j + numofpart];   //No of CPU cycles required
    float Ti_latency = info[j + 2 * numofpart]; //Delay tolerance
    float di = info[j+ 3 * numofpart];  // distance

    float cons = 0.0553;
    cons = cons/pow(di,2);
    cons = 1 + cons;
    cons = log2(cons);

    float ri = bi * cons * 1e+6;       // rate of transfer
    float T_mission = ci/ri;           // transmission time
    float ei = T_mission * ri;

    float T_exec = ei/fi;             // Task execution time
    float Tsys = 0.01;                // system delay
    float T_comp =  Tsys + T_mission + T_exec; //totaltime for edge execution

    float P_il = 10;                 // Power for local execution
    float T_local = Tsys + ei_l / F_il; // totaltime for local execution
    float E_local = P_il * T_local;     // Energy for local execution
    float P_tmission = 23;              // Power for edge execution
    float E_comp = P_tmission * T_mission; // Energy for edge execution
    float T_i, E_i, qos;

    if(ai > 0){                           // offloading decision , 0 -> local
        T_i = T_comp;
        E_i = E_comp;
    }
    else{                                // ai > 0 , edge execution
        T_i = T_local;
        E_i = E_local;
    }

    float B =0.8 ;                       // constant factors
    float Y =0.2 ;
    if(T_i <= Ti_latency)                // totaltime required < delay tolerance
        qos = B * ((T_local - T_i)/T_local) + Y * ((E_local - E_i)/E_local); //QoS calculation

    else
       qos = 0;
     return qos;
}

//calculate QOS
double qualityOfService(double ci, double ei_l, double T1, int ai, double bi, double fi, double Tsys, double di)
{
    double cons = 0.0553;
    cons = cons/pow(di/250,2);
    cons = 1 + cons;
    cons = log2(cons);

    double ri = bi * cons* 1000000;
    double T_mission = ci/(ri*1000*10);
    double ei = T_mission * (ri*1000);

    double T_exec = ei/(fi*1000*1000);
    double T_pr = di/(3 * 100000000);
    double T_comp =  Tsys + T_mission + T_exec + T_pr;

    if(ai==0) T_comp=0;

    double P_il = 10;
    double T_local = Tsys + ei_l / 1000*F_il;

    if(T_local==0) T_local = 0.001;

    double E_local = P_il * T_local;
    double P_tmission = 23;
    double E_comp = P_tmission * T_mission;
    if(ai==0) E_comp =0;

    if(T_local==0) T_local = 0.0001;

    double T_i, E_i, qos;

    if(ai > 0){
        T_i = T_comp;
        E_i = E_comp;
    }
    else{
        T_i = T_local;
        E_i = E_local;
    }

    double B = 0.8 ;
    double Y = 0.2 ;
    if(T_i <= T1)
        qos = B * ((T_local - T_i)/T_local) + Y * ((E_local - E_i)/E_local);
    else
       qos = 0;
    if(ai == 0) qos*=0.6;
    else qos*=0.85;
     return qos;
}

//Fitness Function for PSO
void fitnessfunc(float X[numofdims], float fitnesses[numofpart])
{
    memset(fitnesses, 0, sizeof (float) * numofpart);
        for(int j = 0; j < numofpart/3; j++)
        {
            fitnesses[j] += calc_qos(j,(int)X[j],X[j + numofpart],X[ j + 2*numofpart]);
        }
}

//Function to implement PSO
void PSO(int numofiterations, float c1, float c2,
               float initialpop[numofdims],float info[numofdims], float &gbestfit, float gbest[3])
{
    float V[numofdims] = {0};           // Velocity vector
    float X[numofdims];                 // Position vector
    float pbests[numofdims];            // pbests for particles
    float pbestfits[numofpart];
    float fitnesses[numofpart];         // fitnesses of particles of current generation
    float w;                            // weight factor
    float maxfit;                       // max fitness
    int maxfitindx;                     //max fitness index
    float total = 0;

    memcpy(X, initialpop, sizeof(float) * numofdims);   //copy initial pop to temporary vector
    fitnessfunc(X, fitnesses);
    maxfit = *max_element(fitnesses, fitnesses + numofpart);
    maxfitindx = max_element(fitnesses, fitnesses + numofpart) - fitnesses;

    gbestfit = maxfit;                     //global best fitness
    gbest[0] = X[maxfitindx];
    gbest[1] = X[maxfitindx + numofpart];
    gbest[2] = X[maxfitindx + 2 * numofpart];

    for(int t = 0; t < numofiterations; t++)      // run for t iterations
    {
        w = 0.9 - 0.7 * (float) (t / numofiterations);

        for(int i = 0; i < numofpart; i++)       //updating pbest
        {
            if(fitnesses[i] > pbestfits[i])
            {
                pbestfits[i] = fitnesses[i];
                pbests[i] = X[i];
                pbests[i+numofpart] = X[i + numofpart];
                pbests[i+ 2 * numofpart] = X[i + 2 * numofpart];
            }
            if(X[i] > 0)
                {
                    int a = (int)X[i];
                  util[a] += (1/cap[a]) * ( 1 * info[i+numofpart]);

                }
        }
        float LB = 0;                   //Load balancing
        float U_mean = (util[1] + util[2] + util[3])/3; // Utilization
                for(int j = 1;j <= 3;j++)
                {
                    LB += (1/3) * pow( (util[j] - U_mean),2);
                    total = 0;
                    for(int i = 0;i<numofpart;i++)
                    {   if(X[i] == j)
                        total += X[i + 2*numofpart];
                    }

                }
            for(int j = 0; j < numofdims; j++)  //velocity and position vectors updation
            {
                V[j] = (w* V[j] + rand_01 * c1 * (pbests[j] - X[j])
                                   + rand_01 * c2 * (gbest[j/numofpart]));
                X[j] = (X[j] + V[j]);

                if(LB > 1000)
                fitnesses[j/numofpart] -= 2;

               if(j < 1 * numofpart)
                {
                    if( X[j] < 0)
                   { fitnesses[j/3] -= abs(0 - X[j]);
                     X[j] = (int) rand() % 4;
                   }
                    else if(X[j] > 3 )
                   {
                    fitnesses[j/3] -= abs(3 - X[j]);
                    X[j] =  rand() % 4;

                   }
                }
                else if(j < (2 * numofpart))
                {
                    if( X[j] < 0)
                    {
                        fitnesses[j/3] -= abs(0 - X[j]);
                    X[j] = 0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2-0)));
                    }
                    else if(X[j] > 2 )
                    {
                    fitnesses[j/3] -= abs(2 - X[j]);
                    X[j] = 0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2-0)));
                    }
                }
                else
                {
                    if( X[j] < 5)
                    {
                    fitnesses[j/3] -= abs(5 - X[j]);
                    X[j] = 5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(25-5)));
                    }
                    else if(X[j] > 25 )
                    {
                    fitnesses[j/3] -= abs(25 - X[j]);
                    X[j] = 5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(25-5)));
                    }
                }
            }
    }
        memcpy(initialpop,X, sizeof(float) * numofdims);
        fitnessfunc(X, fitnesses);
        maxfit = *max_element(fitnesses, fitnesses + numofpart);
        maxfitindx = max_element(fitnesses, fitnesses + numofpart) - fitnesses;
        if(maxfit > gbestfit)
        {
            gbestfit = maxfit;
            gbest[0] = X[maxfitindx];
            gbest[1] = X[maxfitindx + numofpart];
            gbest[2] = X[maxfitindx + 2 * numofpart];
        }
    }

void callForPSO()
{
    time_t t;
        srand((unsigned) time(&t));

        float initpop[numofdims];          //initial population vector
        float gbestfit;
        float gbest[3];

    for(int j = 0; j < numofdims; j++)           // Initializing population
    {
        if(j < 1 * numofpart)
        {
            initpop[j] = rand() % 4 ;         //ai
            info[j] =  10 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1000-10)));   // input size

        }
        else if(j < (2 * numofpart))
        {
         initpop[j] =  (0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2-0))));       //bi

         info[j] = (int) (20 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2000-20))));       // no of cpu cycles
        }
        else if(j < (3 * numofpart))
        {
            initpop[j] = 5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(25-5)));          //fi
            info[j] =  (0.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-0.1))));     // delay tolerance
        }
    }

    for(int i = numofpart * 3;i < 4 * numofpart;i++)
    {
        info[i] = 5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20-5)));
    }
        PSO(1000, 2, 2, initpop,info, gbestfit, gbest);

        cout << "fitness: " << gbestfit << " ";

        //float v_left,rsu1_l,rsu2_l,rsu3_l;
        //int res = 0;

        //CSV part
                // file pointer
//                fstream fout;
//
//                // opens an existing csv file or creates a new file.
//                fout.open("offloading.csv", ios::out | ios::app);
//
//
//        //fout << "input_size," << "CPU_cycles_needed," << "delay_tolerance,"  << "v_left,"  << "rsu1_left," << "rsu2_left," << "rsu3_left," <<"computing_capacity_allocated" << endl;
//
//        fout << "input_size," << "CPU_cycles_needed," << "delay_tolerance,"  << "offloaded_to" << endl;
//
//        for(int i = 0;i<numofpart ;i++)
//        {
//
//        fout << info[i] << "," << info[i + numofpart] << "," << info[i + 2*numofpart] << "," <<  initpop[i] <<  endl;
//
//        }
}
//DNN Start
namespace machine_learning
{
    /** \namespace neural_network
     * \brief Neural Network or Multilayer Perceptron
     */
    namespace neural_network
    {
        /** \namespace activations
         * \brief Various activation functions used in Neural network
         */
        namespace activations
        {
            /**
             * Sigmoid function
             * @param X Value
             * @return Returns sigmoid(x)
             */
            double sigmoid(const double &x) { return 1.0 / (1.0 + std::exp(-x)); }

            /**
             * Derivative of sigmoid function
             * @param X Value
             * @return Returns derivative of sigmoid(x)
             */
            double dsigmoid(const double &x) { return x * (1 - x); }

            /**
             * Relu function
             * @param X Value
             * @returns relu(x)
             */
            double relu(const double &x) { return std::max(0.0, x); }

            /**
             * Derivative of relu function
             * @param X Value
             * @returns derivative of relu(x)
             */
            double drelu(const double &x) { return x >= 0.0 ? 1.0 : 0.0; }

            /**
             * Tanh function
             * @param X Value
             * @return Returns tanh(x)
             */
            double tanh(const double &x) { return 2 / (1 + std::exp(-2 * x)) - 1; }

            /**
             * Derivative of Sigmoid function
             * @param X Value
             * @return Returns derivative of tanh(x)
             */
            double dtanh(const double &x) { return 1 - x * x; }
        } // namespace activations
        /** \namespace util_functions
         * \brief Various utility functions used in Neural network
         */
        namespace util_functions
        {
            /**
             * Square function
             * @param X Value
             * @return Returns x * x
             */
            double square(const double &x) { return x * x; }
            /**
             * Identity function
             * @param X Value
             * @return Returns x
             */
            double identity_function(const double &x) { return x; }
        } // namespace util_functions
        /** \namespace layers
         * \brief This namespace contains layers used
         * in MLP.
         */
        namespace layers
        {
            /**
             * neural_network::layers::DenseLayer class is used to store all necessary
             * information about the layers (i.e. neurons, activation and kernel). This
             * class is used by NeuralNetwork class to store layers.
             *
             */
            class DenseLayer
            {
            public:
                // To store activation function and it's derivative
                double (*activation_function)(const double &);
                double (*dactivation_function)(const double &);
                int neurons;                               // To store number of neurons (used in summary)
                std::string activation;                    // To store activation name (used in summary)
                std::vector<std::valarray<double>> kernel; // To store kernel (aka weights)

                /**
                 * Constructor for neural_network::layers::DenseLayer class
                 * @param neurons number of neurons
                 * @param activation activation function for layer
                 * @param kernel_shape shape of kernel
                 * @param random_kernel flag for whether to intialize kernel randomly
                 */
                DenseLayer(const int &neurons, const std::string &activation,
                           const std::pair<size_t, size_t> &kernel_shape,
                           const bool &random_kernel)
                {
                    // Choosing activation (and it's derivative)
                    if (activation == "sigmoid")
                    {
                        activation_function = neural_network::activations::sigmoid;
                        dactivation_function = neural_network::activations::sigmoid;
                    }
                    else if (activation == "relu")
                    {
                        activation_function = neural_network::activations::relu;
                        dactivation_function = neural_network::activations::drelu;
                    }
                    else if (activation == "tanh")
                    {
                        activation_function = neural_network::activations::tanh;
                        dactivation_function = neural_network::activations::dtanh;
                    }
                    else if (activation == "none")
                    {
                        // Set identity function in casse of none is supplied
                        activation_function =
                            neural_network::util_functions::identity_function;
                        dactivation_function =
                            neural_network::util_functions::identity_function;
                    }
                    else
                    {
                        // If supplied activation is invalid
                        std::cerr << "ERROR (" << __func__ << ") : ";
                        std::cerr << "Invalid argument. Expected {none, sigmoid, relu, "
                                     "tanh} got ";
                        std::cerr << activation << std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    this->activation = activation; // Setting activation name
                    this->neurons = neurons;       // Setting number of neurons
                    // Initialize kernel according to flag
                    if (random_kernel)
                    {
                        uniform_random_initialization(kernel, kernel_shape, -1.0, 1.0);
                    }
                    else
                    {
                        unit_matrix_initialization(kernel, kernel_shape);
                    }
                }
                /**
                 * Constructor for neural_network::layers::DenseLayer class
                 * @param neurons number of neurons
                 * @param activation activation function for layer
                 * @param kernel values of kernel (useful in loading model)
                 */
                DenseLayer(const int &neurons, const std::string &activation,
                           const std::vector<std::valarray<double>> &kernel)
                {
                    // Choosing activation (and it's derivative)
                    if (activation == "sigmoid")
                    {
                        activation_function = neural_network::activations::sigmoid;
                        dactivation_function = neural_network::activations::sigmoid;
                    }
                    else if (activation == "relu")
                    {
                        activation_function = neural_network::activations::relu;
                        dactivation_function = neural_network::activations::drelu;
                    }
                    else if (activation == "tanh")
                    {
                        activation_function = neural_network::activations::tanh;
                        dactivation_function = neural_network::activations::dtanh;
                    }
                    else if (activation == "none")
                    {
                        // Set identity function in casse of none is supplied
                        activation_function =
                            neural_network::util_functions::identity_function;
                        dactivation_function =
                            neural_network::util_functions::identity_function;
                    }
                    else
                    {
                        // If supplied activation is invalid
                        std::cerr << "ERROR (" << __func__ << ") : ";
                        std::cerr << "Invalid argument. Expected {none, sigmoid, relu, "
                                     "tanh} got ";
                        std::cerr << activation << std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    this->activation = activation; // Setting activation name
                    this->neurons = neurons;       // Setting number of neurons
                    this->kernel = kernel;         // Setting supplied kernel values
                }

                /**
                 * Copy Constructor for class DenseLayer.
                 *
                 * @param model instance of class to be copied.
                 */
                DenseLayer(const DenseLayer &layer) = default;

                /**
                 * Destructor for class DenseLayer.
                 */
                ~DenseLayer() = default;

                /**
                 * Copy assignment operator for class DenseLayer
                 */
                DenseLayer &operator=(const DenseLayer &layer) = default;

                /**
                 * Move constructor for class DenseLayer
                 */
                DenseLayer(DenseLayer &&) = default;

                /**
                 * Move assignment operator for class DenseLayer
                 */
                DenseLayer &operator=(DenseLayer &&) = default;
            };
        } // namespace layers
        /**
         * NeuralNetwork class is implements MLP. This class is
         * used by actual user to create and train networks.
         *
         */
        class NeuralNetwork
        {
        private:
            std::vector<neural_network::layers::DenseLayer> layers; // To store layers
            /**
             * Private Constructor for class NeuralNetwork. This constructor
             * is used internally to load model.
             * @param config vector containing pair (neurons, activation)
             * @param kernels vector containing all pretrained kernels
             */
            NeuralNetwork(
                const std::vector<std::pair<int, std::string>> &config,
                const std::vector<std::vector<std::valarray<double>>> &kernels)
            {
                // First layer should not have activation
                if (config.begin()->second != "none")
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr
                        << "First layer can't have activation other than none got "
                        << config.begin()->second;
                    std::cerr << std::endl;
                    std::exit(EXIT_FAILURE);
                }
                // Network should have atleast two layers
                if (config.size() <= 1)
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr << "Invalid size of network, ";
                    std::cerr << "Atleast two layers are required";
                    std::exit(EXIT_FAILURE);
                }
                // Reconstructing all pretrained layers
                for (size_t i = 0; i < config.size(); i++)
                {
                    layers.emplace_back(neural_network::layers::DenseLayer(
                        config[i].first, config[i].second, kernels[i]));
                }
                std::cout << "INFO: Network constructed successfully" << std::endl;
            }
            /**
             * Private function to get detailed predictions (i.e.
             * activated neuron values). This function is used in
             * backpropagation, single predict and batch predict.
             * @param X input vector
             */
            std::vector<std::vector<std::valarray<double>>>
            __detailed_single_prediction(const std::vector<std::valarray<double>> &X)
            {
                std::vector<std::vector<std::valarray<double>>> details;
                std::vector<std::valarray<double>> current_pass = X;
                details.emplace_back(X);
                for (const auto &l : layers)
                {
                    current_pass = multiply(current_pass, l.kernel);
                    current_pass = apply_function(current_pass, l.activation_function);
                    details.emplace_back(current_pass);
                }
                return details;
            }

        public:
            /**
             * Default Constructor for class NeuralNetwork. This constructor
             * is used to create empty variable of type NeuralNetwork class.
             */
            NeuralNetwork() = default;

            /**
             * Constructor for class NeuralNetwork. This constructor
             * is used by user.
             * @param config vector containing pair (neurons, activation)
             */
            explicit NeuralNetwork(
                const std::vector<std::pair<int, std::string>> &config)
            {
                // First layer should not have activation
                if (config.begin()->second != "none")
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr
                        << "First layer can't have activation other than none got "
                        << config.begin()->second;
                    std::cerr << std::endl;
                    std::exit(EXIT_FAILURE);
                }
                // Network should have atleast two layers
                if (config.size() <= 1)
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr << "Invalid size of network, ";
                    std::cerr << "Atleast two layers are required";
                    std::exit(EXIT_FAILURE);
                }
                // Separately creating first layer so it can have unit matrix
                // as kernel.
                layers.push_back(neural_network::layers::DenseLayer(
                    config[0].first, config[0].second,
                    {config[0].first, config[0].first}, false));
                // Creating remaining layers
                for (size_t i = 1; i < config.size(); i++)
                {
                    layers.push_back(neural_network::layers::DenseLayer(
                        config[i].first, config[i].second,
                        {config[i - 1].first, config[i].first}, true));
                }
                std::cout << "INFO: Network constructed successfully" << std::endl;
            }

            /**
             * Copy Constructor for class NeuralNetwork.
             *
             * @param model instance of class to be copied.
             */
            NeuralNetwork(const NeuralNetwork &model) = default;

            /**
             * Destructor for class NeuralNetwork.
             */
            ~NeuralNetwork() = default;

            /**
             * Copy assignment operator for class NeuralNetwork
             */
            NeuralNetwork &operator=(const NeuralNetwork &model) = default;

            /**
             * Move constructor for class NeuralNetwork
             */
            NeuralNetwork(NeuralNetwork &&) = default;

            /**
             * Move assignment operator for class NeuralNetwork
             */
            NeuralNetwork &operator=(NeuralNetwork &&) = default;

            /**
             * Function to get X and Y from csv file (where X = data, Y = label)
             * @param file_name csv file name
             * @param last_label flag for whether label is in first or last column
             * @param normalize flag for whether to normalize data
             * @param slip_lines number of lines to skip
             * @return returns pair of X and Y
             */

            std::pair<std::pair<std::vector<std::vector<std::valarray<double>>>,
                                            std::vector<std::vector<std::valarray<double>>>>,
                                  std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>>
                        get_XY_from_csv_reg(const std::string &file_name, const bool &last_label,
                                            const bool &normalize, const int &slip_lines = 1)
                        {
                            std::ifstream in_file;                         // Ifstream to read file
                            in_file.open(file_name.c_str(), std::ios::in); // Open file
                            // If there is any problem in opening file
                            if (!in_file.is_open())
                            {
//                                std::cerr << "ERROR (" << _func_ << ") : ";
                                std::cerr << "Unable to open file: " << file_name << std::endl;
                                std::exit(EXIT_FAILURE);
                            }
                            std::vector<std::vector<std::valarray<double>>> X,
                                Y;            // To store X and Y
                            std::string line; // To store each line
                            // Skip lines
                            for (int i = 0; i < slip_lines; i++)
                            {
                                std::getline(in_file, line, '\n'); // Ignore line
                            }
                            // While file has information
                            while (!in_file.eof() && std::getline(in_file, line, '\n'))
                            {
                                std::valarray<double> x_data,
                                    y_data;                 // To store single sample and label
                                std::stringstream ss(line); // Constructing stringstream from line
                                std::string token;          // To store each token in line (seprated by ',')
                                while (std::getline(ss, token, ','))
                                { // For each token
                                    // Insert numerical value of token in x_data
                                    x_data = insert_element(x_data, std::stod(token));
                                }
                                // If label is in last column
                                if (last_label)
                                {
                                    y_data.resize(this->layers.back().neurons);
                                    // If task is classification
                                    if (y_data.size() > 1)
                                    {
                                        y_data[x_data[x_data.size() - 1]] = 1;
                                    }
                                    // If task is regrssion (of single value)
                                    else
                                    {
                                        y_data[0] = x_data[x_data.size() - 1];
                                    }
                                    x_data = pop_back(x_data); // Remove label from x_data
                                }
                                else
                                {
                                    y_data.resize(this->layers.back().neurons);
                                    // If task is classification
                                    if (y_data.size() > 1)
                                    {
                                        y_data[x_data[x_data.size() - 1]] = 1;
                                    }
                                    // If task is regrssion (of single value)
                                    else
                                    {
                                        y_data[0] = x_data[x_data.size() - 1];
                                    }
                                    x_data = pop_front(x_data); // Remove label from x_data
                                }
                                // Push collected X_data and y_data in X and Y
                                X.push_back({x_data});
                                Y.push_back({y_data});
                            }

                            // Normalize training data if flag is set

                            std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> minmaxes;

                            if (normalize)
                            {
                                // Scale data between 0 and 1 using min-max scaler
                                auto xx = minmax_scaler_minmax(X, 0.01, 1.0);
                                X = xx.first;
                                auto yy = minmax_scaler_minmax(Y, 0.01, 1.0);
                                Y = yy.first;
                                minmaxes = make_pair(xx.second, yy.second);
                            }
                            in_file.close(); // Closing file
                            auto dataset2 = make_pair(X, Y);
                            return make_pair(dataset2, minmaxes); // Return pair of X and Y
                        }


            std::pair<std::vector<std::vector<std::valarray<double>>>,
                      std::vector<std::vector<std::valarray<double>>>>
            get_XY_from_csv(const std::string &file_name, const bool &last_label,
                            const bool &normalize, const int &slip_lines = 1)
            {
                std::ifstream in_file;                         // Ifstream to read file
                in_file.open(file_name.c_str(), std::ios::in); // Open file
                // If there is any problem in opening file
                if (!in_file.is_open())
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr << "Unable to open file: " << file_name << std::endl;
                    std::exit(EXIT_FAILURE);
                }
                std::vector<std::vector<std::valarray<double>>> X,
                    Y;            // To store X and Y
                std::string line; // To store each line
                // Skip lines
                for (int i = 0; i < slip_lines; i++)
                {
                    std::getline(in_file, line, '\n'); // Ignore line
                }
                // While file has information
                while (!in_file.eof() && std::getline(in_file, line, '\n'))
                {
                    std::valarray<double> x_data,
                        y_data;                 // To store single sample and label
                    std::stringstream ss(line); // Constructing stringstream from line
                    std::string token;          // To store each token in line (seprated by ',')
                    while (std::getline(ss, token, ','))
                    { // For each token
                        // Insert numerical value of token in x_data
                        x_data = insert_element(x_data, std::stod(token));
                    }
                    // If label is in last column
                    if (last_label)
                    {
                        y_data.resize(this->layers.back().neurons);
                        // If task is classification
                        if (y_data.size() > 1)
                        {
                            y_data[x_data[x_data.size() - 1]] = 1;
                        }
                        // If task is regrssion (of single value)
                        else
                        {
                            y_data[0] = x_data[x_data.size() - 1];
                        }
                        x_data = pop_back(x_data); // Remove label from x_data
                    }
                    else
                    {
                        y_data.resize(this->layers.back().neurons);
                        // If task is classification
                        if (y_data.size() > 1)
                        {
                            y_data[x_data[x_data.size() - 1]] = 1;
                        }
                        // If task is regression (of single value)
                        else
                        {
                            y_data[0] = x_data[x_data.size() - 1];
                        }
                        x_data = pop_front(x_data); // Remove label from x_data
                    }
                    // Push collected X_data and y_data in X and Y
                    X.push_back({x_data});
                    Y.push_back({y_data});
                }
                // Normalize training data if flag is set
                if (normalize)
                {
                    // Scale data between 0 and 1 using min-max scaler
                    X = minmax_scaler(X, 0.01, 1.0);
                }
                in_file.close();        // Closing file
                return make_pair(X, Y); // Return pair of X and Y
            }



            /**
             * Function to get prediction of model on single sample.
             * @param X array of feature vectors
             * @return returns predictions as vector
             */
            std::vector<std::valarray<double>> single_predict(
                const std::vector<std::valarray<double>> &X)
            {
                // Get activations of all layers
                auto activations = this->__detailed_single_prediction(X);
                // Return activations of last layer (actual predicted values)
                return activations.back();
            }

            /**
             * Function to get prediction of model on batch
             * @param X array of feature vectors
             * @return returns predicted values as vector
             */
            std::vector<std::vector<std::valarray<double>>> batch_predict(
                const std::vector<std::vector<std::valarray<double>>> &X)
            {
                // Store predicted values
                std::vector<std::vector<std::valarray<double>>> predicted_batch(
                    X.size());
                for (size_t i = 0; i < X.size(); i++)
                { // For every sample
                    // Push predicted values
                    predicted_batch[i] = this->single_predict(X[i]);
                }
                return predicted_batch; // Return predicted values
            }

            /**
             * Function to fit model on supplied data
             * @param X array of feature vectors
             * @param Y array of target values
             * @param epochs number of epochs (default = 100)
             * @param learning_rate learning rate (default = 0.01)
             * @param batch_size batch size for gradient descent (default = 32)
             * @param shuffle flag for whether to shuffle data (default = true)
             */
            void fit(const std::vector<std::vector<std::valarray<double>>> &X_,
                     const std::vector<std::vector<std::valarray<double>>> &Y_,
                     const int &epochs = 100, const double &learning_rate = 0.01,
                     const size_t &batch_size = 32, const bool &shuffle = true)
            {
                std::vector<std::vector<std::valarray<double>>> X = X_, Y = Y_;
                // Both label and input data should have same size
                if (X.size() != Y.size())
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr << "X and Y in fit have different sizes" << std::endl;
                    std::exit(EXIT_FAILURE);
                }
                std::cout << "INFO: Training Started" << std::endl;
                for (int epoch = 1; epoch <= epochs; epoch++)
                { // For every epoch
                    // Shuffle X and Y if flag is set
                    if (shuffle)
                    {
                        equal_shuffle(X, Y);
                    }
                    auto start =
                        std::chrono::high_resolution_clock::now(); // Start clock
                    double loss = 0,
                           acc = 0; // Intialize performance metrics with zero
                    // For each starting index of batch
                    for (size_t batch_start = 0; batch_start < X.size();
                         batch_start += batch_size)
                    {
                        for (size_t i = batch_start;
                             i < std::min(X.size(), batch_start + batch_size); i++)
                        {
                            std::vector<std::valarray<double>> grad, cur_error,
                                predicted;
                            auto activations = this->__detailed_single_prediction(X[i]);
                            // Gradients vector to store gradients for all layers
                            // They will be averaged and applied to kernel
                            std::vector<std::vector<std::valarray<double>>> gradients;
                            gradients.resize(this->layers.size());
                            // First intialize gradients to zero
                            for (size_t i = 0; i < gradients.size(); i++)
                            {
                                zeroes_initialization(
                                    gradients[i], get_shape(this->layers[i].kernel));
                            }
                            predicted = activations.back(); // Predicted vector
                            cur_error = predicted - Y[i];   // Absoulute error
                            // Calculating loss with MSE
                            loss += sum(apply_function(
                                cur_error, neural_network::util_functions::square));
                            // If prediction is correct
                            if (argmax(predicted) == argmax(Y[i]))
                            {
                                acc += 1;
                            }
                            // For every layer (except first) starting from last one
                            for (size_t j = this->layers.size() - 1; j >= 1; j--)
                            {
                                // Backpropogating errors
                                cur_error = hadamard_product(
                                    cur_error,
                                    apply_function(
                                        activations[j + 1],
                                        this->layers[j].dactivation_function));
                                // Calculating gradient for current layer
                                grad = multiply(transpose(activations[j]), cur_error);
                                // Change error according to current kernel values
                                cur_error = multiply(cur_error,
                                                     transpose(this->layers[j].kernel));
                                // Adding gradient values to collection of gradients
                                gradients[j] = gradients[j] + grad / double(batch_size);
                            }
                            // Applying gradients
                            for (size_t j = this->layers.size() - 1; j >= 1; j--)
                            {
                                // Updating kernel (aka weights)
                                this->layers[j].kernel = this->layers[j].kernel -
                                                         gradients[j] * learning_rate;
                            }
                        }
                    }
                    auto stop =
                        std::chrono::high_resolution_clock::now(); // Stoping the clock
                    // Calculate time taken by epoch
                    auto duration =
                        std::chrono::duration_cast<std::chrono::microseconds>(stop -
                                                                              start);
                    loss /= X.size();       // Averaging loss
                    acc /= X.size();        // Averaging accuracy
                    std::cout.precision(4); // set output precision to 4
                    // Printing training stats
                    std::cout << "Training: Epoch " << epoch << '/' << epochs;
                    std::cout << ", Loss: " << loss;
                    std::cout << ", Accuracy: " << acc;
                    std::cout << ", Taken time: " << duration.count() / 1e6
                              << " seconds";
                    std::cout << std::endl;
                }
                return;
            }

            /**
             * Function to fit model on data stored in csv file
             * @param file_name csv file name
             * @param last_label flag for whether label is in first or last column
             * @param epochs number of epochs
             * @param learning_rate learning rate
             * @param normalize flag for whether to normalize data
             * @param slip_lines number of lines to skip
             * @param batch_size batch size for gradient descent (default = 32)
             * @param shuffle flag for whether to shuffle data (default = true)
             */
            void fit_from_csv(const std::string &file_name, const bool &last_label,
                              const int &epochs, const double &learning_rate,
                              const bool &normalize, const int &slip_lines = 1,
                              const size_t &batch_size = 32,
                              const bool &shuffle = true)
            {
                // Getting training data from csv file
                auto data =
                    this->get_XY_from_csv(file_name, last_label, normalize, slip_lines);
                // Fit the model on training data
                this->fit(data.first, data.second, epochs, learning_rate, batch_size,
                          shuffle);
                return;
            }

            std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> fit_from_csv_reg(const std::string &file_name, const bool &last_label, const int &epochs, const double &learning_rate, const bool &normalize, const int &slip_lines = 1, const size_t &batch_size = 32, const bool &shuffle = true)
                        {
                            // Getting training data from csv file
                            auto alldata =
                                this->get_XY_from_csv_reg(file_name, last_label, normalize, slip_lines);
                            auto data = alldata.first;
                            auto minmaxes = alldata.second;
                            // Fit the model on training data
                            this->fit(data.first, data.second, epochs, learning_rate, batch_size,
                                      shuffle);
                            return minmaxes;
                        }

            std::pair<std::vector<std::vector<std::valarray<double>>>, std::vector<std::vector<std::valarray<double>>>> XY_test(const std::string &file_name, const bool &last_label,
                                                                                                                                const bool &normalize, const int &slip_lines = 1)
            {
                std::ifstream in_file;                         // Ifstream to read file
                in_file.open(file_name.c_str(), std::ios::in); // Open file
                // If there is any problem in opening file
                if (!in_file.is_open())
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr << "Unable to open file: " << file_name << std::endl;
                    std::exit(EXIT_FAILURE);
                }
                std::vector<std::vector<std::valarray<double>>> X,
                    Y;            // To store X and Y
                std::string line; // To store each line
                // Skip lines
                for (int i = 0; i < slip_lines; i++)
                {
                    std::getline(in_file, line, '\n'); // Ignore line
                }
                // While file has information
                while (!in_file.eof() && std::getline(in_file, line, '\n'))
                {
                    std::valarray<double> x_data,
                        y_data;                 // To store single sample and label
                    std::stringstream ss(line); // Constructing stringstream from line
                    std::string token;          // To store each token in line (seprated by ',')
                    while (std::getline(ss, token, ','))
                    { // For each token
                        // Insert numerical value of token in x_data
                        x_data = insert_element(x_data, std::stod(token));
                    }
                    // If label is in last column
                    if (last_label)
                    {
                        y_data.resize(this->layers.back().neurons);
                        // If task is classification
                        if (y_data.size() > 1)
                        {
                            y_data[x_data[x_data.size() - 1]] = 1;
                        }
                        // If task is regression (of single value)
                        else
                        {
                            y_data[0] = x_data[x_data.size() - 1];
                        }
                        x_data = pop_back(x_data); // Remove label from x_data
                    }
                    else
                    {
                        y_data.resize(this->layers.back().neurons);
                        // If task is classification
                        if (y_data.size() > 1)
                        {
                            y_data[x_data[x_data.size() - 1]] = 1;
                        }
                        // If task is regrssion (of single value)
                        else
                        {
                            y_data[0] = x_data[x_data.size() - 1];
                        }
                        x_data = pop_front(x_data); // Remove label from x_data
                    }

                    // Push collected X_data and y_data in X and Y
                    X.push_back({x_data});
                    Y.push_back({y_data});
                }
                if (normalize)
                {
                    // Scale data between 0 and 1 using min-max scaler
                    X = minmax_scaler(X, 0.01, 1.0);
                }
                return make_pair(X, Y);
            }

            /**
             * Function to evaluate model on supplied data
             * @param X array of feature vectors (input data)
             * @param Y array of target values (label)
             */
            void evaluate(const std::vector<std::vector<std::valarray<double>>> &X,
                          const std::vector<std::vector<std::valarray<double>>> &Y)
            {
                std::cout << "INFO: Evaluation Started" << std::endl;
                double acc = 0, loss = 0; // intialize performance metrics with zero
                for (size_t i = 0; i < X.size(); i++)
                { // For every sample in input
                    // Get predictions
                    std::vector<std::valarray<double>> pred =
                        this->single_predict(X[i]);
                    // If predicted class is correct
                    if (argmax(pred) == argmax(Y[i]))
                    {
                        acc += 1; // Increment accuracy
                    }
                    // Calculating loss - Mean Squared Error
                    loss += sum(apply_function((Y[i] - pred),
                                               neural_network::util_functions::square) *
                                0.5);
                }
                acc /= X.size();  // Averaging accuracy
                loss /= X.size(); // Averaging loss
                // Prinitng performance of the model
                std::cout << "Evaluation: Loss: " << loss;
                std::cout << ", Accuracy: " << acc << std::endl;
                return;
            }

            void evaluate_reg(const std::vector<std::vector<std::valarray<double>>> &X,
                                          const std::vector<std::vector<std::valarray<double>>> &Y)
            {
                std::cout << "INFO: Evaluation Started" << std::endl;
                double acc = 0, loss = 0; // intialize performance metrics with zero
                for (size_t i = 0; i < X.size(); i++)
                { // For every sample in input
                    // Get predictions
                    std::vector<std::valarray<double>> pred =
                        this->single_predict(X[i]);
                    // If predicted class is correct
                    if (argmax(pred) == argmax(Y[i]))
                    {
                        acc += 1; // Increment accuracy
                    }
                    // Calculating loss - Mean Squared Error
                    loss += sum(apply_function((Y[i] - pred),
                                               neural_network::util_functions::square) *
                                0.5);
                }
                acc /= X.size();  // Averaging accuracy
                loss /= X.size(); // Averaging loss
                // Prinitng performance of the model
                std::cout << "Evaluation: Loss: " << loss;
                std::cout << ", Accuracy: " << acc << std::endl;
                return;
            }

            /**
             * Function to evaluate model on data stored in csv file
             * @param file_name csv file name
             * @param last_label flag for whether label is in first or last column
             * @param normalize flag for whether to normalize data
             * @param slip_lines number of lines to skip
             */
            void evaluate_from_csv_reg(const std::string &file_name, const bool &last_label,
                                       const bool &normalize, const int &slip_lines = 1)
            {
                // Getting training data from csv file
                auto data =
                    this->get_XY_from_csv_reg(file_name, last_label, normalize, slip_lines).first;
                // Evaluating model
                this->evaluate_reg(data.first, data.second);
                return;
            }

            /**
             * Function to evaluate model on data stored in csv file
             * @param file_name csv file name
             * @param last_label flag for whether label is in first or last column
             * @param normalize flag for whether to normalize data
             * @param slip_lines number of lines to skip
             */
            void evaluate_from_csv(const std::string &file_name, const bool &last_label,
                                   const bool &normalize, const int &slip_lines = 1)
            {
                // Getting training data from csv file
                auto data =
                    this->get_XY_from_csv(file_name, last_label, normalize, slip_lines);
                // Evaluating model
                this->evaluate(data.first, data.second);
                return;
            }

            /**
             * Function to save current model.
             * @param file_name file name to save model (*.model)
             */
            void save_model(const std::string &_file_name)
            {
                std::string file_name = _file_name;
                // Adding ".model" extension if it is not already there in name
                if (file_name.find(".model") == file_name.npos)
                {
                    file_name += ".model";
                }
                std::ofstream out_file; // Ofstream to write in file
                // Open file in out|trunc mode
                out_file.open(file_name.c_str(),
                              std::ofstream::out | std::ofstream::trunc);
                // If there is any problem in opening file
                if (!out_file.is_open())
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr << "Unable to open file: " << file_name << std::endl;
                    std::exit(EXIT_FAILURE);
                }


                out_file << layers.size();
                out_file << std::endl;
                for (const auto &layer : this->layers)
                {
                    out_file << layer.neurons << ' ' << layer.activation << std::endl;
                    const auto shape = get_shape(layer.kernel);
                    out_file << shape.first << ' ' << shape.second << std::endl;
                    for (const auto &row : layer.kernel)
                    {
                        for (const auto &val : row)
                        {
                            out_file << val << ' ';
                        }
                        out_file << std::endl;
                    }
                }
                std::cout << "INFO: Model saved successfully with name : ";
                std::cout << file_name << std::endl;
                out_file.close(); // Closing file
                return;
            }

            /**
             * Function to load earlier saved model.
             * @param file_name file from which model will be loaded (*.model)
             * @return instance of NeuralNetwork class with pretrained weights
             */
            NeuralNetwork load_model(const std::string &file_name)
            {
                std::ifstream in_file;           // Ifstream to read file
                in_file.open(file_name.c_str()); // Openinig file
                // If there is any problem in opening file
                if (!in_file.is_open())
                {
                    std::cerr << "ERROR (" << __func__ << ") : ";
                    std::cerr << "Unable to open file: " << file_name << std::endl;
                    std::exit(EXIT_FAILURE);
                }
                std::vector<std::pair<int, std::string>> config; // To store config
                std::vector<std::vector<std::valarray<double>>>
                    kernels; // To store pretrained kernels
                // Loading model from saved file format
                size_t total_layers = 0;
                in_file >> total_layers;
                for (size_t i = 0; i < total_layers; i++)
                {
                    int neurons = 0;
                    std::string activation;
                    size_t shape_a = 0, shape_b = 0;
                    std::vector<std::valarray<double>> kernel;
                    in_file >> neurons >> activation >> shape_a >> shape_b;
                    for (size_t r = 0; r < shape_a; r++)
                    {
                        std::valarray<double> row(shape_b);
                        for (size_t c = 0; c < shape_b; c++)
                        {
                            in_file >> row[c];
                        }
                        kernel.push_back(row);
                    }
                    config.emplace_back(make_pair(neurons, activation));
                    ;
                    kernels.emplace_back(kernel);
                }
                std::cout << "INFO: Model loaded successfully" << std::endl;
                in_file.close(); // Closing file
                return NeuralNetwork(
                    config, kernels); // Return instance of NeuralNetwork class
            }

            /**
             * Function to print summary of the network.
             */
            void summary()
            {
                // Printing Summary
                std::cout
                    << "==============================================================="
                    << std::endl;
                std::cout << "\t\t+ MODEL SUMMARY +\t\t\n";
                std::cout
                    << "==============================================================="
                    << std::endl;
                for (size_t i = 1; i <= layers.size(); i++)
                { // For every layer
                    std::cout << i << ")";
                    std::cout << " Neurons : "
                              << layers[i - 1].neurons; // number of neurons
                    std::cout << ", Activation : "
                              << layers[i - 1].activation; // activation
                    std::cout << ", kernel Shape : "
                              << get_shape(layers[i - 1].kernel); // kernel shape
                    std::cout << std::endl;
                }
                std::cout
                    << "==============================================================="
                    << std::endl;
                return;
            }
        };
    } // namespace neural_network
} // namespace machine_learning

//Regression Model for prediction of bandwidth
machine_learning::neural_network::NeuralNetwork myNNreg =
    machine_learning::neural_network::NeuralNetwork({
        {7, "none"},
        {64, "relu"}, // First layer with 3 neurons and "none" as activation
        {1, "relu"}   // Third layer with 3 neurons and "sigmoid" as
                      // activation
    });
// Training Model
auto minmaxesBandwidth = myNNreg.fit_from_csv_reg("bandwidth.csv", true, 10, 0.3, true, 2, 8, true);


//test function for bandwidth prediction
static void test()
{
    double a, b, c, d;
    vector<double> topredict({694.818, 515.062, 537.822, 94.4924, 497, 122.111, 48});
    std::valarray<double> test(topredict.size());
    for (int i = 0; i < topredict.size(); i++)
    {
        test[i] = topredict[i];
    }
    for (int i = 0; i < test.size(); i++)
    {
        int min1 = minmaxesBandwidth.first[i][0];
        int max1 = minmaxesBandwidth.first[i][1];

        test[i] = (test[i] - min1) / (max1 - min1) * (0.99) + 0.01;
    }
    std::vector<std::valarray<double>> x = myNNreg.single_predict({test});

    int sliplines = 1;
    std::pair<std::vector<std::vector<std::valarray<double>>>, std::vector<std::vector<std::valarray<double>>>> xy_test = myNNreg.XY_test("bandwidthTest.csv", true, true, sliplines);

    std::vector<double> bandwidthPredicted;
    for (auto i : xy_test.first)
    {
        std::vector<std::valarray<double>> x = myNNreg.single_predict({i});
        for (auto i : x)
        {
            for (auto j : i)
            {
                bandwidthPredicted.push_back(((j - 0.01) * (minmaxesBandwidth.second[0][1] - minmaxesBandwidth.second[0][0]) / (0.99)) + minmaxesBandwidth.second[0][0]);
            }
        }
    }
    return;
}

//function to predict bandwidth
static vector<double> predictBandwidth()
{
    int sliplines = 1;
    std::pair<std::vector<std::vector<std::valarray<double>>>, std::vector<std::vector<std::valarray<double>>>> xy_test = myNNreg.XY_test("bandwidthTest.csv", true, true, sliplines);

    std::vector<double> bandwidthPredicted;
    for (auto i : xy_test.first)
    {
        std::vector<std::valarray<double>> x = myNNreg.single_predict({i});
        for (auto i : x)
        {
            for (auto j : i)
            {
                bandwidthPredicted.push_back(abs(((j - 0.01) * (minmaxesBandwidth.second[0][1] - minmaxesBandwidth.second[0][0]) / (0.99)) + minmaxesBandwidth.second[0][0]));
            }
        }
    }
    return bandwidthPredicted;
}
// Training Model for computing capacity allocation
auto minmaxesComputing = myNNreg.fit_from_csv_reg("computing_capacity_allocated.csv", true, 10, 0.3, true, 2, 8, true);

// test function for computing capacity prediction
static void test1()
{
    double a, b, c, d;
    vector<double> topredict({694.818, 515.062, 537.822, 94.4924, 497, 122.111, 48});
    std::valarray<double> test(topredict.size());
    for (int i = 0; i < topredict.size(); i++)
    {
        test[i] = topredict[i];
    }
    for (int i = 0; i < test.size(); i++)
    {
        int min1 = minmaxesComputing.first[i][0];
        int max1 = minmaxesComputing.first[i][1];

        test[i] = (test[i] - min1) / (max1 - min1) * (0.99) + 0.01;
    }
    std::vector<std::valarray<double>> x = myNNreg.single_predict({test});

    int sliplines = 1;
    std::pair<std::vector<std::vector<std::valarray<double>>>, std::vector<std::vector<std::valarray<double>>>> xy_test = myNNreg.XY_test("bandwidthTest.csv", true, true, sliplines);

    std::vector<double> bandwidthPredicted;
    for (auto i : xy_test.first)
    {
        std::vector<std::valarray<double>> x = myNNreg.single_predict({i});
        for (auto i : x)
        {
            for (auto j : i)
            {
                bandwidthPredicted.push_back(((j - 0.01) * (minmaxesComputing.second[0][1] - minmaxesComputing.second[0][0]) / (0.99)) + minmaxesComputing.second[0][0]);
            }
        }
    }
    return;
}

//function to predict computing capacity to be allocated
static vector<double> predictComputingCapacity()
{
    int sliplines = 1;
    std::pair<std::vector<std::vector<std::valarray<double>>>, std::vector<std::vector<std::valarray<double>>>> xy_test = myNNreg.XY_test("bandwidthTest.csv", true, true, sliplines);

    std::vector<double> computingCapacityPredicted;
    for (auto i : xy_test.first)
    {
        std::vector<std::valarray<double>> x = myNNreg.single_predict({i});
        for (auto i : x)
        {
            for (auto j : i)
            {
                computingCapacityPredicted.push_back(abs(((j - 0.01) * (minmaxesComputing.second[0][1] - minmaxesComputing.second[0][0]) / (0.99)) + minmaxesComputing.second[0][0]));
            }
        }
    }
    return computingCapacityPredicted;
}

// classification Model for offloading prediction
machine_learning::neural_network::NeuralNetwork myNN =
    machine_learning::neural_network::NeuralNetwork({
        {7, "none"}, // First layer with 3 neurons and "none" as activation
        {7, "relu"},
        {4, "sigmoid"} // Third layer with 3 neurons and "sigmoid" as
                       // activation
    });

//test function for offload prediction
static void testOffload()
{
    myNN.summary();
    myNN.fit_from_csv("offloading.csv", true, 10, 0.3, true, 2, 8, true);
    int sliplines = 1;
    std::pair<std::vector<std::vector<std::valarray<double>>>, std::vector<std::vector<std::valarray<double>>>> xy_test = myNN.XY_test("offloadingTest.csv", true, true, sliplines);

    double correct = 0;
    for (int i = 0; i < xy_test.first.size(); i++)
    {
        std::vector<std::valarray<double>> xtest_pred = myNN.single_predict({xy_test.first[i]});
        std::vector<int> predicted;
        for (int i = 0; i < xtest_pred.size(); i++)
        {
            int max = 0;
            for (int j = 0; j < xtest_pred[i].size(); j++)
            {
                if (xtest_pred[i][j] > xtest_pred[i][max])
                {
                    max = j;
                }
            }
            predicted.push_back(max);
        }
        for (int j = 0; j < xy_test.first[i].size(); j++)
        {
            for (int k = 0; k < xy_test.first[i][j].size(); k++)
            {
                if (xy_test.second[i][j][k] == 1)
                {
                    if (k == predicted[j])
                    {
                        correct = correct + 1;
                    }
                    break;
                }
            }
        }
    }
    std::cout << "accuracy on test set - " << 100 * correct / xy_test.first.size() << "%" << std::endl;
    return;
}

//function to predict offloading outcome
static vector<int> predictOffload()
{
    int sliplines = 1;
    std::pair<std::vector<std::vector<std::valarray<double>>>, std::vector<std::vector<std::valarray<double>>>> xy_test = myNN.XY_test("offloadingTest.csv", true, true, sliplines);
    std::vector<int> predicted;
    for (int i = 0; i < xy_test.first.size(); i++)
    {
        std::vector<std::valarray<double>> xtest_pred = myNN.single_predict({xy_test.first[i]});

        for (int i = 0; i < xtest_pred.size(); i++)
        {
            int max = 0;
            for (int j = 0; j < xtest_pred[i].size(); j++)
            {
                if (xtest_pred[i][j] > xtest_pred[i][max])
                {
                    max = j;
                }
            }
            predicted.push_back(max);
        }
    }
    return predicted;
}

//function to process incoming packets on MECO
void VeinsInetAppForMeco::processPacket(std::shared_ptr<inet::Packet> pk)
{
    auto l3Addresses = pk->getTag<L3AddressInd>();
    srcAddresses =  l3Addresses->getSrcAddress();

    if(strcmp(pk->getName(),"TaskAssignmentByRSU")==0)
    {
    auto payload = makeShared<CollectRequests>();
    timestampPayload(payload);
    payload->setChunkLength(B(100));
    payload->setMecoID(1);
    payload->setNumReqs(3);
    EV_INFO << "**************************************" <<  endl;
    EV_INFO << "**************************************" <<  endl;
    EV_INFO << "After receiving Send packet: VehicleTaskAckByMeco" << payload << endl;
    EV_INFO << "**************************************" <<  endl;
    EV_INFO << "**************************************" <<  endl;
    auto packet = createPacket("VehicleTaskAckByMeco");

    packet->insertAtBack(payload);
    sendPacketToRSU(std::move(packet));
    }
    if(strcmp(pk->getName(),"TaskAssignmentByRSU")==0)
        {
            int x, y;
            x = (pk->peekData<TaskAssignmentByRSU>())->getX();
            y = (pk->peekData<TaskAssignmentByRSU>())->getY();
            int MIPS;
            int taskSize;
            int delayTol;
            int vehicleID;
            int index = (pk->peekData<TaskAssignmentByRSU>())->getRsuID();;

            string filename = (pk->peekData<TaskAssignmentByRSU>())->getFilename();
            fileNum++;
            string line;
            std::vector<int> packetv;
            std::vector<std::vector<int>> packets;

            ifstream myfile(filename);
            if(myfile.is_open())
            {
                while(std::getline(myfile,line))
                {
                    if (!line.empty())
                    {
                        std::stringstream in( line );
                        std::copy( std::istream_iterator<int, char>(in), std::istream_iterator<int, char>(), back_inserter( packetv ) );
                        packets.push_back(packetv);
                        packetv.clear();
                    }
                }
            }
            myfile.close();

            fout.open("prediction.csv", ios::out | ios::app);
            float v_left, rsu1_l, rsu2_l, rsu3_l;
            fout << "input_size,workload,delay_tolerance,v_left,rsu1_left,rsu2_left,rsu3_left,offload\n";

            foutb.open("b_prediction.csv", ios::out | ios::app);
            foutb << "input_size,workload,delay_tolerance,v_left,rsu1_left,rsu2_left,rsu3_left,bandwidth\n";

            foutc.open("c_prediction.csv", ios::out | ios::app);
            foutc << "input_size,workload,delay_tolerance,v_left,rsu1_left,rsu2_left,rsu3_left,computingcap\n";

            for(int i=0; i<packets.size(); i++)
            {
                v_left = 1 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (125 - 1)));
                rsu1_l = 200 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (500 - 200)));
                rsu2_l = 1 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (600 - 200)));
                rsu3_l = 1 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (700 - 200)));

                fout << packets[i][1] << "," << packets[i][0] << "," << packets[i][2] << "," << v_left << "," << rsu1_l << "," << rsu2_l << "," << rsu3_l << "," << 0 << endl;
                foutb << packets[i][1] << "," << packets[i][0] << "," << packets[i][2] << "," << v_left << "," << rsu1_l << "," << rsu2_l << "," << rsu3_l << "," << 0 << endl;
                foutc << packets[i][1] << "," << packets[i][0] << "," << packets[i][2] << "," << v_left << "," << rsu1_l << "," << rsu2_l << "," << rsu3_l << "," << 0 << endl;
            }
            fout.close();
            foutb.close();
            foutc.close();

            vector<int> p;
            vector<double>q, r;

             if(fileNum == 1)
             {
                callForPSO();
                test();
                test1();
                testOffload();
             }

             simtime_t start = simTime();

             p = predictOffload();
             q = predictBandwidth();
             r = predictComputingCapacity();

             simtime_t end = simTime();
             double Tsys = (end - start).dbl();
             int x1, y1;

             unordered_map<int, int>mpx, mpy;
             mpx[0] = 2100; mpy[0] = 1600;
             mpx[1] = 2000; mpy[1] = 1200;
             mpx[2] = 1900; mpy[2] = 1000;

             double dis = sqrt(pow(x - mpx[index], 2)* 1.0 +
                             pow(y - mpy[index], 2) * 1.0);

            for(int i=0; i<packets.size(); i++)
            {
                int Edgeid = 0;
                if(p.size()!=0) Edgeid = p[i];
                e1++;

                qos += qualityOfService(packets[i][1], packets[i][0], packets[i][2], p[i], q[i], r[i], Tsys, dis);

                auto payload = makeShared<CollectRequests>();
                int RSUid = (pk->peekData<TaskAssignmentByRSU>())->getRsuID();
                timestampPayload(payload);
                payload->setChunkLength(B(100));
                payload->setMecoID(1);
                payload->setNumReqs(3);
                payload->setRsuID(RSUid);
                payload->setRq_MIPS(packets[i][0]);
                payload->setTaskSize(packets[i][1]);
                payload->setDelayTol(packets[i][2]);
                payload->setVehicleID(packets[i][5]);
                payload->setIndex(packets[i][6]);
                if(i<q.size())
                    payload->setBw(q[i]);
                if(i<r.size())
                    payload->setCap(r[i]);
                payload->setTsys(Tsys);
                EV_INFO << "**************************************" <<  endl;
                EV_INFO << "**************************************" <<  endl;
                EV_INFO << "After receiving Send packet: CollectRequests" << payload << endl;
                EV_INFO << "**************************************" <<  endl;
                EV_INFO << "**************************************" <<  endl;
                auto packet = createPacket("CollectRequests");

                packet->insertAtBack(payload);
                if(Edgeid == 0)
                    sendPacketToRSU(std::move(packet));
                else
                sendPacketToEdge(std::move(packet), Edgeid);
            }
        }
}
