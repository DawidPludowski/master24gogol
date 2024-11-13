dyn.load('vec.so')

mycumsum <- function(x, na.rm=FALSE) {
    .Call('c_cumsum', x, na.rm)
}

a1 <- c(1, 2, 3, 4, 5)
a2 <- c(1, 2, 3, 4, NA)

b1 <- c(1.0, 2.5, 5.8)
b2 <- c(NA, 2.5, 5.8)

c1 <- c(TRUE, TRUE, TRUE)
c2 <- c(TRUE, FALSE, TRUE)
c3 <- c(TRUE, NA, NA)

print(mycumsum(a1, TRUE))
print(mycumsum(a1, FALSE))
print(mycumsum(a2, TRUE))
print(mycumsum(a2, FALSE))

print(mycumsum(b1, TRUE))
print(mycumsum(b1, FALSE))
print(mycumsum(b2, TRUE))
print(mycumsum(b2, FALSE))

print(mycumsum(c1, TRUE))
print(mycumsum(c2, TRUE))
print(mycumsum(c3, TRUE))
print(mycumsum(c3, FALSE))