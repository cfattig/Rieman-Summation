/*************************************************************************//**
 * @file 
 * @brief claculates riemann sums between curves
 *
 * @mainpage Program 2 - rieman sums
 * 
 * @section course_section Course Information 
 *
 * @author Christian Fattig
 * 
 * @date April 1, 2015
 * 
 * @par Professor: 
 *         Dr. Qiao
 * 
 * @par Course: 
 *         CSC 150 - Section -  2:00 pm
 * 
 * @par Location: 
 *         McLaury - Room 205
 *
 * @section program_section Program Information 
 * 
 * @details This program will find an approximated area between two polynomial
 * equations. The user enters an upper and lower limit as well as
 * the number of intervals which are used to calculate the width of the intervals
 * and will determine what the x values are that are stored into an array.
 * It then uses two seperate arrays to store user entered coefficient values.
 * A function is then called that uses these arrays to determine the y values which
 * are also stored into an array. 
 *
 * Once all the information has been obtained, the program calls a function that finds
 * the area of the individual intervals of the equations and takes the difference of 
 * them. From this point, the intervals are summed together which gives the area and is 
 * returned to the main function.
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      None
 * 
 * @par Usage: 
   @verbatim  
   c:\> prog2.exe 
   d:\> c:\bin\prog2.exe 
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug None
 * 
 * @todo None
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   Mar 25, 2015  Started basic outline,
				 cout, function calls, ect.
   Mar 26, 2015  Implimented math algorithms
				 and loops that filled arrays,
				 gave error messages, and 
				 calculated area.
   Mar 28, 2015  Fixed minor mistakes and added
				 white space.
   Mar 31, 2015  Added documentation.
   @endverbatim
 *
 *****************************************************************************/


#include "header.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <math.h>
using namespace std;


int main()
{
	char choice = ' '; // used to re-run or end the program

	cout<< "This program computes the area of between curves." << endl;

	do // loop used to re-run the program
	{

		int numOfInterval = 0; 
		// is the number of intervals used
		double intervalWidth = 0.0; 
		// the calculated width of each interval
		int fdegree = 0; 
		// equation F's highest polynomial degree
		int gdegree = 0; 
		// equation G's highest polynomial degree
		double x[MAX_INTERVAL] = {0.0};
		// where the computed midpoints of each interval are stored
		double f[MAX_DEGREE + 1] = {0.0};
		// where F's polynomial coefficients are stored
		double g[MAX_DEGREE + 1] = {0.0}; 
		// where G's polynomial coefficients are stored
		double fy[MAX_INTERVAL] = {0.0}; 
		// where F's computed interval heights are stored
		double gy[MAX_INTERVAL] = {0.0};
		// where G's computed interval heights are stored
		double total_Area = 0.0; 
		// the outputed total area between two equations


		cout<< setprecision(4) << fixed << showpoint;
	
		get_x_intervals( x, numOfInterval, intervalWidth); 
		// used to get information and to calculate midpoints

		cout<< endl << "First polynomial equation" << endl << endl;

		get_polynomial_coefficients( f, fdegree);

		cout<< endl << "Second polynomial equation" << endl << endl;

		get_polynomial_coefficients( g, gdegree);

		compute_polynomial(f, fdegree, x, fy, numOfInterval); // used to find F's interval heights

		compute_polynomial(g, gdegree, x, gy, numOfInterval); // used to find G's interval heights

		total_Area = integrate(fy, gy, numOfInterval, intervalWidth); 

		cout<< endl << "The area is: " << total_Area << " " << endl << endl;
		cout<< "Do another? [Y/N]: "; // used to re-run or terminate function
		cin>> choice;
		cout<< endl;
		choice = toupper(choice);

	}while(choice == 'Y');

	return 0;
}


/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function recieves an upper and a lower limit as well as the number of 
 * intervals to calculates the interval width. It also computes the midpoints
 * of each interval and stores it into x[].
 *
 * @param[in] x - Array that stores the computed midpoints of each interval.
 * @param[in] numOfInterval - The number of intervals.
 ******************************************************************************/
