dyn.load('agg.so')

myprod <- function(x, na.rm=FALSE) {
    .Call('c_prod', x, na.rm)
}

a1 <- c(1, 2, 3, 4, 5)
a2 <- c(1, 2, 3, 4, NA)

b1 <- c(1.0, 2.5, 5.8)
b2 <- c(NA, 2.5, 5.8)

c1 <- c(TRUE, TRUE, TRUE)
c2 <- c(TRUE, FALSE, TRUE)
c3 <- c(TRUE, NA, NA)

print(myprod(a1, TRUE))
print(myprod(a1, FALSE))
print(myprod(a2, TRUE))
print(myprod(a2, FALSE))

print(myprod(b1, TRUE))
print(myprod(b1, FALSE))
print(myprod(b2, TRUE))
print(myprod(b2, FALSE))

print(myprod(c1, TRUE))
print(myprod(c2, TRUE))
print(myprod(c3, TRUE))
print(myprod(c3, FALSE))