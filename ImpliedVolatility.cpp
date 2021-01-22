/* Program to calculate the implied volatility of european call option of a stock for different 
maturites and strike price
 */
#include <iostream>
#include <cmath>
#include "BlackScholes.h"
#include <iomanip>
#include <array>
#include <string>
using namespace std;
double BlackScholes::spot_price = 50.5000;   //current stock price
double BlackScholes::int_rate = 0.0300; //risk-free interest rate
double maturity = 0.5000; //in years
double strike_price = BlackScholes::spot_price + 5;  //initial strike price is taken as spot_price + 5
double BlackScholes::hist_vol = 0.3000;           //historical volatility 30%
double BlackScholes::option_market_price = 3.000; //current option price in the market 
int main()
{
    BlackScholes obj1(strike_price, maturity);
    BlackScholes obj2(strike_price, maturity);
    cout << fixed << setprecision(4);
    array<double, 10> implied_vola_maturity = obj1.inverse_volatility_maturity(); //store the implied volatitlity v/s maturity values
    array<double, 10> implied_vola_strike = obj2.inverse_volatility_strike();     //store the implied volatility v/s strike price
    string draw_graph = "python3 Implied_volatility.py";                          //python file name
    for (int i = 0; i < implied_vola_maturity.size(); i++)
    {
        draw_graph.append(" " + to_string(implied_vola_maturity.at(i)));
    }
    for (int i = 0; i < implied_vola_strike.size(); i++)
    {
        draw_graph.append(" " + to_string(implied_vola_strike.at(i)));
    }
    system(draw_graph.c_str()); //call python script to draw the implied volatility curves
    return 0;
}