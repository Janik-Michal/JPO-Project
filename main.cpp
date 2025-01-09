#include "FIR.hpp"
#include "IIR.hpp"
#include "filter.hpp"

using std::cout;
using std::endl;

int main()
{
    try
    { 
    cout << "--- FIR filter test ---" << endl;

    mj::FIR<double> fir_test1({1.5,2.0,3.5});
    cout << "Test Getter x: " << fir_test1.getX() << endl;
    cout << "Test Getter h: " <<fir_test1.getH() << endl;
    cout << "Test FIR filtration - first constructor: " << fir_test1.OutSignal() << endl;

    mj::FIR<int> fir_test2({1,2,3},{3,2,1});
    cout << "Test FIR filtration - second constructor: " << fir_test2.OutSignal() << endl;
    fir_test2.setX({2,1,3,7});
    fir_test2.setH({7,3,1,2});
    cout << "Test FIR filtration - setters: " << fir_test2.OutSignal() << endl;

    cout << "Test exception: " << endl;
    //fir_test2.setX({});

    cout << "--- IIR filter test ---" << endl;

    mj::IIR<double> iir_test1;
    cout << "Test IIR filtration - first constructor: " << iir_test1.OutSignal({1.5,2.0,-1.0}) << endl;
    iir_test1.SetB({0.5,1,0,-0.5});
    iir_test1.SetA({2.0,-1,1});
    iir_test1.SetL(2);
    cout << "Test IIR filtration - setters: " << iir_test1.OutSignal({1,0,1}) << endl;
    iir_test1.SetL(5);
    cout << "Test filter stability: " << iir_test1.stability() << endl;
    cout << "Test Getter B: " << iir_test1.getB() << endl;
    cout << "Test Getter A: " <<iir_test1.getA() << endl;
    cout << "Test Getter L: " <<iir_test1.getL() << endl;

    mj::IIR<int> iir_test2({2,0,-1,1},{1,1,2});
    cout << "Test IIR filtration - second constructor: " << iir_test2.OutSignal({1,0,-1}) << endl;
    cout << "Test filter stability: " << iir_test2.stability() << endl;

    cout << "Test exceptions: " << endl;
    //mj::IIR<int> iir_test3({1,1},{0,1});
    //iir_test2.SetA({});
    //iir_test1.SetL(-1);
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
}