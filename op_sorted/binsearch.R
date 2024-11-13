dyn.load('binsearch.so')

mybinsearch <- function(x, el) {
    .Call('binsearchc', x, el)
}

x <- c(1, 2, 3, 4, 5)
y <- c(5, 2, 3, 1, 4)

print(mybinsearch(x, 4))
print(mybinsearch(-x, -4))
print(mybinsearch(y, 2))
print(mybinsearch(y, 200))



