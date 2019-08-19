# Project-Mach-1
# **PDM - Parachute Deployment Module**

# Basis for use
Due to the relatively small area reserved for the launch(~2km radius), we need to make sure the rocket does not fall outside the boundary. In order to do that, we need to deploy the main parachute very late, 300m above ground so that it does not slowly drift away as it descends. The parachute deployer would keep the main parachute undeployed until the threshold height is reached before deploying.

# requirements
* must be able to handle the high G forces during launch and must me mechanical stable
* Must use a combination of pressure and temperature to determine altitude
* Unexpected spikes in pressure must be safely handled to prevent the parachute from deploying prematurely or late. Potentially using a low pass filter.
* Must be mechanically reliable when deploying. 99% success during testing required.
