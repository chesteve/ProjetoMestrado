interArrival_sample = [ 5.0000e-07, 1.5000e-06, 1.5000e-06, 2.5000e-06, 2.5000e-06, 3.5000e-06, 4.5000e-06, 7.5000e-06, 1.2500e-05, 1.9500e-05, 3.1500e-05, 4.3500e-05, 6.0500e-05, 7.6500e-05, 1.1050e-04, 1.4050e-04, 1.8150e-04, 2.1150e-04, 2.3350e-04, 2.4350e-04, 2.5650e-04, 3.0350e-04, 4.1250e-04, 1.3655e-03, 1.1593e-02, 3.2483e-02, 8.1235e-02, 2.0939e-01, 5.0755e-01, 1.7351e+00 ]' ;
X_sample = [ones(length(interArrival_sample), 1) , interArrival_sample];
theta = zeros(2, 1);
emCdf_octave = [ 0.033333, 0.100000, 0.100000, 0.166667, 0.166667, 0.200000, 0.233333, 0.266667, 0.300000, 0.333333, 0.366667, 0.400000, 0.433333, 0.466667, 0.500000, 0.533333, 0.566667, 0.600000, 0.633333, 0.666667, 0.700000, 0.733333, 0.766667, 0.800000, 0.833333, 0.866667, 0.900000, 0.933333, 0.966667, 1.000000 ];
fprintf("emCdf_octave, theta,  interArrival_sample and X_sample loaded\n")
