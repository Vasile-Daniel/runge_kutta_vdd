#include <stdio.h>
#include <math.h>

#define VIN 5.0   // Input voltage (in volts)
#define R   10  // Resistance (in ohms)
#define C   0.01 // Capacitance (in farads)
#define T   10.0  // Total time (in seconds)
#define DT  0.0001  // Time step (in seconds)

// Function to define the differential equation (dy/dt) for charging a capacitor
double f(double t, double v_c) {
    return (VIN - v_c) / (R * C);
}

// Runge-Kutta 4th order method
double rungeKutta(double t0, double v_c0, double t, double h) {
    int n = (int)((t - t0) / h);

    double k1, k2, k3, k4;
    double v_c = v_c0;

    for (int i = 0; i < n; i++) {
        k1 = h * f(t0, v_c);
        k2 = h * f(t0 + h / 2, v_c + k1 / 2);
        k3 = h * f(t0 + h / 2, v_c + k2 / 2);
        k4 = h * f(t0 + h, v_c + k3);

        v_c = v_c + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

        t0 += h;
    }

    return v_c;
}

int main() {
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL) {
        fprintf(stderr, "Error: Unable to open GNUplot.\n");
        return 1;
    }

    fprintf(gnuplot, "set terminal 'png'\n");
    fprintf(gnuplot, "set output 'Capacitor Charging.png'\n");
    fprintf(gnuplot, "set title 'Capacitor Charging 1'\n");
    fprintf(gnuplot, "set xlabel 'Time (s)'\n");
    fprintf(gnuplot, "set ylabel 'Voltage (V)'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot '-' with lines\n");

    double t = 0.0;
    double v_c = 0.0;

    while (t <= T) {
        fprintf(gnuplot, "%f %f\n", t, v_c);
        v_c = rungeKutta(t, v_c, t + DT, DT);
        t += DT;
    }

    fprintf(gnuplot, "e\n");
    fflush(gnuplot);
    pclose(gnuplot);

    return 0;
}
