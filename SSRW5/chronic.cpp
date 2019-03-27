#include <random>
#include <array>
#include <iostream>
#include <iomanip>
#include <thread>
#include <algorithm>
#include <mutex>
#include <chrono>

//class to produce random numbers from a poisson distribution
class poisson_generator
{
    public:
        poisson_generator( int seed, double mean)
            :engine{ seed }, poisson{ mean } {}

        int operator()()
        { return sample(); }

        int sample()
        { return poisson(engine) ; }

    private:
        std::default_random_engine engine;
        std::poisson_distribution<int> poisson;

};


//class to store random numbers
template < class Container>
class histogram
{
    public:
        histogram()
            :fData{} {}

        void fill( int val )
        {
            std::lock_guard<std::mutex> guard(fMutex);
            ++fData[val];
        }

        typename Container::iterator begin()
        { return fData.begin(); }

        typename Container::iterator end()
        { return fData.end(); }

        typename Container::value_type at(typename Container::size_type pos)
        {
            std::lock_guard<std::mutex> guard(fMutex);
            return fData.at(pos);
        }


   private:
        Container fData;
        std::mutex fMutex;
};

//Function to gnenerate events
    template <class Generator, class Storage>
void generate_events( Generator& g , Storage& store, int nEvents )

{
    std::cout << "Generating " + std::to_string(nEvents) + " events.\n";
    while ( nEvents-- )
    {
        store.fill( g() );
    }
}


//Printer for the histogram
    template <class H>
void printHistogram( H& h, unsigned int min, unsigned int max, int peak = 30 )
{

    auto total = std::accumulate( begin(h), end(h), 0 );
    std::cout << "There were " << total << " events" << '\n' ;

    auto dmax = *std::max_element( begin(h), end(h) );
    auto denom = (dmax > peak  ? dmax : peak ) / peak;

    auto length = end(h) - begin(h);

    for ( unsigned int i = min ; i != max ; ++ i)
    {
        std::cout << std::setw(4) << i << ' '
            << (i > length ? 0 : std::string( h.at(i) / denom, '*' ) ) << '\n';
    }
}

int main( int argc, char * argv[] )
{
    //Set up
    histogram<std::array<int, 100> > h;
    int sample_size = 1000000;
    std::random_device rd;

    //Create threads
    std::vector<std::thread> threads;
    auto nThreads = 8; //default

    //Read number of threads from command line
    if (argc == 2 )
    {nThreads = std::stoi(argv[1]) ; }

      auto start = std::chrono::steady_clock::now();

for( int t = 0 ; t != nThreads ; ++t )
{
    //Divide sample size between nThreads
    int sample_t = sample_size / nThreads;

    if ( t == nThreads - 1 )
    {
        sample_t = sample_size - ( nThreads - 1 ) * sample_t ;
    }

    //Generate random events
    threads.push_back(std::thread( [&h, t, sample_t, &rd] ()
                {
                poisson_generator pg ( rd(), 10 );
                generate_events( pg, h, sample_t);
                }
                ) );
}

for (auto& thread : threads )
{ thread.join() ; }

 //Timing print out
    auto finish = std::chrono::steady_clock::now();
    auto time_period = finish - start;
    std::cout << "Processing took " <<
        std::chrono::duration<double, std::milli>(time_period).count()  << " ms .\n" ;

    //Histogram print out
    printHistogram( h, 0, 25);

    return 0;
}