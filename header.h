//DO NOT MODIFY THIS FILE

//the comments before each prototype describe the indicated parameters. Some may
//be input params, some may be output params.

/*! 
 * @brief The maximum degree in a polynomial equation.
 */
const int MAX_DEGREE = 10;

/*! 
 * @brief The maximum number of intervals in a range for integration.
 */
const int MAX_INTERVAL = 10000;

//x[] - the computed x-values in the intervals (the middle points of the intervals for this program)
//numOfInterval - the number of intervals entered by the user
//intervalWidth - the computed width of every interval
void get_x_intervals ( double x[], int & numOfInterval, double & intervalWidth);

//coeff[] - the coefficients of a polynomial equation entered by the user
//degree - the degree of the polynomial equation entered by the user
void get_polynomial_coefficients(double coeff[], int &degree);

//coeff[] - the coefficients of the polynomial equation
//degree - the degree of the polynomial equation
//x[] - the selected x-values in the intervals (the middle points of the intervals for this program)
//numOfInterval - the number of intervals
//y[] - the computed values of the polynomial equation at the selected x-values in the intervals
void compute_polynomial(const double coeff[], int degree, const double x[], double y[], int numOfIntervals);


//f[] - the values of the first polynomial equation in the intervals
//g[] - the values of the second polynomial equation in the intervals
//numOfInterval - the number of intervals
//width - the width of every interval

//returns the area between two polynomial curves
double integrate (const double f[],const double g[], int numOfInterval, double width);

