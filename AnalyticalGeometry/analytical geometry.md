# Question
Given two points $A(-3,4)$ and $B(9,-1)$ and a point $C(x,k)$ where $k$ is a fixed constant while $x$ is free, Find for which values of k we have the angle $\angle ACB ≠ 90^\circ$ using the <b>Inverse Pythagorean Theorem</b>.

# Answer

Let's start by noting that the <b>Inverse Pythagorean Theorem</b> tells us that in a triangle, the angle at point $C$ is $90^\circ$ if its sides satisfy the equation:

$$ AC^2 + BC^2 = AB^2. $$

We are given:

-   $A(-3, 4)$,
    
-   $B(9, -1)$,
    
-   $C(x, k)$ where $k$ is fixed and $x$ is free.
    

### Step 1: Compute $AB^2$, $AC^2$ and $BC^2$

$$AB^2 = (9-(-3))^2+(-1-4)^2=12^2 + (-5)^2 = 144 + 25 = 169. $$$$ AC^2 = (x-(-3))^2+(k-4)^2=(x + 3)^2 + (k - 4)^2, $$ $$ BC^2 = (x-9)^2+(k-(-1))^2 = (x - 9)^2 + (k + 1)^2.  $$

### Step 2: Set Up the Right Angle Condition

For angle $\angle ACB$ to not be $90^\circ$, the condition is: 

$AC^2+BC^2\neq AB^2$

Which is equivalent to:

$$ (x+3)^2 + (k-4)^2 + (x-9)^2 + (k+1)^2 \neq 169. $$

#### Expand and Simplify:

1.  Expand the $x$-terms: $$ (x+3)^2 = x^2 + 6x + 9, \quad (x-9)^2 = x^2 - 18x + 81. $$ Adding: $$ (x+3)^2 + (x-9)^2 = 2x^2 - 12x + 90. $$
    
2.  Expand the $k$-terms: $$ (k-4)^2 = k^2 - 8k + 16, \quad (k+1)^2 = k^2 + 2k + 1. $$ Adding: $$ (k-4)^2 + (k+1)^2 = 2k^2 - 6k + 17. $$
    

So the inequality becomes: $$ 2x^2 - 12x + 90 + 2k^2 - 6k + 17 \neq 169. $$ Combine the constant terms: $$ 2x^2 - 12x + 2k^2 - 6k + 107 \neq 169. $$ Subtract 169 from both sides: $$ 2x^2 - 12x + 2k^2 - 6k - 62 \neq 0. $$ Divide through by 2: $$ x^2 - 6x + k^2 - 3k - 31 \neq 0. $$

### Step 3: Determine When a Right Angle is Not Possible

The equation $$ x^2 - 6x + k^2 - 3k - 31 = 0 $$ will have a real solution for $x$ (meaning that there exists some location for $C$ with a right angle at $C$) if its discriminant is <b>nonnegative</b>. The discriminant $\Delta$ of a quadratic $ax^2 + bx + c = 0$ is given by: $$ \Delta = b^2 - 4ac. $$ Here, $a = 1, b = -6$, and $c = k^2 - 3k - 31$.

 Thus: $$ \Delta = (-6)^2 - 4 \cdot 1 \cdot (k^2 - 3k - 31) = 36 - 4(k^2 - 3k - 31). $$ Expanding: $$ \Delta = 36 - 4k^2 + 12k + 124 = -4k^2 + 12k + 160. $$

In order for the quadratic to <b>not</b> have a real solution in $x$, we must have: $$ \Delta=-4k^2 + 12k + 160 < 0. $$ Multiply the inequality by $-1$ (remembering to flip the sign): $$ 4k^2 - 12k - 160 > 0. $$ Divide by 4: $$ k^2 - 3k - 40 > 0. $$

### Step 4: Solve the Quadratic Inequality

First we will solve the quadratic equation: $$ k^2 - 3k - 40 = 0. $$ The discriminant for this equation is: $$ \delta = (-3)^2 - 4 \cdot 1 \cdot (-40) = 9 + 160 = 169. $$ Thus, the roots are: $$ k = \frac{3 \pm \sqrt{169}}{2} = \frac{3 \pm 13}{2}. $$ This gives: $$ k = 8 \quad \text{or} \quad k = -5. $$

Since the quadratic $k^2 - 3k - 40$ opens upward (the coefficient of $k^2$ which is $1$ is positive), the inequality $$ k^2 - 3k - 40 > 0 $$ is satisfied for: $$ k < -5 \text{ or } 8<k$$

## Final Answer: 

For every choice of $k$ that satisfies the inequalities $k<-5\text{ or }8<k$ no matter what $x$ you choose, the angle $\angle ACB$ will never be $90^\circ$, In other words: For every choice of the point $C$ on every horizontal line below the line $y=-5$ or above the line $y=8$ that you choose, You will never get $\angle ACB=90^\circ$ no matter where the point $C$ is located.
