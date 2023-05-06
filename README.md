# TSP-Solver
Travelling Salesman Problem Solver using GRASP and Swap Algorithm


GRASP TSP Solver with Swap Algorithm

This program is a TSP (Traveling Salesman Problem) solver that uses the GRASP (Greedy Randomized Adaptive Search Procedure) algorithm with a Swap implementation as a local search method. 
The program reads a TSP file, which contains the coordinations of each city and calculates the shortest possible route that visits each city exactly once.

How to Use

    Clone the repository to your local machine.
    Compile the program using a C++ compiler of your choice.
    Run the executable.
    Enter the TSP filename when prompted.
    Choose the starting location from the available options.
    Enter the time limit in seconds.
    Wait for the program to calculate the shortest route.
    The program will output the total distance of the route and the route taken.

Implementation Details

GRASP Algorithm

The GRASP algorithm is a metaheuristic that combines a greedy algorithm with a randomised component to generate an initial solution. 
It then improves the solution iteratively by removing or adding elements to the solution set. 

The algorithm works as follows:

    1. Generate an initial solution using a greedy algorithm with a randomized component.
    2. Improve the initial solution using a local search method (in this program, the Swap algorithm is used).
    3. Repeat step 2 until a stopping criterion is met (in this program, the time limit).

Swap Algorithm

The Swap algorithm is a local search method that improves the current solution by swapping the position of two cities in the route. 

The algorithm works as follows:

 1. Choose two cities to swap.
 2. Calculate the total distance of the new route.
 3. If the new route is shorter than the current route, update the current route with the new route.
    Repeat steps 1-3 until no further improvement can be made.

Candidate List

The candidate list is a parameter that determines the number of candidate cities considered in each iteration of the GRASP algorithm. 
The candidate list size is set according to the size of the dataset, with larger datasets having a larger candidate list size.

Time Limit

The time limit is a parameter that determines the maximum amount of time the program is allowed to run. The program will stop once the time limit is reached, regardless of whether a solution has been found.

Dataset examined

The program has been tested on the following datasets:

    wi29, 15 seconds
    dj38, 15 seconds
    xqf131, 1 minute
    qa194, 1 minute
    uy734, 10 minutes
    zi929, 15 minutes
    lim963, 15 minutes
    xit1083, 15 minutes

For the large-sized datasets, the time limit entered should be smaller than the designated time limit above to stop before reaching the time limit. Thus enter a smaller time limit, as there are more swaps and GRASPs to be done.