void get_x_intervals ( double x[], int & numOfInterval, double & intervalWidth)
{
	double a = 0.0; // lower limit
	double b = 0.0; // upper limit

	do // used for error checking
	{
		cout<< endl << "Enter lower limit (a): ";
		cin>> a;
		cout<< endl << "Enter upper limit (b): ";
		cin>> b;
		if(b <= a)
			cout<< "Invalid input, b must be greater than a." << endl;
	}while(b <=a );

	do // used for error checking
	{
		cout<< endl << "Enter the number of intervals (n): ";
		cin>> numOfInterval;
		if(numOfInterval < 1 || numOfInterval > 10000)
			cout<< "Invalid input, n must be between 1 and 10000." << endl;
	}while(numOfInterval < 1 || numOfInterval > 10000);

	intervalWidth = (b - a) / numOfInterval; // calculates intervalwidth

	for(int i=0; i < numOfInterval; i++)
	{
		x[i] = a + ((b - a) / (2 * numOfInterval)) + (i) * intervalWidth;  
		// calculates interval midpoints
	}

}


/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function recieves an array and fills it with user entered coefficient
 * values.
 *
 * @param[in] coeff - An array where the coefficients are stored.
 * @param[in] degree - Tells what the highest degree the polynomial has is.
 ******************************************************************************/
void get_polynomial_coefficients(double coeff[], int &degree)
{
	cout<< "Enter the degree of the polynomial equation: ";

	do // used for error checking
	{
		cin>> degree;
		if(degree < 0 || degree > 10) 
		{
			cout<< "Invalid input, the degree must be between 0 and 10." << endl;
			cout<< "Please re-enter the degree: ";
		}
	}while(degree < 0 || degree > 10);

	cout << endl << "Enter coefficients for the equation."<< endl;

	for(int i=degree; i>0; i--) // used to store coefficient values
	{
		cout<< "Enter the coefficients for x^"<< i << ": ";
		cin>> coeff[i];
		cout<< endl;
	}

	cout<< "Enter the constant term: ";
	cin>> coeff[0];
	// this part is seperate so that it won't say x^0
}


/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description: 
 * This function finds the interval heights of each x array
 * index by inserting the found midpoints into a computed polynomial. The
 * resulting answers are then stored in corresponding indexes in the y array.
 *
 * @param[in] coeff - The array where the coefficients are stored.
 * @param[in] degree - Tells what the highest degree the polynomial has is.
 * @param[in] x - Array that stores the computed midpoints of each interval.
 * @param[in] y - Array that stores the computed interval heights of each interval.
 * @param[in] numOfIntervals - The number of intervals.
 ******************************************************************************/
void compute_polynomial(const double coeff[], int degree, const double x[], double y[], int numOfIntervals)
{
	double sum = 0.0;

	for (int j = 0; j<numOfIntervals; j++) // fills y[]
	{
		sum = 0.0; // used to reset sum
		
		for (int i = 1; i<=degree; i++) // inputs 1 x[] value to find 1 y[] value
		{
			sum = sum + coeff[i] * pow( x[j], i);  
		}
		y[j]=sum+coeff[0];
	}

}


/***************************************************************************//**
 * @author Christian Fattig
 *
 * @par Description:
 * This function uses the interval height and width values to calculate area of
 * each interval for both equations. From there the difference is taken from the
 * resulting interval areas. These results will then be summed together which
 * then returns the overall area.
 *
 * @param[in] f - Array that has stored interval height values for the 
 * first equation.
 * @param[in] g - Array that has stored interval height values for the
 * second equation.
 * @param[in] numOfInterval - The number of intervals.
 * @param[in] width - The calculated width of the intervals
 *
 * @returns total_Area - The approximated are between the two equations.
 ******************************************************************************/
double integrate (const double f[],const double g[], int numOfInterval, double width)
{
	double total_Area = 0.0; // used to output area

	for(int i=0; i<numOfInterval; i++) // calculates area
		{
		  total_Area = total_Area + fabs(f[i] - g[i]) * width;
		  
		}

	
	return total_Area;
}