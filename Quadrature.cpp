#include "Quadrature.h"

namespace Sun {

    double GaussQuadrature::roots_2[2] = { 0.5773502692,-0.5773502692 };
    double GaussQuadrature::cofs_2[2] = { 1.0, 1.0 };
    double GaussQuadrature::roots_3[3] = { 0.7745966692, 0.0,-0.7745966692 };
    double GaussQuadrature::cofs_3[3] = { 0.5555555556,0.8888888889,0.5555555556 };
    double GaussQuadrature::roots_4[4] = { 0.8611363116, 0.3399810436, -0.3399810436, -0.8611363116 };
    double GaussQuadrature::cofs_4[4] = { 0.3478548451, 0.6521451549, 0.6521451549 ,0.3478548451 };
    double GaussQuadrature::roots_5[5] = { 0.9061798459, 0.5384693101, 0.0,-0.5384693101,-0.9061798459 };
    double GaussQuadrature::cofs_5[5] = { 0.2369268850, 0.4786286705, 0.5688888889,0.4786286705, 0.2369268850 };

}