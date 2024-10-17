# DSA_Project

### Event-Driven Simulation Using a Priority Queue(using fibonachi heap)

#### Develop a simulation framework where events are processed based on priority or timing, such as simulating traffic flow in a city. Use a priority queue(should be doveloped from scratch using fibonacci heap)  to manage events like car arrivals and traffic light changes, ensuring they are processed in the correct order. The simulation runs until all events are processed or a set time is reached.

A Fibonacci Heap is a type of priority queue that provides efficient operations for algorithms that need to repeatedly insert, delete, or modify elements, especially when the priority (or key) of elements can change over time. It is named after the Fibonacci numbers because the analysis of its time complexity involves Fibonacci series properties.

In a Fibonacci Heap, it follows the basic idea of a min heap but the change is that each node contains 4 pointers in it that is its parent, child, left and right node which are at the same level