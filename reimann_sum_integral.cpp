#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

enum Method {left, mid, right};
double equation(double x);
double reimann_sum(function<double(double)> eq, double lower_limit, double upper_limit, Method method = mid, size_t rectangles = 10000);

int main() {
    const double lower_limit = 0.0;
    const double upper_limit = acos(-1.0)/2; //Pi/2
    double result = 0.0;
    double resultL = 0.0;
    double resultR = 0.0;
    result = reimann_sum(equation, lower_limit, upper_limit);
    cout << "I(low,up) = " << result << endl << endl;

    result = reimann_sum(equation, upper_limit, lower_limit);
    cout << "I(up,low) = " << result << endl << endl;

    result = reimann_sum(equation, lower_limit, upper_limit, Method::left);
    cout << "I(low,up,left) = " << result << endl << endl;
    resultL = result;

    result = reimann_sum(equation, lower_limit, upper_limit, Method::mid);
    cout << "I(low,up,mid) = " << result << endl << endl;

    result = reimann_sum(equation, lower_limit, upper_limit, Method::right);
    cout << "I(low,up,right) = " << result << endl << endl;
    resultR = result;

    result = (resultL + resultR) / 2;
    cout << "[I(left) + I(right)]/2 = " << result << endl << endl;
    return 0;
}

double equation(double x){
    return cos(x);
}

double reimann_sum(function<double(double)> eq, double lower_limit, double upper_limit, Method method, size_t rectangles){
    const double interval = abs(upper_limit - lower_limit)/rectangles;
    if (interval == 0){
        return 0;
    }
    double start = ((lower_limit < upper_limit)?lower_limit:upper_limit);
    double sum = 0;
    switch (method) {
        case Method::mid:
            start += interval/2;
            break;
        case Method::right:
            start += interval;
            break;
        default:
            break;
    }
    for (size_t i = 0; i < rectangles; i++){
        sum += interval*eq(start + i * interval);
    }
    if (upper_limit < lower_limit){
        return -sum;
    }
    return sum;
}