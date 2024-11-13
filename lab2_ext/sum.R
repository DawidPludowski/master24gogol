dyn.load('sum.so')

mysum <- function(x, y) {
    .Call('sumc', x, y)
}

x <- c(1, 2, 3, NA, 5)
y <- c(1, 2, 3, 4, 5)


print(mysum(x, y))
print(mysum(x[1:2], y))
print(mysum(x, y[2:4]))

print(x + y)
print(x[1:2] + y)
print(x + y[2:4])
