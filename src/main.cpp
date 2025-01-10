/**
 * @file main.cpp
 * @brief Main file to test the FIR and IIR filter implementations.
 *
 * This program demonstrates the usage of FIR and IIR filter classes,
 * including their constructors, methods, and exception handling.
 */

#include "FIR.hpp"
#include "IIR.hpp"
#include "filter.hpp"

using std::cout;
using std::endl;

/**
 * @brief The entry point of the program.
 *
 * This function performs the following operations:
 * - Tests the functionality of the FIR filter:
 *   - Constructor usage.
 *   - Getter methods for coefficients.
 *   - Signal filtering using FIR filter.
 * - Tests the functionality of the IIR filter:
 *   - Constructor usage.
 *   - Getter and setter methods for coefficients and parameters.
 *   - Signal filtering using IIR filter.
 *   - Stability analysis of the IIR filter.
 * - Demonstrates exception handling for invalid inputs.
 *
 * @return int Returns 0 on successful execution.
 */
int main()
{
    try
    { 
        cout << "--- FIR filter test ---" << endl;

        /**
         * @brief Testing the FIR filter with default coefficients.
         */
        mj::FIR<double> fir_test1({1.5, 2.0, 3.5});
        cout << "Test Getter x: " << fir_test1.getX() << endl;
        cout << "Test Getter h: " << fir_test1.getH() << endl;
        cout << "Test FIR filtration - first constructor: " << fir_test1.OutSignal() << endl;

        /**
         * @brief Testing the FIR filter with custom coefficients.
         */
        mj::FIR<int> fir_test2({1, 2, 3}, {3, 2, 1});
        cout << "Test FIR filtration - second constructor: " << fir_test2.OutSignal() << endl;
        fir_test2.setX({2, 1, 3, 7});
        fir_test2.setH({7, 3, 1, 2});
        cout << "Test FIR filtration - setters: " << fir_test2.OutSignal() << endl;

        cout << "Test exception: " << endl;
        /**
         * @brief Demonstrating exception handling for invalid input.
         * Uncomment the following line to test:
         * fir_test2.setX({});
         */

        cout << "--- IIR filter test ---" << endl;

        /**
         * @brief Testing the IIR filter with default coefficients.
         * 
         * In the first setter L was set to a very small value, which will be confirmed by a message.
         * 
         * In this test the filter will be stable.
         */
        mj::IIR<double> iir_test1;
        cout << "Test IIR filtration - first constructor: " << iir_test1.OutSignal({1.5, 2.0, -1.0}) << endl;

        iir_test1.SetB({0.5, 1, 0, -0.5});
        iir_test1.SetA({2.0, -1, 1});
        iir_test1.SetL(2);
        cout << "Test IIR filtration - setters: " << iir_test1.OutSignal({1, 0, 1}) << endl;

        iir_test1.SetL(5);
        cout << "Test filter stability: " << iir_test1.stability() << endl;
        cout << "Test Getter B: " << iir_test1.getB() << endl;
        cout << "Test Getter A: " << iir_test1.getA() << endl;
        cout << "Test Getter L: " << iir_test1.getL() << endl;

        /**
         * @brief Testing the IIR filter with custom coefficients.
         * 
         * In this test the filter will be found to be unstable which will be confirmed by a warning. 
         */
        mj::IIR<int> iir_test2({2, 0, -1, 1}, {1, 1, 2});
        cout << "Test IIR filtration - second constructor: " << iir_test2.OutSignal({1, 0, -1}) << endl;
        cout << "Test filter stability: " << iir_test2.stability() << endl;

        cout << "Test exceptions: " << endl;
        /**
         * @brief Demonstrating exception handling for invalid coefficients.
         * Uncomment the following lines to test:
         * mj::IIR<int> iir_test3({1, 1}, {0, 1});
         * iir_test2.SetA({});
         * iir_test1.SetL(-1);
         */
    }
    catch (const std::exception& e) 
    {
        /**
         * @brief Catch and display any exceptions thrown during the tests.
         */
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
