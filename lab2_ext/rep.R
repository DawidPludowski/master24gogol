dyn.load('rep.so')

myrep <- function(x, times=as.numeric(NA), length.out=as.numeric(NA)) {
    .Call('rep', x, times, length.out)
}

x <- c(1, 2, 3, 4, 5)

print(myrep(x, times=2L))
print(myrep(x, length.out=7L))
print(myrep(x, length.out=3L))
