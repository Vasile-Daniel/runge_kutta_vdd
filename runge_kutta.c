// Author: Vasile-Daniel DAN
// Today: 2024 05 19 
// Project Runge Kutta Method apply to an RC circuit 

#include <stdio.h>

// Function to define the differential equation (dy/dx)
double f(double x, double y) {
    // For electrical circuits, let's use the equation for charging a capacitor
    double R = 100; // Resistance (in ohms)
    double C = 0.001; // Capacitance (in farads)
    double Vin = 5; // Input voltage (in volts)
    
    double dVc_dt = (Vin - y) / (R * C); // Equation for charging a capacitor
    return dVc_dt;
}

// Runge-Kutta 4th order method
double rungeKutta(double x0, double y0, double x, double h) {
    // Count number of iterations using step size or
    // step height h
    int n = (int)((x - x0) / h);

    double k1, k2, k3, k4;

    double y = y0;
    for (int i = 1; i <= n; i++) {
        // Apply Runge Kutta Formulas to find next value of y
        k1 = h * f(x0, y);
        k2 = h * f(x0 + 0.5 * h, y + 0.5 * k1);
        k3 = h * f(x0 + 0.5 * h, y + 0.5 * k2);
        k4 = h * f(x0 + h, y + k3);

        // Update next value of y
        y = y + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);

        // Update next value of x
        x0 = x0 + h;
    }

    return y;
}

int main() {
    double x0 = 0, y0 = 0; // Initial conditions
    double x = 10; // Final time
    double h = 0.1; // Step size

    // Find approximation of y at x
    double y = rungeKutta(x0, y0, x, h);
    
    printf("Voltage across the capacitor at time %f seconds: %f volts\n", x, y);
    
    return 0;
}
