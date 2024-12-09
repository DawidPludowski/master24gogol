# Lecture 9

## Written assignment in next week

* material from leture 1-8
* max 20 points

## Programming assignment (before xmass, two weeks)

* probably in numpy but may be R
* matrices operations

## Actual lecture

### WCSS

$\min_{C_i : C_k} \frac 1n \sum_{l=1}^k \frac{1}{C_l} \sum_{x,x' \in C_l} \| x - x' \|^2$

* discrete steepest ascend (hill climbing) - can be used on top of other algorithms
    1. tabu search
* k-means algrithm
    1. centroid of $C \in X$: $\mu = \frac{1}{|C|} \sum_{x \in C} x = argmin_\mu \sum\|x-\mu\|$
        * `x[c == i].mean(axis=0)`
    2. variance of $C$: $\frac{1}{C} \sum_{x \in C} \| x - \mu \|^2$
    3. sum of squares $SS(C)$: $2 \sum_{x \in C} \|x - \mu \|^2 = 2|C|VarC$
    4. $min_{C_1:C_k}\frac 1n \sum^k_{l=1} \sum_{x\in C_l} \| x - \mu_l \|^2 = \frac 1n \sum_{x\in X} \| x - \mu_x \|$
    5. now, function is dpeendent of choising centroids, not clusters
    6. it's now Lloyd algorithm
        * pick centers $\mu_1,\dots,\mu_k$ from the observations
        * for each point assign the nearest $\mu_i$ (minimizing distance)
        * recompute $\mu$ in these clusters
        * go to the second point 'till convergence
        * complexity for one interation - O(nkd) observations, # of clusters, # of columns
* another approach - Gaussian mixtures
    1.
* fuzzy (soft) k-means (or c-means lol)
    1. we do not assign observation to the cluster but rather we assign weights of being in a certain cluster
    2. weights sum up to 1 and are non-negative
* on (idk on what lol), implement version of k-means
        * complexity for one interation - O(nkd) observations, # of clusters, # of columns
