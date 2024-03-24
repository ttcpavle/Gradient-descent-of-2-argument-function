# Gradient descent of 2 argument function z=f(x,y)
The gradient vector is a vector that points in the direction of the steepest increase of a function at a given point. Gradient descent is an 
optimization algorithm that iteratively moves towards the minimum of a function by taking steps proportional to the negative of the gradient 
(antigradient) at the current point. It is used in various fields like: machine learning, deep learning, computer vision, physics simulations and so on.

Gradient descent visually:

<img src="https://github.com/ttcpavle/Gradient-descent-of-2-argument-function/assets/159661698/5e2b4374-ab35-4d6e-98a7-91fcbd74f683" alt="Gradient descent" style="width: 50%;">

There are more efficient and effective ways to find local minimum of a function like Stochastic Gradient Descent, Mini-batch Gradient Descent,
Newton's Method, Conjugate Gradient Method... so this is only just for understanding a concept of gradient descent.
# Script:
This is a simple script for finding local minimum of a 2 argument function z=f(x,y) starting from given point (x,y).
MinimumCalculator uses constant size step vectors while MinimumCalculator2 uses anti-gradient vector itself.
The second one works better (in my example) since it breaks from loop after smaller number of iterations and the closer 
it gets to minimum, the more precise is estimation. With constant step size an oscillation around minimum is likely to occur.
