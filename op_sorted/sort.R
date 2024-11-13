dyn.load('sort.so')

mysort <- function(x) {
    .Call('sortc', x)
}

x <- c(1, 2, 3, 4, 5)
y <- c(5, 2, 3, 1, 4)

print(mysort(x))
print(mysort(-x))
print(mysort(y))


