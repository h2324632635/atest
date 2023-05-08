/*

Problem Description

Tom and Jerry are going on a vacation. They are now driving on a one-way road and several cars are in front of them. To be more specific, there are n cars in front of them. The ith car has a length of li, the head of it is si from the stop-line, and its maximum velocity is vi. The car Tom and Jerry are driving is l0 in length, and s0from the stop-line, with a maximum velocity of v0.
The traffic light has a very long cycle. You can assume that it is always green light. However, since the road is too narrow, no car can get ahead of other cars. Even if your speed can be greater than the car in front of you, you still can only drive at the same speed as the anterior car. But when not affected by the car ahead, the driver will drive at the maximum speed. You can assume that every driver here is very good at driving, so that the distance of adjacent cars can be kept to be 0.
Though Tom and Jerry know that they can pass the stop-line during green light, they still want to know the minimum time they need to pass the stop-line. We say a car passes the stop-line once the head of the car passes it.
Please notice that even after a car passes the stop-line, it still runs on the road, and cannot be overtaken.


Input

This problem contains multiple test cases.
For each test case, the first line contains an integer n (1≤n≤105,∑n≤2×106), the number of cars.
The next three lines each contains n+1 integers, li,si,vi (1≤si,vi,li≤109). It's guaranteed that si≥si+1+li+1,∀i∈[0,n−1]


Output

For each test case, output one line containing the answer. Your answer will be accepted if its absolute or relative error does not exceed 10−6.
Formally, let your answer be a, and the jury's answer is b. Your answer is considered correct if |a−b|max(1,|b|)≤10−6.
The answer is guaranteed to exist.

*/





/*

Based on the provided problem description, the task is to find the minimum time required for Tom and Jerry to pass the stop-line while driving on a one-way road with several cars in front of them. The cars have different lengths, positions, and maximum velocities. Tom and Jerry's car is also defined with its length, position, and maximum velocity.

To solve this problem, you can follow these steps:

Read the number of test cases.
Iterate over each test case.
Read the number of cars in the current test case.
Initialize variables for the minimum time and the position of the last car.
Iterate over each car in reverse order (from the last car to the first car):
Read the car's length, position, and maximum velocity.
Calculate the relative position between the current car and the last car.
Calculate the time required for the current car to reach the stop-line based on its position, length, and maximum velocity.
Update the minimum time if the calculated time is greater than the current minimum time.
Update the position of the last car to the current car's position.
Print the minimum time for the current test case.
Repeat steps 3-6 for each test case.

*/


#include <iostream>

int main() {
    int t;
    std::cin >> t; // Read the number of test cases

    while (t--) {
        int n;
        std::cin >> n; // Read the number of cars in the current test case

        int l0, s0, v0;
        std::cin >> l0 >> s0 >> v0; // Read Tom and Jerry's car parameters

        double minTime = 0.0;
        int lastPos = s0;

        for (int i = n; i > 0; --i) {
            int li, si, vi;
            std::cin >> li >> si >> vi; // Read the current car parameters

            double relativePos = lastPos - si - li; // Calculate relative position
            double currTime = relativePos / vi; // Calculate time required to reach the stop-line

            if (currTime > minTime)
                minTime = currTime;

            lastPos = si; // Update the position of the last car
        }

        std::cout << minTime << std::endl; // Print the minimum time for the current test case
    }

    return 0;
}
