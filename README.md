# TrafficJamSimulation

Simulation of Traffic Jam Simulation with Crossroad example. Here is also my aproach to Data-Driven like ECS to moving actors. I have implemented some interfaces and classes to develop data oriented optimization.

# Example

https://user-images.githubusercontent.com/56387911/167942577-4f5ab734-563f-4372-ab9c-5f4edb487460.mp4

# Repository

https://github.com/kosowskie/TrafficJamSimulation </br>

# How It was implemented

At first, GameMode creates our EntityManager. Therefore It creates needed systems (we need to declare them). 
All actors which implements special interface are converted to Entity. Actually Instance of InstancedStaticMeshComponent which belong to specific System.
Now we can update view, but also data of specific Entities from our System.

# How to implement

To Convert any actor to Entity, they need to extend EntityInterface.h interface. Only override GetData with this interface with specific FEntityData struct of ours. Then we need to exclude custom EntityManager class to declare which systems will be implemented.
Override InitializeSystems method and then with specific subclass create them with derivde method CreateSystem(TSubclassOf<AActor> SystemClass).
System can be created by EntitySystem.h class as a parent. System need to have our own type of continer, Id (the same as Entity) and overriden Adding and Removing methods.
Now with UpdateInstanceLocation and Add/Remove Entity methods we could improve our system!

# What we get with InstancedStaticMesh

We dont create/destroy objects during runtime which consumes CPU resources. Also we dont render object all the time but only when counted all data on specific entites.
So we dont split data through motherboard bus between memory, CPU and GPU.
