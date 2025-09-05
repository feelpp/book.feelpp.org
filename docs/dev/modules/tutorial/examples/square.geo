// Simple square domain for Feel++ tutorials
// Author: Feel++ Consortium

// Mesh parameters
h = 0.1;  // characteristic mesh size

// Domain boundaries
Point(1) = {0, 0, 0, h};
Point(2) = {1, 0, 0, h};
Point(3) = {1, 1, 0, h};
Point(4) = {0, 1, 0, h};

// Boundary edges
Line(1) = {1, 2};
Line(2) = {2, 3};  
Line(3) = {3, 4};
Line(4) = {4, 1};

// Create surface
Line Loop(1) = {1, 2, 3, 4};
Plane Surface(1) = {1};

// Physical groups for boundary conditions
Physical Line("bottom") = {1};
Physical Line("right") = {2};
Physical Line("top") = {3};
Physical Line("left") = {4};
Physical Surface("domain") = {1};
