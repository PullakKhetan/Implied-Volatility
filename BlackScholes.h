#include <iostream>
#include <cmath>
#include <array>
using namespace std;
#define _USE_MATH_DEFINES_
#define epsilon 0.0001 //tolerance value for approximation using Newton-raphson method

class BlackScholes
{
public:
    static double spot_price;
    static double int_rate;
    double maturity = 0.0; //in years
    double strike_price = 0.0;
    static double hist_vol; //historical volatility
    static double option_market_price;
    double vol = hist_vol;
    BlackScholes();
    BlackScholes(double a, double b) : strike_price(a), maturity(b) {}
    double calc_price() //calcute the option price using Black-Schole method
    {
        double d1 = (log(spot_price / strike_price) + (int_rate + (pow(vol, 2) / 2) * maturity)) / (vol * sqrt(maturity));
        double d2 = d1 - (vol * sqrt(maturity));
        double price = spot_price * (erfc(-d1 / sqrt(2)) / 2) - strike_price * (erfc(-d2 / sqrt(2)) / 2) * exp(-int_rate * maturity); //erfc is complementary error function used for calculating standard normal cumulative density function
        return price;
    }
    double vega() //calculate the greek vega of the european call option
    {
        double d1 = (log(spot_price / strike_price) + (int_rate + (pow(vol, 2) / 2) * maturity)) / (vol * sqrt(maturity));
        double d2 = d1 - (hist_vol * sqrt(maturity));
        return spot_price * sqrt(maturity) * (1 / (pow(M_PI * 2, 0.5))) * exp(-0.5 * d1 * d1);
    }

    array<double, 10> inverse_volatility_maturity();
    array<double, 10> inverse_volatility_strike();

    ~BlackScholes();
};
array<double, 10> BlackScholes::inverse_volatility_maturity() //calculate the implied volatility values for different maturities using newton-raphson mathod
{
    array<double, 10> impl_vol_mat;
    for (int i = 0; i < 10; i++)
    {

        double init_price = calc_price();
        double init_vol = hist_vol;
        while (fabs(option_market_price - init_price) > epsilon)
        {

            init_vol += (option_market_price - init_price) / vega();
            vol = init_vol;
            init_price = calc_price();
        }
        impl_vol_mat[i] = vol;
        maturity += 0.1;
    }

    return impl_vol_mat;
}
array<double, 10> BlackScholes::inverse_volatility_strike() //calculate the implied volatility values for different strike price using newton-raphson mathod
{
    array<double, 10> impl_vol_strike;
    for (int i = 0; i < 10; i++)
    {

        double init_price = calc_price();
        double init_vol = hist_vol;
        while (fabs(option_market_price - init_price) > epsilon)
        {

            init_vol += (option_market_price - init_price) / vega();
            vol = init_vol;
            init_price = calc_price();
        }
        impl_vol_strike[i] = vol;
        strike_price += 1;
    }

    return impl_vol_strike;
}

BlackScholes::BlackScholes(/* args */)
{
}

BlackScholes::~BlackScholes()
{
}
