dyn.load('seq.so')

myseq <- function(from=as.integer(NA), to=as.integer(NA), by=as.numeric(NA), length.out=as.integer(NA)) {
    .Call('seq', from, to, by, length.out)
}

from = 1L
to = 10L

print(myseq(from, to, by = 1))
print(myseq(from, to, as.numeric(NA), 9L))
print(myseq(from, to, as.numeric(NA), 10L))
