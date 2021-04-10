// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double power(double left, double right)
{
    double pow(1);
    for(int i = 0; i < right; ++i)
    {
        pow *= left;
    }

    return pow;
}
