dyn.load("rinsertsort.so")

insertsort <- function(x) {
    size <- length(x)
    .Call("insertsort_wrapper", x, PACAKGE="rinsertsort.so")
}

arr <- as.integer(c(6, 3, 9, 2, 1, 0, 10, 4, 8, 7))
print(arr)

insertsort(arr)

print(arr)