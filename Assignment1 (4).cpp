
/*
 Program Title	    : Fermat’s Last Theorem
 File Name	    : Assignment1.cpp
 External File	    : N/A
 Created Ext File   : N/A
 Programmers Name   :Yashwanth Reddy Arravapula
 Email Address	    :yashwanthreddyarra@lewis.edu
 CourseNumber	    :60550
 Section Number     :001
 Submission Date    :07/31/2022
 Program Definition : To find the smallest possible miss using Fermat’s Last Theorem.
 References         : https://www.geeksforgeeks.org/fermats-last-theorem/,
 https://leetcode.com/problems/super-pow/discuss/84487/c-9ms-solution-improved-by-fermats-little-theorem
*/

// Include header file
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <math.h>
class Settlement
{
public:
    // returns a value of standard input in c++
    template <typename T>
    static T input()
    {
        T value;
        std::cin >> value;
        return value;
    }
};
class Main
{
public:
    static int k;
    static int n; //  equation variables
    static float smallestRelativeMiss;
    // smallest relative miss
    static long smallestMiss;
    // smallest actual miss
    static float s_Miss;

    // main method to start the program
    static void main(std::vector<std::string> &args)
    {
        // main method

        Main::GetInput();
        Main::TestValues();

        std::cout << "\nSmall Miss: " + std::to_string(s_Miss) << std::endl;
    }

    // receive input from the keyboard for k & n
    static void GetInput()
    {

        do
        {
            std::cout << "\nThe value k must be greater than 10" << std::endl;
            std::cout << "Enter the value of k for the equation:" << std::endl;
            // tell the user to input a value for k
            Main::k = Settlement::input<int>();
        } while (!Main::IsValid(Main::k, 11, 99));

        do
        {
            std::cout << "\nThe value n must be 2< n <12." << std::endl;
            std::cout << "Enter the  n value:" << std::endl;
            Main::n = Settlement::input<int>();
        } while (!Main::IsValid(Main::n, 3, 11));
    }

    // validating the input values for the received value, min and max
    static bool IsValid(int value, int min, int max)
    {

        if (value < min || value > max)
        {
            //  user input was not valid
            std::cout << "Value must be greater than " + std::to_string((min - 1)) + " and less than " + std::to_string((max + 1)) + "\n"
                      << std::endl;
            return false;
        }
        return true;
    }

    // testing the received values for findinga actual miss
    static void TestValues()
    {
        // test the different x y z combinations
        for (int x = 10; x <= Main::k; x++)
        {
            // loop through all x value
            for (int y = x; y <= Main::k; y++)
            {
                // loop through y values greater than x
                float C = std::numeric_limits<float>::max();
                // relative "closeness" of x^n + y^n and z^n
                int z = (x + y) / 2;
                if (z > Main::k)
                {
                    z = Main::k;
                    Main::PrintResults(x, y, z, Main::RelativeMiss(x, y, z));
                    continue;
                }
                // initiate z at a value near x and y
                while (z <= Main::k)
                {
                    // increase z until the closest value is found
                    float near = Main::RelativeMiss(x, y, z);
                    // get the "closeness" of x y z
                    if (near > C)
                    {
                        break;
                    }
                    C = near;
                    // closeness is increasing, continue loop
                    z++;
                }
                z--;
                Main::PrintResults(x, y, z, C);
                if (x != y)
                {
                    Main::PrintResults(y, x, z, C);
                }
            }
        }
    }
	
    // display the result for actual miss x, y, and z
    static void PrintResults(int x, int y, int z, float C)
    {
        // Print the results
        float relMiss = C;
        // abs value of distance from 1
        if (Main::smallestRelativeMiss > relMiss)
        {
            //  new smallest rel miss
            Main::smallestRelativeMiss = relMiss;
            std::cout << "\n New Close miss." << std::endl;
            std::cout << "x: " + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z) << std::endl;
            std::cout << "Relative Miss: " + std::to_string((1 + C)) << std::endl;

            float Relat_miss = (1 + C);
            if (Relat_miss < s_Miss)
            {
                s_Miss = Relat_miss;
            }
            std::cout << "Actual Miss: " + std::to_string(Main::ActualMiss(x, y, z)) << std::endl;
        }
    }

    // finding relative miss
    static float RelativeMiss(int x, int y, int z)
    {
        // relative miss
        double zValue = pow(z, Main::n);
        double xyValues = pow(x, Main::n) + pow(y, Main::n);
        return (float)abs(1.0 - xyValues / zValue);
    }

    // finding the actual miss for the received x, y and z
    static long ActualMiss(int x, int y, int z)
    {
        //  actual miss
        double zValue = pow(z, Main::n);
        double xyValues = pow(x, Main::n) + pow(y, Main::n);
        return (long)(xyValues - zValue);
    }
};

int Main::k = 0;
int Main::n = 0;
float Main::s_Miss = std::numeric_limits<float>::max();
float Main::smallestRelativeMiss = std::numeric_limits<float>::max();
long Main::smallestMiss = std::numeric_limits<long>::max();

//Main method to start the program
int main(int argc, char **argv)
{
    std::vector<std::string> parameter(argv + 1, argv + argc);
    Main::main(parameter);
    return 0;
};
