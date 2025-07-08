# Not-quantum-entanglement simulation
A simple simulation to visualize quantum entanglement phenomena, nothing was intended to be scientifically accurate.

Project inspired from: Bjørn Gunnar Staal [https://www.youtube.com/watch?v=aKPkYY-CYuw]

# Introduction
Project made with C++ and SFML 3.0 (simple and fast multimedia library). No 3d library included, everything was made in 2d.



# Quantum principles implementation
- particle: i really don't think i can visualize the wave side of the particle, so i went with the particle representation.
- spin: visualized by literally rotating the dots around the Z-axis, one particle is rotating to the right and the other is rotating to the left to mimic (+1/2 , -1/2).
- entanglement: when the particles are first created they are not entangled yet, the one spining has a defined state (for example +1/2 spin) but the second one has an undefined state(the particle isn't rotating), after entanglement (when the particles are in the same position) the second particle gets a defined state (-1/2 spin).
- quantum information: represented by the line between the core of the two particles.
- distance dependency: even if the two particles exist in different galaxies (different rendering windows) they remain entangled (the line still follows the core of particles).
(./def_not_qm_entgl.mp4)
